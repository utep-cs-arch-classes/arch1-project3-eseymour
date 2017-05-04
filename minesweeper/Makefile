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
























random.o: random.h

sprites.o: sprites.h

minesweeper.elf: minesweeper.o board.o draw.o random.o sprites.o 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lSprite

load: minesweeper.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf
