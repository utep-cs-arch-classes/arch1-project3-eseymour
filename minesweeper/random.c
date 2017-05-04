#include <msp430.h>
#include <lcdutils.h>

#include "random.h"

static int x, y;

#define SRAM_MIN ((char *) 0x0200)
#define SRAM_MAX ((char *) 0x03FF)

void rngSeedSram(void) {
  char seed = 0;

  /* Iterate through SRAM and xor its contents together */
  for (char *i = SRAM_MIN; i <= SRAM_MAX; i++) {
    seed ^= *i;
  }

  y = seed;
}

void rngSeedTimer(void) {
  x = TA1R;

  TA1CTL = MC_0; /* Stop timer */
  
  if (x == 0 && y == 0) {
    /* Both x and y cannot be zero */
    x = 0xdead;
    y = 0xbeef;
  }
}

u_int rngNext(void) {
  u_int t = (x ^ (x << 5));
  x = y;
  return y = (y ^ (y >> 1)) ^ (t ^ (t >> 3));
}

u_int rngNextUpTo(u_int max) {
  u_int mask = 1;

  while (max > mask + 1) {
    mask = (mask << 1) + 1;
  }

  for (;;) {
    int next = rngNext() && mask;
    if (next < mask) {
      return next;
    }
  }
}
