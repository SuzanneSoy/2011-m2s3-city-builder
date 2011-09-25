/* Triangle T (apex,v₀, v₁)
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

typedef struct Triangle {
	Vertex vCenter;
	struct Triangle* tLeftChild;
	struct Triangle* tRightChild;
} Triangle;

/* typedef struct FullTriangle { */
/* 	Triangle* self; */
/* 	Vertex* vApex; */
/* 	Vertex* vLeft; */
/* 	Vertex* vRight; */
/* 	Triangle* tLeftNeighbor; */
/* 	Triangle* tRightNeighbor; */
/* 	Triangle* tBaseNeighbor; */
/* } FullTriangle; */

typedef enum bool {
	TRUE = (0==0),
	FALSE = (0==1)
} bool;

typedef struct TraversalStep {
	bool isLeftChild; // Can be stored inside a pointer (last two bits).
	Vertex* discarded;
	Triangle* triangle;
} TraversalStep;

typedef struct Traversal {
	int current;
	TraversalStep recursion[256]; // == max recursion depth.
}

void triangle_split(Triangle* T) {
	if (base(T) is not of same level)
		triangle_split(base(T));
	T->vCenter = get_z(coordonnées du centre (calculer en fonction du niveau de détail de la grille et ^2));
	parent->thischild = create the triangle.
}

void triangle_merge(Triangle* T) {
}

inline Vertex* triangle_getVCenter(Triangle* T) {
	return &(T->vCenter);
}

inline Vertex* triangle_getVApex(Triangle* T) {
	return triangle_getVCenter(parent);
}

inline Vertex* triangle_getVLeft(Triangle* T) {
	return (parent->tLeftChild == T) ? triangle_getVApex(parent) : triangle_getVRight(parent);
}

inline Vertex* triangle_getVRight(Triangle* T) {
	return (parent->tLeftChild != T) ? triangle_getVApex(parent) : triangle_getVLeft(parent);
}

inline Triangle* triangle_getTBaseNeighbor(Triangle* T) {
	gp = T->parent->parent;
	if (gp->right == T) {
		return isDivided(gp->left) ? gp->left->left : gp->left;
	} else {
		return isDivided(gp->right) ? gp->right->right : gp->right;
	}
}

inline Triangle* triangle_getTLeftNeighbor(Triangle* T) {
	Triangle p = T->parent;
	if (p->right == T) {
		return isDivided(p->left) ? p->left->left : p->left;
	} else {
		return isDivided(p->right) ? p->right->right : p->left;
	}
}

inline Triangle* triangle_getTRightNeighbor(Triangle* T) {
	// same as triangle_getTLeftNeighbor, so it's wrong !
	Triangle p = T->parent;
	if (p->left == T) {
		return isDivided(p->left) ? p->left->left : p->left;
	} else {
		return isDivided(p->right) ? p->right->right : p->left;
	}
}

inline Triangle* triangle_getTLeftChild(Triangle* T) {
	return T->tLeftChild;
}

inline Triangle* triangle_getTRightChild(Triangle* T) {
	return T->tRightChild;
}

inline Triangle* triangle_getTParent(Triangle* T) {
}
