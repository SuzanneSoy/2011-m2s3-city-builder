#include "roam.h"
#include "hash.h"

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

// renvoie un z entre 0 et 255
int get_z(int x, int y) {
	x = x; /* Unused */
	y = y; /* Unused */
	int z = 0;
	int level;
	int maxlevel = 6;
	for (level = maxlevel; level >= 0; level--) {
		int step = (1 << level);
		int mask = step - 1;
		int zmax = 2*step - 1;
		int x1 = x & ~mask;
		int y1 = y & ~mask;
		int x2 = x1 + step;
		int y2 = y1 + step;
		z += interpolation(x, y, x1, y1, x2, y2, hash3(level, x2, y1) & zmax, hash3(level, x2, y2) & zmax, hash3(level, x1, y2) & zmax, hash3(level, x1, y1) & zmax);
	}
	// ici le résultat est entre 0 (inclus) et 2^(2+maxlevel) (non inclus)
	// On normalise sur [0,256[ sachant que 256 == 2^8.
	if (maxlevel > 6)
		z = z >> (-6+maxlevel);
	else if (maxlevel != 6)
		z = z << (6-maxlevel);
	return z;
}

void triangle_split(Triangle* t) {
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

void recursiveSplit(Triangle* t, int n) {
	if (n == 0) return;
	if (t->tLeftChild == NULL) { // t is not already split
		triangle_split(t);
	}
	recursiveSplit(t->tLeftChild, n-1);
	recursiveSplit(t->tRightChild, n-1);
}

Triangle* initDefaultExample() {
	Triangle* t = (Triangle*)malloc(sizeof(Triangle));
	Vertex* vApex = (Vertex*)malloc(sizeof(Vertex));
	Vertex* vLeft = (Vertex*)malloc(sizeof(Vertex));
	Vertex* vRight = (Vertex*)malloc(sizeof(Vertex));
	
	vApex->x  = 256; vApex->y  = 256; vApex->z  = get_z(256,256);
	vLeft->x  = 0;    vLeft->y  = 0;    vLeft->z  = get_z(0,0);
	vRight->x = 512; vRight->y = 0;    vRight->z = get_z(512,0);
	
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
