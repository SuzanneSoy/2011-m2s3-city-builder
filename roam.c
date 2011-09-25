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
	int z;
	// Ajouter des champs ici.
} Vertex;

/* Normalement, cette structure suffit, les autres champs sont
 * récupérables autrement. */
// typedef struct Triangle {
// 	Vertex vCenter;
// 	struct Triangle* tLeftChild;
// 	struct Triangle* tRightChild;
// } Triangle;

typedef struct Triangle {
	Vertex vCenter;
	struct Triangle* tLeftChild;
	struct Triangle* tRightChild;
} Triangle;

int get_z(x,y) {
	return 0;
}

Triangle* triangle_new() {
	Triangle* t = malloc(sizeof(Triangle));
	// TODO
	return t;
}

void triangle_split(Triangle* t) {
	if (t->baseNeighbor != NULL)
		// T and its base neighbor aren't of the same LOD.
		if (t->baseNeighbor->baseNeighbor != t)
			triangle_split(t->baseNeighbor);
	Vertex c = {
		// coordonnées du centre (calculer en fonction du niveau de détail de la grille et ^2)
		.z = get_z(42, 42)
	};
	t->tLeftChild = triangle_new();
	t->tRightChild = triangle_new();
	// TODO : couper t->baseNeighbor en deux aussi.
}

void triangle_merge(Triangle* T) {
}
