#include "roads.h"

void svg_start(int w, int h) {
	printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">", w, h);
}

void svg_end() {
	printf("</svg>");
}

void svg_line(Vertex* a, Vertex* b,short color) {
	if(color == 0)
		printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"grey\" />", a->x, a->y, b->x, b->y);
	else if(color == 1)
		printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"#A0A000\" />", a->x, a->y, b->x, b->y);
	else if(color == 2)
		printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"blue\" />", a->x, a->y, b->x, b->y);
	else
		printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" />", a->x, a->y, b->x, b->y);
}

void svg_circle(int x, int y, int r) {
	printf("<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"black\" stroke-width=\"2\" fill=\"red\"/>",x,y,r);
}

void roads(Polygon* quartier) {
	quartier = quartier;
	Vertex center = { .x=400, .y=300 };
	svg_line(&center, &(quartier[0]),6);
}


/* Fonctions de Yoann suffixée par "Y" */

/* La route est constituée d'une série de points, chaque point contient un nœd de route qui peut-être propre à cette route comme
 * appartenir à plusieurs routes. Le nœd contient un Vertex qui permet de le positionner sur la carte. Il contient également
 * le nombre et les portions de routes auxquelles il appartient.
 */

// TODO Fusionner les deux fonctions et retourner une paire de valeurs.
// Transforme des coordonnées du plan en coordonées du tableau sur x.
int toX(Vertex *v) {
	int x = v->x*(nbXSubDivision)/quarterWidth;
	if(x >= nbXSubDivision)
		fprintf(stderr,"depassement du tableau sur x\n");
	return x;
}

// Transforme des coordonnées du plan en coordonées du tableau sur y.
int toY(Vertex *v) {
	int y =  v->y*(nbYSubDivision)/quarterHeight;
	if(y >= nbYSubDivision)
		fprintf(stderr,"Depassement du tableau sur y\n");
	return y;
}

/* Initialise la grille de nœds.
 * @param int width : Largeur du quartier à remplir.
 * @param int height : Hauteur du quartier à remplir.
 * @param int maxSegmentSize : Taille maximale d'un segment de route.
 */
void grid_initNodesGrid(int width, int height, int segmentSize) {
	int xSize, ySize;
	xSize = (int)(width/segmentSize);
	ySize = (int)(height/segmentSize);
	
	nodesGrid = (roadNodeY****) malloc(sizeof(roadNodeY***)*xSize);
	int i,j,k;
	
	maxSegmentSize = segmentSize;
	nbXSubDivision = xSize;
	nbYSubDivision = ySize;
	quarterWidth = width;
	quarterHeight = height;

	for(i=0;i<xSize;i++) {
		nodesGrid[i] = (roadNodeY***) malloc(sizeof(roadNodeY**)*ySize);
		for(j=0;j<ySize;j++) {
			nodesGrid[i][j] = (roadNodeY**) malloc(sizeof(roadNodeY*)*maxNodesInGrid);
			for(k=0;k<maxNodesInGrid;k++)
				nodesGrid[i][j][k] = NULL;
		}
	}
}

