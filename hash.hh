#ifndef _HASH_HH_
#define _HASH_HH_

#include "all_includes.hh"

int random_seed();

unsigned int hash2(unsigned int a, unsigned int b);
int hashInRange(int seed, int n, int a, int b); // Renvoie le n-ième nombre aléatoire dérivé de seed entre a et b (a inclus, b non inclus).
bool proba(int seed, int n, unsigned int a, unsigned int b); // Renvoie vrai avec `a` fois sur `b`.

#endif
