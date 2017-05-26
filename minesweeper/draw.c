#include <lcdutils.h>
#include <lcddraw.h>
#include <sprite.h>

#include "draw.h"

#include "board.h"
#include "sprites.h"

/* Implemented in assembly */
/*
void drawBlock(u_char x, u_char y) {
  u_char screenX, screenY;
  screenX = x * 8;
  screenY = 16 + y * 8;

  const Sprite8x8 *sprite;
  switch (getPosition(x, y) & LABEL_MASK) {
  case UNMARKED:
  default:
    sprite = &uncheckedSquares[0];
    break;
  case FLAGGED:
    sprite = &uncheckedSquares[1];
    break;
  case QUESTION:
    sprite = &uncheckedSquares[2];
    break;
  case EXPOSED:
    sprite = &emptySquares[numNeighboringMines(x, y)];
  }

  drawSprite8x8(screenX, screenY, (Sprite8x8 *) sprite);
}
*/

void drawCursor(u_char x, u_char y) {
  drawRectOutline(x * 8, 16 + y * 8, 8, 8, curPalette->colors[6]);
}

void drawTime(u_char elapsed) {
  for (int i = 0; i < 3; i++) {
    drawSprite8x16(104 + i*8, 0, (Sprite8x16 *) &ssdNumbers[elapsed % 10]);
    elapsed /= 10;
  }
}

void drawMineCount(void) {
  u_char remaining = minesRemaining;

  for (int i = 0; i < 3; i++) {
    drawSprite8x16(16 - i*8, 0, (Sprite8x16 *) &ssdNumbers[remaining % 10]);
    remaining /= 10;
  }
}

void drawPressed(u_char x, u_char y) {
  /* Pressed sprite needed */
  drawBlock(x, y);
}

void drawSmiley(u_char face) {
  drawSprite16x16(56, 0, (Sprite16x16 *) &smileyFaces[face]);
}

void drawBoard(void) {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      drawBlock(i, j);
    }
  }
}

void drawMines(u_char isVictory) {
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (isMine(i, j)) {
	drawSprite8x8(i*8, 16 + j*8,
		      (Sprite8x8 *) (isVictory ? &uncheckedSquares[1] :
				     &bombSquares[isFlagged(i, j) ? 1 : 0]));
      }
    }
  }
}
