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
/* Cette structure définie un noad de route. Les champs next et previous permettent d'avancer
 * ou de reculler sur la route tant que l'on ne rencontre pas d'intersections avec une ou 
 * plusieurs autre routes. Dans ce dernier cas next er previous se retrouvent à NULL.
 */
typedef struct roadNodeY {
	Vertex *v;
	struct roadNodeY *next;
	struct roadNodeY *previous;
	short nbIntersec;
	struct intersection *intersec;
} roadNodeY;

/* Définition d'une intersection. Permet de savoir quelle route est concernée par cette intersection.
 * Elle permet également de changer la navigation por parcourir une nouvelle route.
 * */
typedef struct intersection {
	roadNodeY roadId;			// Premier nœd de la route qui lui sert d'identifiant.
	roadNodeY *next;			// Nœd de la route juste après l'intersection.
	roadNodeY *previous;		// Nœd de la route juste avant l'intersection.
	int zIndex;					// Index sur l'axe z de la route.
} intersection;

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

void carreY() {
	roadNodeY ***nodesGrid = (roadNodeY***) malloc(sizeof(roadNodeY**)*maxSubDivision);
	int i = 0;
	int j = 0;
	int size = 500;
	for(i=0;i<maxSubDivision;i++) {
		nodesGrid[i] = (roadNodeY**) malloc(sizeof(roadNodeY*)*maxSubDivision);
		for(j=0;j<maxSubDivision;j++) {
			roadNodeY *rn = (roadNodeY*) malloc(sizeof(roadNodeY));
			rn->v = (Vertex*) malloc(sizeof(Vertex));
			rn->v->x = i*size/maxSubDivision;
			rn->v->y = j*size/maxSubDivision;
			rn->next = NULL;
			rn->previous = NULL;
			nodesGrid[i][j] = rn;
		}
	}
	
	int a,b;
	for(i=0;i<maxSubDivision;i++) {
		for(j=0;j<maxSubDivision;j++) {
			roadNodeY *rn = nodesGrid[i][j];
			while(rn != NULL) {
				for(a=i-1;a<=i+1;a++) {
					for(b=j-1;b<=j+1;b++) {
						if(a >= 0 && a < maxSubDivision && b >= 0 && b < maxSubDivision) {
							svg_line(rn->v,nodesGrid[a][b]->v);
						}
					}
				}
				rn = NULL;
			}
		}
	}
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