void grid_drawGrid() {
	int i, j;
	
	for(i=0;i<nbXSubDivision-1;i++)
		for(j=0;j<nbYSubDivision-1;j++) {
			Vertex v = {i*maxSegmentSize,j*maxSegmentSize};
			Vertex u = {(i+1)*maxSegmentSize,j*maxSegmentSize};
			svg_line(&v,&u,0);
			u.x = i*maxSegmentSize;
			u.y = (j+1)*maxSegmentSize;
			svg_line(&v,&u,0);
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
	roadNodeY **nr;
	roadNodeY *nearestNode = NULL;
	int i,j;
	int x = toX(v);
	int y = toY(v);
	int distance = maxSegmentSize*2;
	roadNodeY *tmp = NULL;
	int count = 0;
	fprintf(stderr,"colones : %d\n",nbXSubDivision);
	fprintf(stderr,"lignes : %d\n",nbYSubDivision);
	for(i=x-1; i<x+2; i++) {
		for(j=y-1; j<y+2; j++,count++) {
			if(i >= 0 && i < nbXSubDivision && y >= 0 && y < nbYSubDivision) {
				
				nr = grid_getNearNodes2(i,j);
				
				int ind;
				//tmp = nr[0];
				fprintf(stderr,"passage %d\t\t %d %d\n",count,i,j);
				for(tmp = nr[0], ind = 0; tmp != NULL && ind < maxNodesInGrid; tmp = nr[ind++]) {
					fprintf(stderr,"noed\n");
					int dist = distBetween(v,tmp->v);
					if(dist < distance) {
						distance = dist;
						nearestNode = tmp;
					}
					
					tmp = nr[i];
				}
			}
		}
	}
	
	return nearestNode;
}

roadNodeY* insertRoadSegment(roadPointY *road, roadNodeY *rnb, roadNodeY *rne, int lag) {
	int segLength = distBetween(rnb->v, rne->v);
	float coef = ((float)segLength-lag)/(float)segLength;
	roadNodeY *nearestNode = NULL;
	Vertex tmpEnd;
	tmpEnd.x = rnb->v->x+coef*(rne->v->x - rnb->v->x);
	tmpEnd.y = rnb->v->y+coef*(rne->v->y - rnb->v->y);
	fprintf(stderr,"segLength : %d\n",segLength);
	fprintf(stderr," ostart : %d %d\t oend : %d %d\n",rnb->v->x,rnb->v->y,rne->v->x,rne->v->y);
	fprintf(stderr," end : %d %d\n",tmpEnd.x,tmpEnd.y);
	nearestNode = grid_getNearestRoadNode(&tmpEnd);
	
	fprintf(stderr,"--11\n");
	
	if(nearestNode != NULL && distBetween(nearestNode->v,rne->v) < lag)
		rne = nearestNode;
		
	grid_insertRoadNode(rnb);
	grid_insertRoadNode(rne);
	addRoadNode(road,rne);
	return rne;
}

int distBetween(Vertex *v, Vertex *u) {
	return sqrt((v->x-u->x)*(v->x-u->x)+(v->y-u->y)*(v->y-u->y));
}

roadNodeY** grid_getNearNodes(Vertex *v) {
	return nodesGrid[toX(v)][toY(v)];
}

roadNodeY** grid_getNearNodes2(int x, int y) {
	return nodesGrid[x][y];
}

void carreY() {
	grid_initNodesGrid(800,600,10);
	roadPointY *roada = (roadPointY*) malloc(sizeof(roadPointY));
	roadPointY *roadb = (roadPointY*) malloc(sizeof(roadPointY));
	roadNodeY *rn;
	Vertex *v;
	roadNodeY *lastNode = NULL;
	int i;
	
	for(i=0;i<36;i++) {
		rn = (roadNodeY*)malloc(sizeof(roadNodeY));
		v = (Vertex*) malloc(sizeof(Vertex));
		
		v->x = (i+1)*16;
		v->y = ((i+1)%3)*(61%(i+1))+100;
		rn->v = v;

		grid_insertRoadNode(rn);
		addRoadNode(roada,rn);
	}
	
	for(i=0;i<30;i++) {
		rn = (roadNodeY*)malloc(sizeof(roadNodeY));
		v = (Vertex*) malloc(sizeof(Vertex));
		
		v->x = (i+1)*22;
		v->y = ((i+1)%5)*(61%(i+2))+120;
		rn->v = v;
		if(i==4) {fprintf(stderr,"x : %d  y : %d\n",toX(v),toY(v));}
		if(v->x < 800 && v->y < 600) {
			fprintf(stderr,"Noed : %d\n",i);
			if(i==0) {
				addRoadNode(roadb,rn);
				lastNode = rn;
			}
			else {
				insertRoadSegment(roadb,lastNode,rn,10);
				lastNode = rn;
			}
		}
	}
	
	roadPointY *rd = roada;
	while(rd->next != NULL) {
		svg_line(rd->rn->v,rd->next->rn->v,1);
		svg_circle(rd->rn->v->x,rd->rn->v->y,1);
		rd = rd->next;
	}
	
	rd = roadb;
	while(rd->next != NULL) {
		svg_line(rd->rn->v,rd->next->rn->v,2);
		svg_circle(rd->rn->v->x,rd->rn->v->y,1);
		rd = rd->next;
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
	
	grid_drawGrid();
	
n=n;
	//roads(points);
	points[0] = points[0];
	svg_end();
	return 0;
}
