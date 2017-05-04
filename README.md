# Minesweeper

For Project 3, I implemented a Minesweeper game. The game is incomplete and non interactive at the moment.

It also includes a sprite library to be able to draw the Minesweeper graphics.

One of the draw routines, `drawBlock(u_int x, u_int y)` is written in assembly since it used a switch.

## How to compile it

From the root directory of the repository type:

```shell
$ make
```

## How to run it

After first compiling, from the root directory of the repository type:

```shell
$ cd minesweeper
$ make load
```

To run the spriteLib demo instead, write

```shell
$ cd spriteLib
$ make load
```

## How to use it

Currently, it does not respond to user input. It does draw a board, then populates it with mines and shows the solution.

## Resources used

For the random number generator, I used a XOR shift generator as specified in http://b2d-f9r.blogspot.com/2010/08/16-bit-xorshift-rng-now-with-more.html

## More info on spriteLib

spriteLib defines 3 types of sprites, 8x8, 8x16 and 16x16.

Each sprite can only have 4 colors from a 16 color global palette. It is possible to switch palettes during computation, allowing graphics to be stored using a compact representation.

Palettes are simply a 16 word array with each color represented in 16 bit BGR.

For every sprite struct, the first word represents the colors used by the sprite as a 4 half byte array. After the first word, it is followed by an array of rows, starting from the top, and going to the bottom.

Then each row is represented as a 2 bit array, where each value represents each sprite color used. Colors are stored from left to right LSB
