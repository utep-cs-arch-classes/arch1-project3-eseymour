#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#define NUM_MINES 60
#define BOARD_HEIGHT 18
#define BOARD_WIDTH 16
#define BOARD_LEN (BOARD_HEIGHT * BOARD_WIDTH / 2)

#define POSITION_MASK 0x0F

#define MINE_MASK 0x01
#define EMPTY 0x00
#define MINE 0x01

#define LABEL_MASK 0x0E
#define UNMARKED 0x00
#define FLAGGED 0x02
#define QUESTION 0x04
#define EXPAND 0x06 /* Used to mark blocks that should be expanded */
#define EXPOSED 0x08

extern u_char minesRemaining;

void boardInit(void);
void boardGenerateMines(u_char startX, u_char startY);
u_char getPosition(u_char x, u_char y);
void setPosition(u_char x, u_char y, u_char newVal);
u_char isMine(u_char x, u_char y);
u_char isFlagged(u_char x, u_char y);
u_char numNeighboringMines(u_char x, u_char y);
u_char numNeighboringFlags(u_char x, u_char y);
void expandBlock(u_char x, u_char y);

#endif /* BOARD_INCLUDED */
