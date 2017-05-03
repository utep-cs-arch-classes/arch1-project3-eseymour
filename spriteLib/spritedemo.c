#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "sprite.h"
#include "sprites.h"

int main(void) {
  configureClocks();
  lcd_init();

  curPalette = &basicPalette;
  u_char width = screenWidth, height = screenHeight;

  clearScreen(curPalette->colors[0]);

  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 9; j++) {
      drawSprite8x8(j*8, i*8, &emptySquares[j]);
    }
    for (int j = 0; j < 2; j++) {
      drawSprite8x8(72 + j*8, i*8, &bombSquares[j]);
    }
    for (int j = 0; j < 3; j++) {
      drawSprite8x8(88 + j*8, i*8, &uncheckedSquares[j]);
    }
  }

  for (int i = 0; i < 10; i++) {
    drawSprite8x16(i*8, 112, &ssdNumbers[i]);
  }

  for (int i = 0; i < 4; i++) {
    drawSprite16x16(i*16, 128, &smileyFaces[i]);
  }

  //drawSprite8x16(8, 8, &test8x16);
  //drawSprite16x16(16, 24, &test16x16);
}
