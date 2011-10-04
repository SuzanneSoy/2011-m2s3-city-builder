// get_z()
#include "roam.h"

#define INIT_VERTEX(v,xx,yy) do { (v)->x=(xx); (v)->y=(yy); (v)->z=get_z((xx),(yy)); } while(0);

// QuadTree Node.
typedef struct QTNode {
	Vertex* center;
	Vertex* ne;
	Vertex* se;
	Vertex* so;
	Vertex* no;
	struct QTNode* ne_child;
	struct QTNode* se_child;
	struct QTNode* so_child;
	struct QTNode* no_child;
} QTNode;

typedef enum QTQuadrant {
	QT_NE,
	QT_SE,
	QT_SO,
	QT_NO,
} QTQuadrant;

void QT_split(QTNode* parent, QTQuadrant quadrant) {
	if (quadrant == QT_NE) {
		q = malloc(sizeof(QTNode));
		
		q->center = malloc(sizeof(Vertex));
		INIT_VERTEX(q->center, (parent->ne->x + parent->so->x) / 2, (parent->ne->y + parent->so->y) / 2);
		
		q->ne = parent->ne;
		
		q->se = malloc(sizeof(Vertex)); // TODO : réutiliser le vertex existant s'il y en a un.
		INIT_VERTEX(q->se, parent->ne->x, (parent->ne->y + parent->so->y) / 2);
		
		q->so = parent->center;
		
		q->no = malloc(sizeof(Vertex)); // TODO : réutiliser le vertex existant s'il y en a un.
		INIT_VERTEX(q->no, (parent->ne->x + parent->so->x) / 2, parent->ne->y);
		
		parent->ne_child = q;
	}
}

QTNode* QT_example() {
	QTNode* q = malloc(sizeof(QTNode));
	Vertex** v = malloc(sizeof(Vertex)*5);
	INIT_VERTEX(v[0], 0, 0);
	INIT_VERTEX(v[1], +1024, +1024);
	INIT_VERTEX(v[2], +1024, -1024);
	INIT_VERTEX(v[3], -1024, -1024);
	INIT_VERTEX(v[4], -1024, +1024);
	q->center = v[0];
	q->ne = v[1];
	q->se = v[2];
	q->so = v[3];
	q->no = v[4];
	return q;
}
