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
	Vertex* c = malloc(sizeof(Vertex));
	c->x = (t->vLeft->x + t->vRight->x) / 2;
	c->y = (t->vLeft->y + t->vRight->y) / 2;
	c->z = get_z(c->x, c->y);

	t2 = malloc(sizeof(Triangle));
	t2->vApex = c;
	t2->vLeft = t->vRight;
	t2->vRight = t->vApex;
	t2->tLeftChild = NULL;
	t2->tRightChild = NULL;
	// Attention aux NULL
	Triangle* parent = t->tParent;*
	//                          v-- Left or right, doesn't matter.
	if (t->tParent->tLeftChild->tLeftChild == NULL) {
		t2->tBaseNeighbor = t->tParent->tLeftChild;
	} else {
		t2->tBaseNeighbor = t->tParent->tLeftChild->tLeftChild;
	}
	t->tLeftChild = t1;
	t->tRightChild = t2;
	// TODO : couper t->baseNeighbor en deux aussi.
}

void triangle_merge(Triangle* T) {
}
