#include "lcdutils.h"
#include "lcddraw.h"
#include "sprite.h"

Palette *curPalette;

void drawSprite8x8(u_char col, u_char row, Sprite8x8 *sprite) {
  u_int colorsBGR[4] = {
    curPalette->colors[sprite->paletteColors & 0x000F],
    curPalette->colors[(sprite->paletteColors & 0x00F0) >> 4],
    curPalette->colors[(sprite->paletteColors & 0x0F00) >> 8],
    curPalette->colors[(sprite->paletteColors & 0xF000) >> 12]
  };
  
  lcd_setArea(col, row, col + 7, row + 7);
  
  for (row = 0; row < 8; row++) {
    u_int mask = 0x3;
    for (col = 0; col < 8; col++, mask) {
      u_int index = sprite->rows[row];
      index >>= col * 2;
      index &= mask;
      lcd_writeColor(colorsBGR[index]);
    }
  }
}

void drawSprite8x16(u_char col, u_char row, Sprite8x16 *sprite) {
  u_int colorsBGR[4] = {
    curPalette->colors[sprite->paletteColors & 0x000F],
    curPalette->colors[(sprite->paletteColors & 0x00F0) >> 4],
    curPalette->colors[(sprite->paletteColors & 0x0F00) >> 8],
    curPalette->colors[(sprite->paletteColors & 0xF000) >> 12]
  };
  
  lcd_setArea(col, row, col + 7, row + 15);
  
  for (row = 0; row < 16; row++) {
    u_int mask = 0x3;
    for (col = 0; col < 8; col++) {
      u_int index = sprite->rows[row];
      index >>= col * 2;
      index &= mask;
      lcd_writeColor(colorsBGR[index]);
    }
  }
}

void drawSprite16x16(u_char col, u_char row, Sprite16x16 *sprite) {
  u_int colorsBGR[4] = {
    curPalette->colors[sprite->paletteColors & 0x000F],
    curPalette->colors[(sprite->paletteColors & 0x00F0) >> 4],
    curPalette->colors[(sprite->paletteColors & 0x0F00) >> 8],
    curPalette->colors[(sprite->paletteColors & 0xF000) >> 12]
  };
  
  lcd_setArea(col, row, col + 15, row + 15);
  
  for (row = 0; row < 16; row++) {
    u_long mask = 0x3;
    for (col = 0; col < 16; col++) {
      u_long index = sprite->rows[row];
      index >>= col * 2;
      index &= mask;
      lcd_writeColor(colorsBGR[index]);
    }
  }
}
