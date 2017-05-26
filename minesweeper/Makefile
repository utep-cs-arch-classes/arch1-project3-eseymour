# Makefile configuration
CPU	= msp430g2553
CFLAGS	= -mmcu=${CPU} -Os -I../h
LDFLAGS = -L../lib -L/opt/ti/msp430_gcc/include/

# Switch the compiler (for internal make rules)
CC	= msp430-elf-gcc
AS	= msp430-elf-gcc -mmcu=${CPU} -c

all: minesweeper.elf

minesweeper.o: board.h draw.h random.h sprites.h

board.o: board.h draw.h random.h

draw.o: draw.h board.h sprites.h

drawBlock.o: draw.h board.h sprites.h

Random.o: random.h

sprites.o: sprites.h

minesweeper.elf: minesweeper.o board.o draw.o drawBlock.o random.o sprites.o 
	${CC} ${CFLAGS} ${LDFLAGS} -mendup-at=main -o $@ $^ -lTimer -lLcd -lSprite -lp1sw -lp2sw

load: minesweeper.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf
