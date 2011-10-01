#include "roam.h"

/* Implémentation de ROAM
 * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.22.1811&rep=rep1&type=pdf
 *
 * Triangle T (apex, vLeft, vRight)
 *               . vApex
 *              /|\
 *             / | \
 * tLeftChild / 90° \ tRightChild
 *           /   |   \
 *          / 45°|45° \
 *   vLeft ._____._____. vRight
 *            vCenter
 *
 * Le triangle T contient le champ `vCenter`, qui permet de construire
 * ses sous-triangles tLeftChild (vCenter, vApex, vLeft) et
 * tRightChild (vCenter, vRight, vApex), du moment qu'on connait
 * vApex, vLeft et vRight quand on manipule T. On les connaît car on a
 * traversé récursivement ses triangles parents avant d'y arriver.
 *
 * T est le tParent de tLeftChild et tRightChild.
 *
 * Voisins :
 *
 * Le tBaseNeighbor de T est le triangle en-dessous, qui partage son
 * côté (vLeft,vRight).
 *
 * Le tLeftNeighbor de T est le triangle à gauche, qui partage son
 * côté (vApex,vLeft).
 *
 * Le tRightNeighbor de T est le triangle à droite, qui partage son
 * côté (vApex,vRight).
 *
 */
 

/* Permet de récupérer la taille de la base du triangle (hypoténuse).*/
// TODO Optimisze la fonction pour éviter la racine carée.
int getFirstTriangleSize(Triangle* t) {
	return sqrt(((t->vRight->x - t->vLeft->x)^2) + ((t->vRight->y - t->vLeft->y)^2));
}

// TODO : à supprimer.
unsigned int getValueForSeed(unsigned int seed) {
	unsigned int primeA = 65521; // Plus grand premier < 2^16
	unsigned int primeB = 4294967291U; // Plus grand premier < 2^32
	return ((seed * primeA) ^ ((seed+1) * primeB)) + seed; // + seed pour éviter d'avoir uniquement des nombres impairs.
}

// Donne des mauvais résultats (en faisant & 0xff…, on obtient des valeurs répétitives).
/* unsigned int hash2(unsigned int a, unsigned int b) { */
/* 	unsigned int primeA = 65521; // Plus grand premier < 2^16 */
/* 	unsigned int primeB = 4294967291U; // Plus grand premier < 2^32 */
/* 	return ((a * primeA) + (b * primeB) + a + 43) ^ ((a * primeB) + (b * primeA) + b + 57); */
/* } */

int hash2(int a, int b) {
	int i;
	for (i = 0; i < 5; i++) { // repeat five times
		b += a; // b = a + b
		a *= b; // a = a * (a + b)
		b ^= a; // b = (a + b) ^ (a * (a + b))
		a += 211; // a = (a * (a + b)) + 5
		b /= 2; // b = ((a + b) ^ (a * (a + b))) / 2
	}
	return (a >> 3); // high bits are never set…
}

// Un hachage certes un peu primaire mais bon…
unsigned int hash(unsigned int seed, int x, int y) {
	return hash2(seed,hash2(x, y));
}

/* Interpolation linéaire entre deux points.
 * (x,y) est le point dont on veut connaître la valeur
 * (x1,y1)--(x2,y2) est le carré dont on connaît les valeurs
 * ne,se,so,no sont les valeurs aux coins nord/sud-est/ouest du carré. */
// A optimiser par aproximation.
// Optimiser aussi le fait que la distance entre xy1 et xy2 est une puissance de 2, donc on peut faire un simple décalage.
// Peut être réalisé par une multiplication de matrice (donc sur le GPU) : http://en.wikipedia.org/wiki/Bilinear_interpolation
int interpolation(int x, int y, int x1, int y1, int x2, int y2, int ne, int se, int so, int no) {
	int ret = 0;
	// on multiplie chaque coin par la superficie du rectangle formé par (x,y) et ce coin.
	ret += so * (x2-x) * (y-y1);
	ret += no * (x2-x) * (y2-y);
	ret += ne * (x-x1) * (y2-y);
	ret += se * (x-x1) * (y-y1);
	return ret / ((x2-x1) * (y2-y1));
}

short** PerlinNoise(Triangle* t) {
	short **values;
	int triangleSize = getFirstTriangleSize(t);
	int i;
	int seed;
	int x,y;
	
	seed = (int)(t->vApex->x / triangleSize + t->vApex->y / triangleSize)*1111;
	
	values = (short**) malloc(sizeof(short*)*triangleSize);
	for(i=0; i<triangleSize;i++)
		values[i] = (short*) malloc(sizeof(short)*triangleSize);
	
	for(i=0; i<8;i++) {
		x = getValueForSeed(seed);
		y = getValueForSeed(x);
		values[x][y] = 255;
	}
	
	// TODO Yoann : tout le reste.
	return values;
}

// renvoie un z entre 0 et 255
int get_z(int x, int y) {
	unsigned int seed = 45;
	x = x; /* Unused */
	y = y; /* Unused */
	int z = 0;
	int level;
	int maxlevel = 7;
	for (level = maxlevel; level > 0; level--) {
		int step = (1 << level);
		int mask = step - 1;
		int zmax = mask;
		int x1 = x & ~mask;
		int y1 = y & ~mask;
		int x2 = x1 + step;
		int y2 = y1 + step;
		z += interpolation(x, y, x1, y1, x2, y2, hash(seed, x2, y1) & zmax, hash(seed, x2, y2) & zmax, hash(seed, x1, y2) & zmax, hash(seed, x1, y1) & zmax);
		//fprintf(stderr, "x=%d y=%d x1=%d y1=%d x2=%d y2=%d hash(seed, x2, y1)=%d ans&zmax=%d\n", x, y, x1, y1, x2, y2, hash(seed, x2, y1), hash(seed, x2, y1) & zmax);
		//break;
	}
	// ici le résultat est entre 0 (inclues) et 2^(1+maxlevel) (non inclus)
	// On normalise sur [0,256[ sachant que 256 == 2^8
	if (maxlevel > 7)
		z = z >> (-7+maxlevel);
	else if (maxlevel != 7)
		z = z << (7-maxlevel);
	return z;
}

void triangle_split(Triangle* t) {
	printf("split (%d,%d) (%d,%d) (%d,%d)\n", t->vLeft->x, t->vLeft->y, t->vRight->x, t->vRight->y, t->vApex->x, t->vApex->y);
	Triangle* b; /* base neighbor */
	Vertex* c; /* center vertex */
	Triangle* subTLeft;
	Triangle* subTRight;
	Triangle* subBLeft;
	Triangle* subBRight;

	b = t->tBaseNeighbor;
	if (b != NULL)
		if (b->tBaseNeighbor != t)
			/* T and its base neighbor aren't of the same LOD. */
			triangle_split(b);
	b = t->tBaseNeighbor;

	c = (Vertex*)malloc(sizeof(Vertex));
	c->x = (t->vLeft->x + t->vRight->x) / 2;
	c->y = (t->vLeft->y + t->vRight->y) / 2;
	c->z = get_z(c->x, c->y);

	subTLeft = (Triangle*)malloc(sizeof(Triangle));
	subTRight = (Triangle*)malloc(sizeof(Triangle));
	if (b != NULL) {
		subBLeft = (Triangle*)malloc(sizeof(Triangle));
		subBRight = (Triangle*)malloc(sizeof(Triangle));
	} else {
		subBLeft = NULL;
		subBRight = NULL;
	}

	/* subTLeft */
	{
		/* Vertices */
		subTLeft->vApex = c;
		subTLeft->vLeft = t->vApex;
		subTLeft->vRight = t->vLeft;
		/* Children */
		subTLeft->tLeftChild = NULL;
		subTLeft->tRightChild = NULL;
		/* To neighbors */
		subTLeft->tBaseNeighbor = t->tLeftNeighbor;
		subTLeft->tLeftNeighbor = subTRight;
		subTLeft->tRightNeighbor = subBRight;
		/* Parent */
		subTLeft->tParent = t;
		/* From neighbors */
		if (t->tLeftNeighbor != NULL) {
			if (t->tLeftNeighbor->tBaseNeighbor == t) {
				t->tLeftNeighbor->tBaseNeighbor = subTLeft;
			} else {
				t->tLeftNeighbor->tRightNeighbor = subTLeft;
			}
		}
	}
	/* subTRight */
	{
		/* Vertices */
		subTRight->vApex = c;
		subTRight->vLeft = t->vRight;
		subTRight->vRight = t->vApex;
		/* Children */
		subTRight->tLeftChild = NULL;
		subTRight->tRightChild = NULL;
		/* To neighbors */
		subTRight->tBaseNeighbor = t->tRightNeighbor;
		subTRight->tLeftNeighbor = subBLeft;
		subTRight->tRightNeighbor = subTLeft;
		/* Parent */
		subTRight->tParent = t;
		/* From neighbors */
		if (t->tRightNeighbor != NULL) {
			if (t->tRightNeighbor->tBaseNeighbor == t) {
				t->tRightNeighbor->tBaseNeighbor = subTRight;
			} else {
				t->tRightNeighbor->tLeftNeighbor = subTRight;
			}
		}
	}
	/* subBLeft */
	if (b != NULL) {
		/* Vertices */
		subBLeft->vApex = c;
		subBLeft->vLeft = b->vApex;
		subBLeft->vRight = t->vRight; /* == b->vLeft, mais a plus de chances d'être dans le cache, non ? */
		/* Children */
		subBLeft->tLeftChild = NULL;
		subBLeft->tRightChild = NULL;
		/* To neighbors */
		subBLeft->tBaseNeighbor = b->tLeftNeighbor;
		subBLeft->tLeftNeighbor = subBRight;
		subBLeft->tRightNeighbor = subTRight;
		/* Parent */
		subBLeft->tParent = t;
		/* From neighbors */
		if (b->tLeftNeighbor != NULL) {
			if (b->tLeftNeighbor->tBaseNeighbor == b) {
				b->tLeftNeighbor->tBaseNeighbor = subBLeft;
			} else {
				b->tLeftNeighbor->tRightNeighbor = subBLeft;
			}
		}
	}
	/* subBRight */
	if (b != NULL) {
		/* Vertices */
		subBRight->vApex = c;
		subBRight->vLeft = t->vLeft; /* == b->vRight, mais a plus de chances d'être dans le cache, non ? */
		subBRight->vRight = b->vApex;
		/* Children */
		subBRight->tLeftChild = NULL;
		subBRight->tRightChild = NULL;
		/* To neighbors */
		subBRight->tBaseNeighbor = b->tRightNeighbor;
		subBRight->tLeftNeighbor = subTLeft;
		subBRight->tRightNeighbor = subBLeft;
		/* Parent */
		subBRight->tParent = t;
		/* From neighbors */
		if (b->tRightNeighbor != NULL) {
			if (b->tRightNeighbor->tBaseNeighbor == b) {
				b->tRightNeighbor->tBaseNeighbor = subBRight;
			} else {
				b->tRightNeighbor->tLeftNeighbor = subBRight;
			}
		}
	}
	t->tLeftChild = subTLeft;
	t->tRightChild = subTRight;
	if (b != NULL) {
		b->tLeftChild = subBLeft;
		b->tRightChild = subBRight;
	}
}

void triangle_merge(Triangle* t, Triangle* b) {
	t = t;
	b = b;
	/* TODO : free récursivement les triangles… Peut-être pas
	 * nécessaire vu qu'on peut les garbage-collecter en quelque sorte
	 * lorsqu'on envoie tous les triangles à la carte (on verra ceux
	 * qu'on n'envoie pas).
	 */
	t->tLeftChild = NULL;
	t->tRightChild = NULL;
	b->tLeftChild = NULL;
	b->tRightChild = NULL;
}

