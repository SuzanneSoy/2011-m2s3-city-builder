// get_z()
#include "roam.h"

#define INIT_VERTEX(v,xx,yy) do { (v)->x=(xx); (v)->y=(yy); (v)->z=get_z((xx),(yy)); } while(0);

// ROTATE4(x,r) == x+r % 4
#define ROTATE4(x,r) ((x+r) & 3)

// L'ordre dans les tableaux est toujours {ne,se,so,no} ou bien {n,e,s,o}.
typedef enum QTQuadrant { QT_NE = 0, QT_SE = 1, QT_SO = 2, QT_NO = 3 } QTQuadrant;
typedef enum QTCardinal { QT_N = 0, QT_E = 1, QT_S = 2, QT_O = 3 } QTCardinal;

#define ROT_NE (ROTATE4(QT_NE, r))
#define ROT_SE (ROTATE4(QT_SE, r))
#define ROT_SO (ROTATE4(QT_SO, r))
#define ROT_NO (ROTATE4(QT_NO, r))

#define ROT_N (ROTATE4(QT_N, r))
#define ROT_E (ROTATE4(QT_E, r))
#define ROT_S (ROTATE4(QT_S, r))
#define ROT_O (ROTATE4(QT_O, r))

// QuadTree Node.
typedef struct QTNode {
	Vertex* center;
	Vertex* vertices[4];
	struct QTNode* children[4];
	struct QTNode* neighbors[4];
} QTNode;

void QT_split(QTNode* parent) {
	// Ne pas split un noeud déjà split.
	if (parent->children[QT_NE] != NULL) return;
	
	int r;
	QTNode* q[4];
	q[0] = malloc(sizeof(QTNode));
	q[1] = malloc(sizeof(QTNode));
	q[2] = malloc(sizeof(QTNode));
	q[3] = malloc(sizeof(QTNode));

	Vertex* new_vertices[4];
	for (r = 0; r < 4; r++) {
		// réutiliser le vertex existant (parent->top_neighbor->se_child->so ou bien parent->top_neighbor->so_child->se)
		if (parent->neighbors[ROT_N] != NULL && parent->neighbors[ROT_N]->children[ROT_SE] != NULL) {
			new_vertices[ROT_N] = parent->neighbors[ROT_N]->children[ROT_SE]->vertices[ROT_SO];
		} else {
			new_vertices[ROT_N] = malloc(sizeof(Vertex));
			switch (r) { // Pourrait être factorisé, mais on y perdrait en clarté !
				case 0: INIT_VERTEX(new_vertices[0], parent->center->x, parent->children[QT_NE]->y); break;
				case 1: INIT_VERTEX(new_vertices[1], parent->children[QT_SE]->x, parent->center->y); break;
				case 2: INIT_VERTEX(new_vertices[2], parent->center->x, parent->children[QT_SO]->y); break;
				case 3: INIT_VERTEX(new_vertices[3], parent->children[QT_NO]->x, parent->center->y); break;
			}
		}
	}
	
	for (r = 0; r < 4; r++) { // Dans le corps de la boucle, positions pour le quadrant ne.
		q[ROT_NE]->center = malloc(sizeof(Vertex));
		// Coordonnées du centre de qne = moyenne du center et de parent->children[QT_NE].
		INIT_VERTEX(q[ROT_NE]->center, (parent->center->x + parent->children[ROT_NE]->x) / 2, (parent->center->y + parent->children[ROT_NE]->y) / 2);
		
		q[ROT_NE]->children[ROT_NE] = parent->children[ROT_NE];
		q[ROT_NE]->children[ROT_SE] = new_vertices[ROT_E];
		q[ROT_NE]->children[ROT_SO] = parent->center;
		q[ROT_NE]->children[ROT_NO] = new_vertices[ROT_N];

		q[ROT_NE]->children[ROT_NE] = NULL;
		q[ROT_NE]->children[ROT_SE] = NULL;
		q[ROT_NE]->children[ROT_SO] = NULL;
		q[ROT_NE]->children[ROT_NO] = NULL;

		// Si le voisin du haut de parent a un se_child, c'est le voisin du haut de qne.
		if (parent->neighbors[ROT_N] != NULL) {
			q[ROT_NE]->neighbors[ROT_N] = parent->neighbors[ROT_N]->children[ROT_SE];
			if (parent->neighbors[ROT_N]->children[ROT_SE] != NULL)
				parent->neighbors[ROT_N]->children[ROT_SE]->neighbors[ROT_S] = q[ROT_NE];
		} else {
			q[ROT_NE]->neighbors[ROT_N] = NULL;
		}
		// Si le voisin de droite de parent a un no_child, c'est le voisin de droite de qne.
		if (parent->neighbors[ROT_E] != NULL) {
			q[ROT_NE]->neighbors[ROT_E] = parent->neighbors[ROT_E]->children[ROT_NO];
			if (parent->neighbors[ROT_E]->children[ROT_NO] != NULL)
				parent->neighbors[ROT_E]->children[ROT_NO]->neighbors[ROT_O] = q[ROT_NE];
		} else {
			q[ROT_NE]->neighbors[ROT_E] = NULL;
		}
		q[ROT_NE]->neighbors[ROT_S] = q[ROT_SE];
		q[ROT_NE]->neighbors[ROT_O] = q[ROT_NO];
		
		parent->children[ROT_NE] = q[ROT_NE];
	}
}

void QT_merge(QTNode* parent) {
	// Ne pas merge un noeud sans enfants.
	if (parent->children[QT_NE] == NULL) return;
	
	int r;
	for (r = 0; r < 4; r++) {
		QT_merge(parent->children[ROT_NE]);
		parent->children[ROT_NE] = NULL;
		// reset à NULL les voisins qui pointaient vers des enfants.
		if (parent->neighbors[ROT_N] != NULL)
			if (parent->neighbors[ROT_N]->children[ROT_SE] != NULL)
				parent->neighbors[ROT_N]->children[ROT_SE]->neighbors[ROT_S] = NULL;
		if (parent->neighbors[ROT_E] != NULL)
			if (parent->neighbors[ROT_E]->children[ROT_NO] != NULL)
				parent->neighbors[ROT_E]->children[ROT_NO]->neighbors[ROT_O] = NULL;
	}
}

QTNode QT_baseNode() {
	QTNode* q = malloc(sizeof(QTNode));
	Vertex** v = malloc(sizeof(Vertex)*5);
	INIT_VERTEX(v[0], 0, 0);
	INIT_VERTEX(v[1], +1024, +1024);
	INIT_VERTEX(v[2], +1024, -1024);
	INIT_VERTEX(v[3], -1024, -1024);
	INIT_VERTEX(v[4], -1024, +1024);
	q->center = v[0];
	q->children[QT_NE] = v[1];
	q->children[QT_SE] = v[2];
	q->children[QT_SO] = v[3];
	q->children[QT_NO] = v[4];
	return q;
}

QTNode* QT_example() {
	QTNode* q = QT_baseNode();
	return q;
}
