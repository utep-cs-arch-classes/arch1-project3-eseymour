#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <sprite.h>

#include "sprites.h"

int main(void) {
  configureClocks();
  lcd_init();

  curPalette = (Palette *) &basicPalette;
  u_char width = screenWidth, height = screenHeight;

  clearScreen(curPalette->colors[0]);

  drawSprite16x16(56, 0, (Sprite16x16 *) &smileyFaces[1]);

  for (int i = 0; i < 3; i++) {
    drawSprite8x16(i*8, 0, (Sprite8x16 *) &ssdNumbers[i+1]);
    drawSprite8x16(104 + i*8, 0, (Sprite8x16 *) &ssdNumbers[0]);
  }

  for (int i = 0; i < 18; i++) {
    for(int j = 0; j < 16; j++) {
      drawSprite8x8(j*8, 16+i*8, (Sprite8x8 *) &uncheckedSquares[0]);
    }
  }

  drawSprite16x16(56, 0, (Sprite16x16 *) &smileyFaces[0]);

  drawRectOutline(56, 80, 8, 8, curPalette->colors[6]);
}