/* TODO : MinMax Heap : http://www.diku.dk/forskning/performance-engineering/Jesper/heaplab/heapsurvey_html/node11.html
 * TODO : flexible memory usage : http://www.diku.dk/forskning/performance-engineering/Jesper/heaplab/heapsurvey_html/node15.html
 * TODO : pour l'instant les comparaisons se font sur les adresses !
 */

/* Index des éléments du tas dans le tableau de stockage.
 *        0
 *    1       2
 *  3   4   5   6
 * 7 8 9 . . . . .
 */

#define HEAP_PARENT(x) (((x)-1)/2)
#define HEAP_LEFT_CHILD(x) ((x)*2+1)
#define HEAP_RIGHT_CHILD(x) ((x)*2+2)
#define SWAP(type, a, b) do { type SWAP_temp = (a); (a) = (b); (b) = SWAP_temp; } while (0)
/* Insère `node` dans `heap`.
 * @param n : nombre de `node`s déjà dans le `heap`.
 */
void maxheap_insert(Triangle** heap, Triangle* node, unsigned int n) {
	heap[n] = node;
	unsigned int x = n;
	while (x != 0 && heap[x] > heap[HEAP_PARENT(x)]) {
		SWAP(Triangle*, heap[x], heap[HEAP_PARENT(x)]);
	}
}

/* Récupère le plus grand élément de `heap`.
 * @param n : nombre de `node`s déjà dans le `heap`.
 */
Triangle* maxheap_pop_max(Triangle** heap, unsigned int n) {
	Triangle* ret = heap[0];
	heap[0] = heap[n];
	unsigned int x = 0;
	while (x != n &&
		   (heap[x] < heap[HEAP_LEFT_CHILD(x)] || heap[x] < heap[HEAP_RIGHT_CHILD(x)])) {
		if (heap[HEAP_LEFT_CHILD(x)] > heap[HEAP_RIGHT_CHILD(x)]) {
			SWAP(Triangle*, heap[x], heap[HEAP_LEFT_CHILD(x)]);
		} else {
			/* échanger right et x */
			SWAP(Triangle*, heap[x], heap[HEAP_RIGHT_CHILD(x)]);
		}
	}
	return ret;
}

// t must not already be split !
void recursiveSplit(Triangle* t, int n) {
	if (n == 0) return;
	triangle_split(t);
	recursiveSplit(t->tLeftChild, n-1);
	recursiveSplit(t->tRightChild, n-1);
}

Triangle* initDefaultExample() {
	Triangle* t = (Triangle*)malloc(sizeof(Triangle));
	Vertex* vApex = (Vertex*)malloc(sizeof(Vertex));
	Vertex* vLeft = (Vertex*)malloc(sizeof(Vertex));
	Vertex* vRight = (Vertex*)malloc(sizeof(Vertex));
	
	vApex->x  = 1024; vApex->y  = 1024; vApex->z  = 0;
	vLeft->x  = 0;    vLeft->y  = 0;    vLeft->z  = 0;
	vRight->x = 2048; vRight->y = 0;    vRight->z = 0;
	
	t->vApex = vApex;
	t->vLeft = vLeft;
	t->vRight = vRight;
	t->tLeftChild = NULL;
	t->tRightChild = NULL;
	t->tBaseNeighbor = NULL;
	t->tLeftNeighbor = NULL;
	t->tRightNeighbor = NULL;
	t->tParent = NULL;
	
	recursiveSplit(t, 10);
	/* triangle_split(t); */
	/* triangle_split(t->tLeftChild); */
	/* triangle_split(t->tLeftChild->tLeftChild); */
	/* triangle_split(t->tLeftChild->tRightChild); */
	
	return t;
}
