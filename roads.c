#include "roads.h"

void svg_start(int w, int h) {
	printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	printf("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">", w, h);
}

void svg_end() {
	printf("</svg>");
}

void svg_line(Vertex* a, Vertex* b, short color) {
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
	if(x >= nbXSubDivision) return 0;
	return x;
}

// Transforme des coordonnées du plan en coordonées du tableau sur y.
int toY(Vertex *v) {
	int y =  v->y*(nbYSubDivision)/quarterHeight;
	if(y >= nbYSubDivision) return 0;
	return y;
}

/* Convertion de coordonnées polaires en coordonnées cartésiennes.
 * @param Vertex* origin : Origine du vecteur.
 * @param short angle : Angle.
 * @param short length : Taille du vecteur.
 * @return struct cartesianCoord* : Les coordonnées cartésiennes du point d'arrivée.
 */
cartesianCoord* ptc(Vertex *origin, short angle, short length) {
	cartesianCoord *cc = (cartesianCoord*) malloc(sizeof(cartesianCoord));
	cc->x = origin->x + cos(M_PI*angle/180)*length;
	cc->y = origin->y + sin(M_PI*angle/180)*length;
	
	return cc;
}

/* Convertion de coordonnées cartésiennes en coordonnées polaires.
 * @param Vertex* origin : Origine du vecteur.
 * @param Vertex* end : Fin du vecteur.
 * @return struct polarCoord* : Les coordonnées polaires du point d'arrivée.
 */
polarCoord* ctp(Vertex *origin, Vertex *end) {
	polarCoord *pc = (polarCoord*) malloc(sizeof(polarCoord));
	pc->length = distBetween(origin,end);
	pc->angle = acos((end->x-origin->x)/pc->length);
	
	return pc;
}

/* Initialise la grille de nœuds.
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

/* Détermine si il existe une intersection entre deux segments de droite. Dans le cas 
 * ou une intersection existe les coordonnées du point d'intersection sont retournées.
 * Dans le cas contraire la fonction retourne NULL.
 * @param Vertex *va : Point de départ du premier segment.
 * @param Vertex *vb : Point d'arrivé du premier segment.
 * @param Vertex *ua : Point de départ du second segment.
 * @param Vertex *vb : Point d'arrivé du second segment.
 * @return Vertex* : Coordonnées du point d'intersection si il existe, sinon NULL.
 */
Vertex* intersectionBetween(Vertex *va, Vertex *vb, Vertex *ua, Vertex *ub) {
	Vertex *inter = (Vertex*) malloc(sizeof(Vertex));
	float m, k;         // Coordonnées de l'intersection des vecteurs sur les droites.
	int Ix, Iy, Jx, Jy; // Vecteur I et J corespondant au segment v et u;
	
	Ix = vb->x - va->x;
	Iy = vb->y - va->y;
	Jx = ub->x - ua->x;
	Jy = ub->y - ua->y;

	m = (float)(-(-Ix*va->y+Ix*ua->y+Iy*va->x-Iy*ua->x))/(float)(Ix*Jy-Iy*Jx);
	k = (float)(-(va->x*Jy-ua->x*Jy-Jx*va->y+Jx*ua->y))/(float)(Ix*Jy-Iy*Jx);

	if(m < 1 && m > 0 && k < 1 && k > 0) {
		inter->x = va->x + k * Ix;
		inter->y = va->y + k * Iy;
	}
	else
		return NULL;

	return inter;
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
	// TODO : previous
	// TODO modif les intersections de previous.
}

/* Retourne le nœd le plus proche dans un certain voisinage. Si aucun nœd n'est trouvé alors 
 * la fonction renvoie NULL.
 * @param Vertex *v : Le nœd pour lequel on souhaite trouver un nœd proche.
 * @return roadNodeY* : le nœd de route le plus proche.
 */
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

/* Ajoute un segment de route à la fin d'une route.
 * Le point d'origine du segment est le dernier de la route actuellement en place. Il est passé en paramètre pour
 * éviter le parcour de la route entière pour le trouver.
 * Le point d'arrivé peut-etre modifié suivant deux règles principales.
 * - Un nœd de route existe proche de l'endroit ou doit ce terminer le segment dans ce cas
 * on "fusionne" les deux le point existant devient le point d'arrivé du segment.
 * - Un segment se trouve sur le chemin du segment que l'on souhaite placer. Dans ce cas le segment
 * que l'on souhaite placer sera sectionné à l'intersection des deux segments et le points d'intersections sera 
 * le point d'arrivé du segment à placer.
 * @param roadPointY *road : La route à laquelle on veut ajouter le segmetn.
 * @param roadNodeY *rnb : Le nœd de départ du segment.
 * @param roadNodeY *rne : Le nœd d'arrivé du segment.
 * @param int lag : le décalage maximal autorisé pour le placement du nœd d'arrivé.
 * @return roadNodeY* : Le nœd d'arrivé du vecteur potentiellement modifié.
 */
roadNodeY* insertRoadSegment(roadPointY *road, roadNodeY *rnb, roadNodeY *rne, int lag) {
	int segLength = distBetween(rnb->v, rne->v);
	float coef = ((float)segLength-lag)/(float)segLength;
	roadNodeY *nearestNode = NULL;
	Vertex tmpEnd;
	
	// ------- TODO à compléter et à vérifier.
	Segment **segs = grid_getNearSegments(rnb->v->x,rnb->v->y);
	Segment *seg = segs[0];
	int s = 0;
	int intersec = 0; // Booléen si intersection = 1 sinon = 0;
	
	while(seg != NULL) {
		Vertex *intersection = intersectionBetween(rnb->v,rne->v,seg->u,seg->v);
		
		if(intersection != NULL) {
			// Créer un nœd, l'insérer au segment qui à causé l'intersection.
			// Ce nœd deviens le point d'arriver du segment à placer : rne;
			intersec = 1;
		}
		seg = segs[s++];
	}
	// -------
	if(intersec == 0) {
		tmpEnd.x = rnb->v->x+coef*(rne->v->x - rnb->v->x);
		tmpEnd.y = rnb->v->y+coef*(rne->v->y - rnb->v->y);
		fprintf(stderr,"segLength : %d\n",segLength);
		fprintf(stderr," ostart : %d %d\t oend : %d %d\n",rnb->v->x,rnb->v->y,rne->v->x,rne->v->y);
		fprintf(stderr," end : %d %d\n",tmpEnd.x,tmpEnd.y);
		nearestNode = grid_getNearestRoadNode(&tmpEnd);
		
		fprintf(stderr,"--11\n");
		
		if(nearestNode != NULL && distBetween(nearestNode->v,rne->v) < lag)
			rne = nearestNode;
	}
		
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

/* Récupère tout les segement potentiellement sécant avec un segment ayant pour arrivée x et y.
 */
Segment** grid_getNearSegments(int x, int y) {
	roadNodeY **nr, *tmpnr;
	Segment** segs = (Segment**) malloc(sizeof(Segment)*9*maxNodesInGrid);
	int i, j, s, k, l;
	
	s = 0;
	
	for(i=x-1;i<x+2;i++) {
		for(j=y-1;j<y+2;j++) {
			if(x >= 0 && x < nbXSubDivision && y >= 0 && y < nbYSubDivision) {
				nr = grid_getNearNodes2(i,j);
				k = 0;
				tmpnr = nr[0];
				
				// TODO Tester si le segment existe déjà dans la liste pour ne pas l'insérer en double.
				
				while(tmpnr != NULL) {
					for(l=0;l<tmpnr->nbIntersec;l++) {
						if(tmpnr->intersec[l]->next != NULL) {
							segs[s]->u = tmpnr->v;
							segs[s]->v = tmpnr->intersec[l]->next->v;
						}
						s++;
						if(tmpnr->intersec[l]->previous != NULL) {
							segs[s]->u = tmpnr->v;
							segs[s]->v = tmpnr->intersec[l]->previous->v;
						}
					}
					tmpnr = nr[k++];
				}
			}
		}
	}
	return segs;
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

// Algo « champs de force »
typedef struct FVector { float x; float y; } FVector;
inline FVector fVector_substract(FVector a, FVector b) { return (FVector){ .x = a.x - b.x, .y = a.y - b.y }; }
inline FVector fVector_add(FVector a, FVector b) { return (FVector){ .x = a.x + b.x, .y = a.y + b.y }; }
inline FVector fVector_rotate90(FVector v) { return (FVector){ .x = -v.y, .y = v.x }; }

typedef struct FSegment { FVector from; FVector to; } FSegment;
inline void fsegment_display(FSegment s) {
	printf("<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"black\" />", s.from.x, s.from.y, s.to.x, s.to.y);
}

// TODO : dimensionner correctement le tableau.
#define FSegmentArray_SIZE 1024
typedef struct FSegmentArray { FSegment seg[FSegmentArray_SIZE]; int firstUnseen; int firstFree; /* + CollisionGrid collision; */ } FSegmentArray;
inline void fSegmentArray_push(FSegmentArray* a, FSegment s) {
	// TODO : check for collisions.
	if (a->firstFree >= FSegmentArray_SIZE) return;
	a->seg[a->firstFree++] = s;
}
inline FSegment fSegmentArray_pop(FSegmentArray* a) {
	return a->seg[a->firstUnseen++];
}

/* Choisir des champs de force. `f(x,y,vecteur)` renvoie tous les
 * vecteurs de routes qu'on peut faire partir du point `(x,y)`,
 * lorsqu'on y arrive par la direction `vecteur`. */
// champ de force "ligne droite".
// TODO : devrait prendre un segment en paramètre.
void f(FSegment s, FSegmentArray* a) {
	FVector delta = fVector_substract(s.to, s.from);
	FSegment newS = {
		.from = s.to,
		.to = fVector_add(s.to, delta),
	};
	// TODO : s'accrocher aux points proches, et ne pas ajouter le segment à la queue si on s'accroche à un point existant.
	// TODO : ne pas utiliser des segments dans la file d'attente, mais juste des vertex, dont on peut énumérer les segments.
	fSegmentArray_push(a, newS);
	FSegment newS2 = {
		.from = s.to,
		.to = fVector_add(s.to, fVector_rotate90(delta)),
	};
	newS2.to.y += 3;
	fSegmentArray_push(a, newS2);
}

void forceFields() {
	/* Initialiser `fifo` à vide. */
	/* Choisir un point de départ aléatoire, une direction aléatoire,
	 * et insérer `(x,y,vecteur)` dans `fifo`. */
	FSegmentArray a;
	a.seg[0] = (FSegment){
		.from = { .x = 100, .y = 100 },
		.to = { .x = 90, .y = 100 }
	};
	a.firstUnseen = 0;
	a.firstFree = 1;
	
	grid_initNodesGrid(800, 600, 20);
	
	int i;
	for (i = 0; i < FSegmentArray_SIZE; i++) {
		f(fSegmentArray_pop(&a), &a);
	}

	grid_drawGrid();
	for (i = 0; i < FSegmentArray_SIZE; i++) {
		fsegment_display(a.seg[i]);
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
	//carreY();
	forceFields();
	Vertex a = {1,1};
	Vertex b = {4,1};
	Vertex c = {1,2};
	Vertex d = {4,0};
	
	Vertex *inter = intersectionBetween(&a,&b,&c,&d);
	if(inter == NULL)
		fprintf(stderr,"Pas d'intersection\n");
	else
		fprintf(stderr,"intersection : %d %d\n",inter->x,inter->y);
	
	//int i;
	//for (i = 0; i < n; i++) {
//		svg_line(&(points[i]), &(points[(i+1)%n]));
//	}
	
//	grid_drawGrid();
	
n=n;
	//roads(points);
	points[0] = points[0];
	svg_end();
	return 0;
}
