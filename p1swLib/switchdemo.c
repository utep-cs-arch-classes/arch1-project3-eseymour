#include <msp430.h>
#include <sr.h>
#include "p1switches.h"
#define RED_LED BIT0

int
main()
{
  p1sw_init(0x8);
  or_sr(0x8);			/* GIE (enable interrupts) */

  P1DIR |= RED_LED;
  for(;;) {
    P1OUT = (0x8 & p1sw_read()) >> 3;
  }
}

