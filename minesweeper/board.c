#include <lcdutils.h>

#include "board.h"

#include "random.h"
#include "draw.h"

static u_char board[BOARD_LEN];

u_char minesRemaining;

void boardInit(void) {
  for (int i = 0; i < BOARD_LEN; i++) {
    board[i] = EMPTY;
  }

  minesRemaining = 0;
}

void boardGenerateMines(u_char startX, u_char startY) {
  rngSeedTimer();
  
  while (minesRemaining < NUM_MINES) {
    char x = rngNext() % BOARD_WIDTH;
    char y = rngNext() % BOARD_HEIGHT;

    if (!isMine(x, y)) {
      if (startX - x > 1 || startX - x < -1 || startY - y > 1 || startY - y < -1) {
	/* Position is empty and not adjacent to start point */
	setPosition(x, y, MINE);
	minesRemaining++;
      }
    }
  }
}

u_char getPosition(u_char x, u_char y) {
  int index = (x + BOARD_WIDTH * y) / 2;

  if (x % 2 == 0) {
    return board[index] & POSITION_MASK;
  }
  else {
    return board[index] >> 4 & POSITION_MASK;
  }
}

void setPosition(u_char x, u_char y, u_char newVal) {
  int index = (x + BOARD_WIDTH * y) / 2;
  newVal &= POSITION_MASK;

  if (x % 2 == 0) {
    board[index] &= POSITION_MASK << 4;
    board[index] |= newVal; 
  }
  else {
    board[index] &= POSITION_MASK;
    board[index] |= newVal << 4;
  }
}

u_char isMine(u_char x, u_char y) {
  return MINE_MASK & getPosition(x, y) == MINE;
}

u_char isFlagged(u_char x, u_char y) {
  return LABEL_MASK & getPosition(x, y) == FLAGGED;
}

u_char numNeighboringMines(u_char x, u_char y) {
  int numMines = 0;
  
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
	/* Don't count self */
	continue;
      }

      if (i+x < 0 || i+x >= BOARD_WIDTH || j+y < 0 || j+y >= BOARD_HEIGHT) {
	/* Don't go out of bounds */
	continue;
      }
      if (isMine(i + x, j + y)) {
	numMines++;
      }
    }
  }

  return numMines;
}

u_char numNeighboringFlags(u_char x, u_char y) {
  int numFlags = 0;
  
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
	/* Don't count self */
	continue;
      }

      if (i+x < 0 || i+x >= BOARD_WIDTH || j+y < 0 || j+y >= BOARD_HEIGHT) {
	/* Don't go out of bounds */
	continue;
      }
      if (isFlagged(i + x, j + y)) {
	numFlags++;
      }
    }
  }

  return numFlags;
}

void expandIteratively(void);
void expandPart(u_char x, u_char y);

void expandBlock(u_char x, u_char y) {
  setPosition(x, y, EXPOSED);

  if(numNeighboringMines(x, y) == 0) {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
	if (i == 0 && j == 0) {
	  continue;
	}

	if (i+x < 0 || i+x >= BOARD_WIDTH || j+y < 0 || j+y >= BOARD_HEIGHT) {
	  continue;
	}
	
	if (getPosition(i+x, j+y) != EXPOSED) {
	  setPosition(i+x, j+y, EXPAND);
	}
      }
    }

    expandIteratively();
  }
  
  drawBlock(x, y);
}

void expandIteratively(void) {
  u_char keepExpanding;

  do {
    keepExpanding = 0;
    for (int i = 0; i < BOARD_WIDTH; i++) {
      for (int j = 0; j < BOARD_HEIGHT; j++) {
	if (getPosition(i, j) == EXPAND) {
	  expandPart(i, j);
	  keepExpanding = 1;
	}
      }
    }
  } while (keepExpanding);
}

void expandPart(u_char x, u_char y) {
  setPosition(x, y, EXPOSED);

  if(numNeighboringMines(x, y) == 0) {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
	if (i == 0 && j == 0) {
	  continue;
	}

	if (i+x < 0 || i+x >= BOARD_WIDTH || j+y < 0 || j+y >= BOARD_HEIGHT) {
	  continue;
	}

	if (getPosition(i+x, j+y) != EXPOSED) {
	  setPosition(i+x, j+y, EXPAND);
	}
      }
    }
  }
  
  drawBlock(x, y);
}
