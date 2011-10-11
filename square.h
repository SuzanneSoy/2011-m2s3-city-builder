// get_z()
#include "roam.h"
#include <GL/gl.h>

// QuadTree Node.
typedef struct QTNode {
	Vertex* center;
	Vertex* vertices[4];
	struct QTNode* children[4];
	struct QTNode* neighbors[4];
	// linked list across all nodes, for traversal when we display them.
	struct QTNode* nextNode;
	struct QTNode* previousNode;
	unsigned int minLOD;
	unsigned int maxLOD;
} QTNode;

QTNode* QT_example();
void QT_enumerate(QTNode* first);
void QT_split(QTNode* parent);
