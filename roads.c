#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
	int x;
	int y;
} Vertex;

typedef Vertex Polygon;

void svg_start(int w, int h) {
	printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">", w, h);
}

void svg_end() {
	printf("</svg>");
}

void svg_line(Vertex* a, Vertex* b) {
	printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" />", a->x, a->y, b->x, b->y);
}

void roads(Polygon* quartier) {
	quartier = quartier;
	Vertex center = { .x=400, .y=300 };
	svg_line(&center, &(quartier[0]));
}


/* Fonctions de Yoann suffixée par "Y" */

/* La route est constituée d'une série de points, chaque point contient un nœd de route qui peut-être propre à cette route comme
 * appartenir à plusieurs routes. Le nœd contient un Vertex qui permet de le positionner sur la carte. Il contient également
 * le nombre et les portions de routes auxquelles il appartient.
 */

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

const int maxSubDivision = 6;	// Nombre de subdivisions max en hauteur et largeur.

// TODO Fusionner les deux fonctions et retourner une paire de valeurs.
// Transforme des coordonnées du plan en coordonées du tableau sur x.
int toX(int x) {
	return x/maxSubDivision;
}

// Transforme des coordonnées du plan en coordonées du tableau sur y.
int toY(int y) {
	return y/maxSubDivision;
}

void addRoadNode(roadPointY *rp, roadNodeY *rn) {
	if(rp->rn == NULL) {
		rp->next = NULL;
		rp->rn = rn;
		return;
	}
	while(rp->next != NULL)
		rp = rp->next;
		
	roadPointY *rpp = (roadPointY*) malloc(sizeof(roadPointY));
	rpp->next = NULL;
	rpp->rn = rn;
	rp->next = rpp;
}

void carreY() {
	roadNodeY ***nodesGrid = (roadNodeY***) malloc(sizeof(roadNodeY**)*maxSubDivision);
	int i = 0;
	int j = 0;
	int size = 500;
	for(i=0;i<maxSubDivision;i++) {
		nodesGrid[i] = (roadNodeY**) malloc(sizeof(roadNodeY*)*maxSubDivision);
		for(j=0;j<maxSubDivision;j++) {
			nodesGrid[i][j] = NULL;
		}
	}
	
	roadPointY *roada = (roadPointY*) malloc(sizeof(roadPointY));
	roadPointY *roadb = (roadPointY*) malloc(sizeof(roadPointY));
	roadNodeY *rn;
	Vertex *v;
	roadNodeY *common = NULL;
	
	for(i=0;i<40;i++) {
		rn = (roadNodeY*)malloc(sizeof(roadNodeY));
		v = (Vertex*) malloc(sizeof(Vertex));
		
		v->x = (i+1)*16;
		v->y = ((i+1)%3)*(61%(i+1))+100;
		rn->v = v;
		if(i == 18) common = rn;
		addRoadNode(roada,rn);
	}
	
	for(i=0;i<40;i++) {
		rn = (roadNodeY*)malloc(sizeof(roadNodeY));
		v = (Vertex*) malloc(sizeof(Vertex));
		
		v->x = (i+1)*22;
		v->y = ((i+1)%5)*(61%(i+2))+160;
		rn->v = v;
		if(i == 12) rn = common;
		addRoadNode(roadb,rn);
	}
	
	roadPointY *rd = roada;
	while(rd->next != NULL) {
		svg_line(rd->rn->v,rd->next->rn->v);
		
		rd = rd->next;
	}
	
	rd = roadb;
	while(rd->next != NULL) {
		svg_line(rd->rn->v,rd->next->rn->v);
		
		rd = rd->next;
	}
	
	size=size;
}

int main() {
	Vertex points[] = {
		{ .x=10, .y=10 },
		{ .x=790, .y=10 },
		{ .x=600, .y=300 },
		{ .x=790, .y=590 },
		{ .x=10, .y=590 },
	};
	int n = 5;
	svg_start(800,600);
	carreY();
	//int i;
	//for (i = 0; i < n; i++) {
//		svg_line(&(points[i]), &(points[(i+1)%n]));
//	}
n=n;
	//roads(points);
	points[0] = points[0];
	svg_end();
	return 0;
}
