#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#define NUM_MINES 60
#define BOARD_HEIGHT 18
#define BOARD_WIDTH 16
#define BOARD_LEN (BOARD_HEIGHT * BOARD_WIDTH / 2)

#define POSITION_MASK 0x0F

#define MINE_MASK 0x1
#define EMPTY 0x0
#define MINE 0x1

#define LABEL_MASK 0xE
#define UNMARKED 0x0
#define FLAGGED 0x2
#define QUESTION 0x4
#define EXPAND 0x6 /* Used to mark blocks that should be expanded */
#define EXPOSED 0x8

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
