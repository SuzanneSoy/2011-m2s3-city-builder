#include <stdio.h>
#include <stdlib.h>
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

typedef struct Vertex {
	int x;
	int y;
	int z;
	/* Ajouter des champs ici. */
} Vertex;

typedef struct Triangle {
	Vertex* vApex;
	Vertex* vLeft;
	Vertex* vRight;
	struct Triangle* tLeftChild;
	struct Triangle* tRightChild;
	struct Triangle* tBaseNeighbor;
	struct Triangle* tLeftNeighbor;
	struct Triangle* tRightNeighbor;
	struct Triangle* tParent;
} Triangle;

int get_z(int x, int y) {
	x = x; /* Unused */
	y = y; /* Unused */
	return 0;
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
		/* Neighbors */
		subTLeft->tBaseNeighbor = t->tLeftNeighbor;
		subTLeft->tLeftNeighbor = subTRight;
		subTLeft->tRightNeighbor = subBRight;
		/* Parent */
		subTLeft->tParent = t;
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
		/* Neighbors */
		subTRight->tBaseNeighbor = t->tRightNeighbor;
		subTRight->tLeftNeighbor = subBLeft;
		subTRight->tRightNeighbor = subTLeft;
		/* Parent */
		subTRight->tParent = t;
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
		/* Neighbors */
		subBLeft->tBaseNeighbor = b->tLeftNeighbor;
		subBLeft->tLeftNeighbor = subBRight;
		subBLeft->tRightNeighbor = subTRight;
		/* Parent */
		subBLeft->tParent = t;
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
		/* Neighbors */
		subBRight->tBaseNeighbor = b->tRightNeighbor;
		subBRight->tLeftNeighbor = subTLeft;
		subBRight->tRightNeighbor = subBLeft;
		/* Parent */
		subBRight->tParent = t;
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

int main() {
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

	triangle_split(t);
	triangle_split(t->tLeftChild);
	triangle_split(t->tLeftChild->tLeftChild);
	triangle_split(t->tLeftChild->tRightChild);
	
	return 0;
}
