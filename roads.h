#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vertex {
	int x;
	int y;
} Vertex;

typedef Vertex Polygon;

/* Cette structure définie un nœd de route. Le nœd contient la liste de toute les intersections.
 */
typedef struct roadNodeY {
	Vertex *v;
	short nbIntersec;
	struct intersectionY *intersec;
} roadNodeY;

/* Définition d'une intersection. Permet de savoir quelle route est concernée par cette intersection.
 * Elle permet également de changer la navigation por parcourir une nouvelle route.
 * */
typedef struct intersectionY {
	roadNodeY roadId;			// Premier nœd de la route qui lui sert d'identifiant.
	roadNodeY *next;			// Nœd de la route juste après l'intersection.
	roadNodeY *previous;		// Nœd de la route juste avant l'intersection.
	int zIndex;					// Index sur l'axe z de la route.
} intersectionY;

typedef struct roadPointY {
	struct roadPointY *first;
	struct roadPointY *next;
	struct roadPointY *previous;
	roadNodeY *rn;
} roadPointY;

roadNodeY ****nodesGrid;
short maxSubDivision;
short maxNodesInGrid = 10;
int quarterSize = 600;

int toX(Vertex*);
int toY(Vertex*);
void grid_initNodesGrid(int size);
short grid_insertRoadNode(roadNodeY *rn);
void addRoadNode(roadPointY *rp, roadNodeY *rn);
int distBetween(Vertex *v, Vertex *u);
roadNodeY** grid_getNearNodes(roadNodeY *rn);
