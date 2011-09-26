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
	// Ajouter des champs ici.
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

int get_z(x,y) {
	return 0;
}

void triangle_split(Triangle* t) {
	if (t->baseNeighbor != NULL)
		// T and its base neighbor aren't of the same LOD.
		if (t->baseNeighbor->baseNeighbor != t)
			triangle_split(t->baseNeighbor);
	Vertex* c = (Vertex*)malloc(sizeof(Vertex));
	c->x = (t->vLeft->x + t->vRight->x) / 2;
	c->y = (t->vLeft->y + t->vRight->y) / 2;
	c->z = get_z(c->x, c->y);

	Triangle* t1 = (Triangle*)malloc(sizeof(Triangle));
	t1->vApex = c;
	t1->vLeft = t->vApex;
	t1->vRight = t->vLeft;
	t1->tLeftChild = NULL;
	t1->tRightChild = NULL;
	//                           v-- Left or right, doesn't matter.
	if (t->tParent == NULL) {
		t1->tBaseNeighbor = NULL;
	} else {
		if (t->tParent->tRightChild->tRightChild == NULL) {
			t1->tBaseNeighbor = t->tParent->tRightChild;
		} else {
			t1->tBaseNeighbor = t->tParent->tRightChild->tRightChild;
		}
	}

	Triangle* t2 = malloc(sizeof(Triangle));
	t2->vApex = c;
	t2->vLeft = t->vRight;
	t2->vRight = t->vApex;
	t2->tLeftChild = NULL;
	t2->tRightChild = NULL;
	//                          v-- Left or right, doesn't matter.
	if (t->tParent->tLeftChild->tLeftChild == NULL) {
		t2->tBaseNeighbor = t->tParent->tLeftChild;
	} else {
		t2->tBaseNeighbor = t->tParent->tLeftChild->tLeftChild;
	}
	t->tLeftChild = t1;
	t->tRightChild = t2;

	// Split tBaseNeighbor
	Triangle* tb = t->tBaseNeighbor;
	if (tb == NULL) return;

	Triangle* t1 = malloc(sizeof(Triangle));
	t1->vApex = c;
	t1->vLeft = tb->vApex;
	t1->vRight = tb->vLeft;
	t1->tLeftChild = NULL;
	t1->tRightChild = NULL;
	//                           v-- Left or right, doesn't matter.
	if (tb->tParent->tRightChild->tRightChild == NULL) {
		t1->tBaseNeighbor = tb->tParent->tRightChild;
	} else {
		t1->tBaseNeighbor = tb->tParent->tRightChild->tRightChild;
	}

	Triangle* t2 = malloc(sizeof(Triangle));
	t2->vApex = c;
	t2->vLeft = tb->vRight;
	t2->vRight = tb->vApex;
	t2->tLeftChild = NULL;
	t2->tRightChild = NULL;
	//                          v-- Left or right, doesn't matter.
	if (tb->tParent->tLeftChild->tLeftChild == NULL) {
		t2->tBaseNeighbor = tb->tParent->tLeftChild;
	} else {
		t2->tBaseNeighbor = tb->tParent->tLeftChild->tLeftChild;
	}
	tb->tLeftChild = t1;
	tb->tRightChild = t2;
}

void triangle_merge(Triangle* T) {
}
