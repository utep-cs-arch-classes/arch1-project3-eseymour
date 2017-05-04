#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <msp430.h>
#include <p2switches.h>
#include <sprite.h>

#include "board.h"
#include "draw.h"
#include "random.h"
#include "sprites.h"

#define NOT_STARTED 0
#define STARTED 1
#define OVER 2

#define NONE 0
#define ERROR 1
#define UP 2
#define LEFT 3
#define RIGHT 4
#define DOWN 5

signed char cursorX, cursorY;
u_char gameState, inputState;

void moveCursor() {
  // Draw working smiley
  drawSmiley(WORKING);
  
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
  drawSmiley(SMILE);
}

int main(void) {
  configureClocks();
  rngSeedSram();
  lcd_init();
  p2sw_init(0xF);
  or_sr(0x8);

  /* Initialize Timer1A */
  TA1CTL = TASSEL_2 + MC_2;

  curPalette = (Palette *) &basicPalette;
  u_char width = screenWidth, height = screenHeight;

  clearScreen(curPalette->colors[0]);

  drawSmiley(WORKING);

  boardInit();
  cursorX = BOARD_WIDTH / 2;
  cursorY = BOARD_HEIGHT / 2;
  
  drawTime(0);
  drawMineCount();
  drawBoard();
  drawCursor(cursorX, cursorY);

  drawSmiley(SMILE);
  inputState = NONE;
  while (1) {
    
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
      inputState = inputState == EMPTY || inputState == RIGHT ? RIGHT : ERROR;
      break;
    default:
      inputState = ERROR;
    }
  }
  
  boardGenerateMines(cursorX, cursorY);
  drawMineCount();

  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (!isMine(i, j)) {
	setPosition(i, j, EXPOSED + EMPTY);
      }
    }
  }
  
  drawBoard();
  drawMines(1);
  drawCursor(cursorX, cursorY);

  drawSmiley(COOL);
}
