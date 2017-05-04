#ifndef RANDOM_INCLUDED
#define RANDOM_INCLUDED

void rngSeedSram(void);
void rngSeedTimer(void);
u_int rngNext(void);
u_int rngNextUpTo(u_int max);

#endif /* RANDOM_INCLUDED */
