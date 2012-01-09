#ifndef _HASH_HH_
#define _HASH_HH_

#include "all_includes.hh"

int random_seed();

unsigned int hash2(unsigned int a, unsigned int b);
float floatInRange(int seed, int n, float a, float b); // Renvoie le n-ième nombre aléatoire dérivé de seed entre a et b (a inclus, b non inclus).
bool proba(int seed, int n, unsigned int a, unsigned int b); // Renvoie vrai avec `a` fois sur `b`.
typedef union FloatUIntUnion {
	float f;
	unsigned int ui;
} FloatUIntUnion;
unsigned int float2uint(float f);

#endif
