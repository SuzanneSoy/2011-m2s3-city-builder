#include <stdio.h>
#include <math.h>

#define SIZE 1024
// best value for MAX_DETAIL is 8
#define MAX_DETAIL 8

int bsr(int x) {
	asm volatile("bsr %0, %0" : "=r" (x) : "0" (x) : "0");
	return x;
}

int random_from_rec2(int a, int b, int c) {
	b += a; // b = a + b                           // 2 bytes
	a *= b; // a = a * (a + b)                     // 2 bytes
	b ^= a; // b = (a + b) ^ (a * (a + b))         // 2 bytes
	a += 211; // a = (a * (a + b)) + 5             // 2-3 bytes ; 211 is wonderfull.
	b /= 2; // b = ((a + b) ^ (a * (a + b))) / 2   // 2 bytes
	
	if (c == 0)
//		return a >> 2;                             // 3 bytes :( , but we can do with >>1 or even without.
		return a >> 1;
	return random_from_rec2(a, b, c-1);
}

unsigned char random_from(int a, int b) {
	return (random_from_rec2(a, b, 1)) & 0xff;
}

/*	Alternate method to compute a single detail level for z.
	// This square
	z = random_from(xd, yd);
	
	// x interpolation
	zb = random_from(xd + 1, yd);
	z += ((zb-z) * (x & mask)) >> detail;
	
	// y interpolation
	zc = random_from(xd, yd + 1);
	zb = random_from(xd + 1, yd + 1);
	zc += ((zb-zc) * (x & mask)) >> detail;
	z  += ((zc-z)  * (y & mask)) >> detail;
*/
				
int get_z(int x, int y) {
	int detail, mask;
	int xd, yd;
	int z00, z01, z10, z11;
	int xm, ym, mxm, mym;
	unsigned int z, ztot;
	
	ztot = 0;
	for (detail = 0; detail < MAX_DETAIL; detail++) {
		x++; // slightly blurs vertical
		y++; // and horizontal artifacts.
		
		mask = (1<<detail) - 1;
		xd   = x >> detail;
		yd   = y >> detail;
		
		if (0 == 0) {
		// Method one
			z00 = random_from(xd + 0, yd + 0);
			z01 = random_from(xd + 0, yd + 1);
			z10 = random_from(xd + 1, yd + 0);
			z11 = random_from(xd + 1, yd + 1);
			
			xm = ((xd + 1) << detail) - x;
			ym = ((yd + 1) << detail) - y;
			mxm = (1 << detail) - xm;
			mym = (1 << detail) - ym;
			
			z = 0;
			z += z00 * xm  * ym ;
			z += z01 * xm  * mym;
			z += z10 * mxm * ym ;
			z += z11 * mxm * mym;
			
			z >>= ((detail * 2) + (MAX_DETAIL - detail));
		// Method two
		} else {		
		// Alternate method
			int zb, zc;
			// This square
			z = random_from(xd, yd);
			
			// x interpolation
			zb = random_from(xd, yd + 1);
			z += ((zb-z) * (y & mask)) >> detail;
			
			// y interpolation
			zc = random_from(xd + 1, yd);
			zb = random_from(xd + 1, yd + 1);
			zc += ((zb-zc) * (y & mask)) >> detail;
			z  += ((zc-z)  * (x & mask)) >> detail;
			
			z >>= 0;
		// Alternate method
		}
		
		// add this detail level
		ztot += z;
	}
	//x = x - MAX_DETAIL; // when using x++ and y++
	//y = y - MAX_DETAIL; // to reduce artifacts.
	
	return ztot & 0xff;
}

int main(int argc, char** argv) {
	int y;
	int x;
	fprintf(stderr, "Aide :\n");
	fprintf(stderr, "Utilisez ./simple-terrain | display pour visualiser la sortie.\n");
	fprintf(stderr, "Utilisez ./simple-terrain > fichier.pnm pour sauvegarder.\n");
        printf("P5 %d %d 255\n", SIZE, SIZE);
        for (y=SIZE-1; y>=0; y--)
                for (x=0; x<SIZE; x++)
			printf("%c", (char)get_z(x,y));
}
