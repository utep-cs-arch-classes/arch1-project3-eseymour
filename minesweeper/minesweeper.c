#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <msp430.h>
#include <p1switches.h>
#include <p2switches.h>
#include <sprite.h>

#include "board.h"
#include "draw.h"
#include "random.h"
#include "sprites.h"

#define NOT_STARTED 0
#define STARTED 1
#define LOSS 2
#define VICTORY 3

#define NONE 0
#define ERROR 1
#define UP 2
#define LEFT 3
#define RIGHT 4
#define DOWN 5
#define CLICK 6
#define FLAG 7
#define MARK_QUESTION 8

signed char cursorX, cursorY;
u_char gameState, inputState, curSmiley, nextSmiley;

void moveCursor() {
  // Clear cursor
  drawBlock(cursorX, cursorY);

  // Find next position
  switch (inputState) {
  case UP:
    cursorY--;
    break;
  case DOWN:
    cursorY++;
    break;
  case LEFT:
    cursorX--;
    break;
  case RIGHT:
    cursorX++;
  }

  // Clamp to bounds
  cursorX = cursorX < 0 ? 0 : cursorX;
  cursorX = cursorX >= BOARD_WIDTH ? BOARD_WIDTH - 1 : cursorX;
  cursorY = cursorY < 0 ? 0 : cursorY;
  cursorY = cursorY >= BOARD_HEIGHT ? BOARD_HEIGHT - 1 : cursorY;

  drawCursor(cursorX, cursorY);
}

void clickAtCursor(void) {
  if (gameState == NOT_STARTED) {
    boardGenerateMines(cursorX, cursorY);
    drawMineCount();
    gameState == STARTED;
  }

  if (isMine(cursorX, cursorY)) {
    gameState = LOSS;
    return;
  }

  expandBlock(cursorX, cursorY);
  drawCursor(cursorX, cursorY);
}

void flagAtCursor(void) {
  u_char block = getPosition(cursorX, cursorY);

  switch (block) {
  case FLAGGED:
    minesRemaining++;
    setPosition(cursorX, cursorY, UNMARKED);
    break;
  case FLAGGED + MINE:
    minesRemaining++;
    setPosition(cursorX, cursorY, UNMARKED + MINE);
    break;
  case EXPOSED:
    break;
  case UNMARKED:
  case QUESTION:
    minesRemaining--;
    setPosition(cursorX, cursorY, FLAGGED);
    break;
  case UNMARKED + MINE:
  case QUESTION + MINE:
    minesRemaining--;
    setPosition(cursorX, cursorY, FLAGGED + MINE);
  }

  drawMineCount();
  drawBlock(cursorX, cursorY);
  drawCursor(cursorX, cursorY);
}

void markQuestionAtCursor(void) {
}

void main(void) {
  configureClocks();
  rngSeedSram();
  lcd_init();
  p1sw_init(0x8);
  p2sw_init(0xF);
  or_sr(0x8);

  /* Initialize Timer1A */
  TA1CTL = TASSEL_2 + MC_2;

  curPalette = (Palette *) &basicPalette;
  u_char width = screenWidth, height = screenHeight;

  clearScreen(curPalette->colors[0]);

  curSmiley = WORKING;
  drawSmiley(curSmiley);

  boardInit();
  cursorX = BOARD_WIDTH / 2;
  cursorY = BOARD_HEIGHT / 2;
  
  drawTime(0);
  drawMineCount();
  drawBoard();
  drawCursor(cursorX, cursorY);

  nextSmiley = SMILE;
  inputState = NONE;
  gameState = NOT_STARTED;
  
  while (gameState == NOT_STARTED || gameState == STARTED) {
    /* Choose proper Smiley */
    switch (inputState) {
    case NONE:
    case ERROR:
    default:
      nextSmiley = SMILE;
      break;
    case UP:
    case DOWN:
    case LEFT:
    case RIGHT:
    case CLICK:
    case FLAG:
    case MARK_QUESTION:
      nextSmiley = WORKING;
    }

    /* Update Smiley if necessary */
    if (curSmiley != nextSmiley) {
      drawSmiley(nextSmiley);
      curSmiley = nextSmiley;
    }
    
    if(p1sw_read() & 0x8) {
      /* Arrow keys */
      switch (p2sw_read() & 0xF) {
      case 0xF:
	if (inputState != NONE) {
	  moveCursor();
	}
	inputState = NONE;
	break;
      case 0xE:
	inputState = inputState == NONE || inputState == UP ? UP : ERROR;
	break;
      case 0xD:
	inputState = inputState == NONE || inputState == DOWN ? DOWN : ERROR;
	break;
      case 0xB:
	inputState = inputState == NONE || inputState == LEFT ? LEFT : ERROR;
	break;
      case 0x7:
	inputState = inputState == NONE || inputState == RIGHT ? RIGHT : ERROR;
	break;
      default:
	inputState = ERROR;
      }
    }
    else {
      /* Action Keys */
      switch (p2sw_read() & 0xF) {
      case 0xF:
	switch (inputState) {
	case CLICK:
	  clickAtCursor();
	  break;
	case FLAG:
	  flagAtCursor();
	  break;
	case MARK_QUESTION:
	  markQuestionAtCursor();
	}
	
	inputState = NONE;
	break;
      case 0xE:
	inputState = inputState == NONE || inputState == CLICK ? CLICK : ERROR;
	break;
      case 0xD:
	inputState = inputState == NONE || inputState == FLAG ? FLAG : ERROR;
	break;
      case 0xB:
	inputState = inputState == NONE || inputState == MARK_QUESTION ? MARK_QUESTION : ERROR;
	break;
      case 0x7:
	/* Restart the game */
	return;
      default:
	inputState = ERROR;
      }
    }
  }

  drawMines(gameState == VICTORY ? 1 : 0);
  drawSmiley(gameState == VICTORY ? COOL : DEAD);
  drawCursor(cursorX, cursorY);

  while (1) {
  }
}
