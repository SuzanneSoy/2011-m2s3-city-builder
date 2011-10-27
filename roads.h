#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vertex {
	int x;
	int y;
} Vertex;

typedef struct Segment {
	Vertex *u;
	Vertex *v;
} Segment;

typedef Vertex Polygon;

/* Cette structure définie un nœd de route. Le nœd contient la liste de toute les intersections.
 */
typedef struct roadNodeY {
	Vertex *v;
	short nbIntersec;
	struct intersectionY **intersec;
} roadNodeY;

typedef struct roadPointY {
	struct roadPointY *first;
	struct roadPointY *next;
	struct roadPointY *previous;
	roadNodeY *rn;
} roadPointY;

/* Définition d'une intersection. Permet de savoir quelle route est concernée par cette intersection.
 * Elle permet également de changer la navigation por parcourir une nouvelle route.
 * */
typedef struct intersectionY {
	roadPointY *roadId;			// Premier point de la route qui lui sert d'identifiant.
	roadNodeY *next;			// Nœd de la route juste après l'intersection.
	roadNodeY *previous;		// Nœd de la route juste avant l'intersection.
	int zIndex;					// Index sur l'axe z de la route.
} intersectionY;

typedef struct cartesianCoord {
	int x;			// Coordonnées sur x.
	int y;			// Coordonnées sur y.
} cartesianCoord;

typedef struct polarCoord {
	int angle;		// Angle en degrès.
	int length;		// Norme du vecteur.
} polarCoord;

typedef struct roadSet {
	roadPointY *roadId;		// Identifiant de la route.
	roadPointY *rpc; 		// Nœd courrant.
} roadStep;


Vertex ****vGrid;
roadPointY **roadsList;
short nbXSubDivision;
short nbYSubDivision;
short maxSegmentSize;
short maxNodesInGrid = 16;
int quarterWidth;
int quarterHeight;

int toX(Vertex*);
int toY(Vertex*);
void grid_initNodesGrid(int w, int h, int maxSegmentSize);
short grid_insertRoadNode(roadNodeY *rn);
int distBetween(Vertex *v, Vertex *u);
roadNodeY** grid_getNearNodes(Vertex *v);
roadNodeY** grid_getNearNodes2(int x, int y);
roadNodeY* grid_getNearestRoadNode(Vertex *v);
void grid_drawGrid();
cartesianCoord* ptc(Vertex *origin, short angle, short length);
polarCoord* ctp(Vertex *origin, Vertex *end);
Segment** grid_getNearSegments(int x, int y);
