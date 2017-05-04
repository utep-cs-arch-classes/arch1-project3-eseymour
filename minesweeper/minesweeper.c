#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <msp430.h>
#include <sprite.h>

#include "board.h"
#include "draw.h"
#include "random.h"
#include "sprites.h"

u_char cursorX, cursorY;

int main(void) {
  configureClocks();
  rngSeedSram();
  lcd_init();

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

  boardGenerateMines(cursorX, cursorY);
  drawMineCount();

  for(int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if(!isMine(i, j)) {
	setPosition(i, j, EXPOSED + EMPTY);
      }
    }
  }
  
  drawBoard();
  drawMines();
  drawCursor(cursorX, cursorY);

  drawSmiley(COOL);
}
