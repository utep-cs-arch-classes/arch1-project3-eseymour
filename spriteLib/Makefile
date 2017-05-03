all: libSprite.a spritedemo.elf

CPU 	= msp430g2553
CFLAGS  = -mmcu=${CPU} -Os -I../h
LDFLAGS	= -L/opt/ti/msp430_gcc/include -L../lib
# Switch the compiler (for internal make rules)
CC	= msp430-elf-gcc
AS	= msp430-elf-as
AR	= msp430-elf-ar

libSprite.a: sprite.o
	${AR} crs $@ $^

sprite.o: sprite.c sprite.h

install: libSprite.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f libSprite.a *.o *.elf

spritedemo.elf: spritedemo.o sprites.o libSprite.a
	${CC} ${CFLAGS} ${LDFLAGS} $^ -L../lib -lTimer -lLcd -o $@

load: spritedemo.elf
	mspdebug rf2500 "prog $^"

spritedemo.o: sprites.h

sprites.o: sprites.h
