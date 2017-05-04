#ifndef DRAW_INCLUDED
#define DRAW_INCLUDED

#define SMILE 0
#define WORKING 1
#define DEAD 2
#define COOL 3

void drawBlock(u_char x, u_char y);
void drawCursor(u_char x, u_char y);
void drawTime(u_char elapsed);
void drawMineCount(void);
void drawPressed(u_char x, u_char y);
void drawSmiley(u_char face);
void drawBoard(void);
void drawMines(void);

#endif /* DRAW_INCLUDED */
