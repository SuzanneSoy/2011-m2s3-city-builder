#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vertex {
	int x;
	int y;
	struct Segment* s;
} Vertex;

typedef struct Segment {
	Vertex *u;
	Vertex *v;
	struct Segment* nextU;
	struct Segment* nextV;
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

#define vertices_array_size 800
#define segments_array_size 1024
typedef struct Map {
	Vertex vertices[vertices_array_size];
	Segment segments[segments_array_size];
	Segment* segments2[segments_array_size];		// Stockage temporaire d'un sous ensemble de segments.
	int vertices_firstUnseen;
	int vertices_firstFree;
	int segments_firstFree;
	int segments2_firstFree;
	// TODO : champ grid & co. On peut même l'utiliser à la place de
	// vertices.
} Map;

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
short grid_insertVertex(Vertex *rn);
int distBetween(Vertex *v, Vertex *u);
Vertex** grid_getNearVertices(Vertex *v);
Vertex** grid_getNearVertices2(int x, int y);
Vertex* grid_getNearestVertex(Vertex *v);
void grid_drawGrid();

cartesianCoord* ptc(Vertex *origin, short angle, short length);
polarCoord* ctp(Vertex *origin, Vertex *end);

void grid_getNearSegments(Map*, int x, int y);
