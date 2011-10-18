#include "roads.h"

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

// TODO Fusionner les deux fonctions et retourner une paire de valeurs.
// Transforme des coordonnées du plan en coordonées du tableau sur x.
int toX(Vertex *v) {
	return v->x*(maxSubDivision-1)/quarterSize;
}

// Transforme des coordonnées du plan en coordonées du tableau sur y.
int toY(Vertex *v) {
	return v->x*(maxSubDivision-1)/quarterSize;
}

void grid_initNodesGrid(int size) {
	nodesGrid = (roadNodeY****) malloc(sizeof(roadNodeY***)*size);
	int i,j,k;
	
	maxSubDivision = size;

	for(i=0;i<size;i++) {
		nodesGrid[i] = (roadNodeY***) malloc(sizeof(roadNodeY**)*size);
		for(j=0;j<size;j++) {
			nodesGrid[i][j] = (roadNodeY**) malloc(sizeof(roadNodeY*)*maxNodesInGrid);
			for(k=0;k<maxNodesInGrid;k++)
				nodesGrid[i][j][k] = NULL;
		}
	}
}

short grid_insertRoadNode(roadNodeY *rn) {
	if(rn == NULL || rn->v == NULL)
		return 0;

	int i;
	for(i=0;i<maxNodesInGrid;i++) {
		if(nodesGrid[toX(rn->v)][toY(rn->v)][i] == NULL) {
			nodesGrid[toX(rn->v)][toY(rn->v)][i] = rn;
			return 1;
		}
	}
	
	return 0;
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

roadNodeY* grid_getNearestRoadNode(Vertex *v) {
	roadNodeY **nr = grid_getNearNodes(v);
	roadNodeY *nearestNode = NULL;
	roadNodeY *tmp = nr[0];
	int distance = distBetween(v,tmp->v);
	
	if(tmp == NULL)
		return NULL;
	
	nearestNode = tmp;
	int i = 0;

	do {
		int dist = distBetween(v,tmp->v);
		if(dist < distance) {
			distance = dist;
			nearestNode = tmp;
		}
		
		i++;
		tmp = nr[i];
	} while(tmp != NULL);
	
	return nearestNode;
}

int distBetween(Vertex *v, Vertex *u) {
	return sqrt((v->x-u->x)*(v->x-u->x)+(v->y-u->y)*(v->y-u->y));
}

roadNodeY** grid_getNearNodes(Vertex *v) {
	return nodesGrid[toX(v)][toY(v)];
}

void carreY() {
	int size = 500;
	grid_initNodesGrid(6);
	roadPointY *roada = (roadPointY*) malloc(sizeof(roadPointY));
	roadPointY *roadb = (roadPointY*) malloc(sizeof(roadPointY));
	roadNodeY *rn;
	Vertex *v;
	roadNodeY *common = NULL;
	int i;
	
	for(i=0;i<40;i++) {
		rn = (roadNodeY*)malloc(sizeof(roadNodeY));
		v = (Vertex*) malloc(sizeof(Vertex));
		
		v->x = (i+1)*16;
		v->y = ((i+1)%3)*(61%(i+1))+100;
		rn->v = v;
		if(i == 18) common = rn;
		grid_insertRoadNode(rn);
		addRoadNode(roada,rn);
	}
	
	for(i=0;i<30;i++) {
		rn = (roadNodeY*)malloc(sizeof(roadNodeY));
		v = (Vertex*) malloc(sizeof(Vertex));
		
		v->x = (i+1)*22;
		v->y = ((i+1)%5)*(61%(i+2))+160;
		rn->v = v;
		if(i%5) if(grid_getNearestRoadNode(v) != NULL)
			rn = grid_getNearestRoadNode(v);
			//rn = common;
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
