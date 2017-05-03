#ifndef SPRITE_INCLUDED
#define SPRITE_INCLUDED

typedef unsigned long u_long;

typedef struct Palette_s {
  u_int colors[16];
} Palette;

typedef struct Sprite8x8_s {
  u_int paletteColors;
  u_int rows[8];
} Sprite8x8;

typedef struct Sprite8x16_s {
  u_int paletteColors;
  u_int rows[16];
} Sprite8x16;

typedef struct Sprite16x16_s {
  u_int paletteColors;
  u_long rows[32];
} Sprite16x16;

extern Palette *curPalette;

void drawSprite8x8(u_char col, u_char row, Sprite8x8 *sprite);

void drawSprite8x16(u_char col, u_char row, Sprite8x16 *sprite);

void drawSprite16x16(u_char col, u_char row, Sprite16x16 *sprite);

#endif /* SPRITE INCLUDED */
