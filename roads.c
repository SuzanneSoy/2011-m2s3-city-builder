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

/* Initialisation de la liste de routes.
 */
void initRoadslIst(int nb){
	roadsList = (roadPointY**) malloc(sizeof(roadPointY*)*nb);
}


/* La route est constituée d'une série de points, chaque point contient un nœd de route qui peut-être propre à cette route comme
 * appartenir à plusieurs routes. Le nœd contient un Vertex qui permet de le positionner sur la carte. Il contient également
 * le nombre et les portions de routes auxquelles il appartient.
 */

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
void grid_initvGrid(int width, int height, int segmentSize) {
	int xSize, ySize;
	xSize = (int)(width/segmentSize);
	ySize = (int)(height/segmentSize);

	vGrid = (Vertex****) malloc(sizeof(Vertex***)*xSize);
	int i,j,k;

	maxSegmentSize = segmentSize;
	nbXSubDivision = xSize;
	nbYSubDivision = ySize;
	quarterWidth = width;
	quarterHeight = height;

	for(i=0;i<xSize;i++) {
		vGrid[i] = (Vertex***) malloc(sizeof(Vertex**)*ySize);
		for(j=0;j<ySize;j++) {
			vGrid[i][j] = (Vertex**) malloc(sizeof(Vertex*)*maxNodesInGrid);
			for(k=0;k<maxNodesInGrid;k++)
				vGrid[i][j][k] = NULL;
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
Vertex* intersectionBetween(Segment *sega, Segment *segb) {
	sega = sega;
	segb = segb;
	Vertex *inter = (Vertex*) malloc(sizeof(Vertex));
	float m, k;         // Coordonnées de l'intersection des vecteurs sur les droites.
	int Ix, Iy, Jx, Jy; // Vecteur I et J corespondant au segment v et u;
	Vertex *va, *vb, *ua, *ub;
	
	va = sega->u;
	vb = sega->v;
	ua = segb->u;
	ub = segb->v;
	
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
	
	return NULL; //return inter;
}

 
void grid_drawGrid() {
	int i, j;
	
	for(i=0;i<nbXSubDivision-1;i++)
		for(j=0;j<nbYSubDivision-1;j++) {
			Vertex v = { .x = i*maxSegmentSize, .y = j*maxSegmentSize };
			Vertex u = { .x = (i+1)*maxSegmentSize, .y = j*maxSegmentSize };
			svg_line(&v,&u,0);
			u.x = i*maxSegmentSize;
			u.y = (j+1)*maxSegmentSize;
			svg_line(&v,&u,0);
		}
}


short grid_insertVertex(Vertex *vtx) {
	if(vtx == NULL)
		return 0;

	int i;
	for(i=0;i<maxNodesInGrid;i++) {
		if(vGrid[toX(vtx)][toY(vtx)][i] == NULL) {
			vGrid[toX(vtx)][toY(vtx)][i] = vtx;
			return 1;
		}
	}
	
	return 0;
}


/* Retourne le nœd le plus proche dans un certain voisinage. Si aucun nœd n'est trouvé alors 
 * la fonction renvoie NULL.
 * @param Vertex *v : Le nœd pour lequel on souhaite trouver un nœd proche.
 * @return roadNodeY* : le nœd de route le plus proche.
 */
Vertex* grid_getNearestVertex(Vertex *v) {
	Vertex **vtx;
	Vertex *nearestVertex = NULL;
	int i,j;
	int x = toX(v);
	int y = toY(v);
	int distance = maxSegmentSize*2;
	Vertex *tmp = NULL;
	int count = 0;
	fprintf(stderr,"colones : %d\n",nbXSubDivision);
	fprintf(stderr,"lignes : %d\n",nbYSubDivision);
	for(i=x-1; i<x+2; i++) {
		for(j=y-1; j<y+2; j++,count++) {
			if(i >= 0 && i < nbXSubDivision && y >= 0 && y < nbYSubDivision) {
				
				vtx = grid_getNearVertices2(i,j);
				
				int ind;

				fprintf(stderr,"passage %d\t\t %d %d\n",count,i,j);
				for(tmp = vtx[0], ind = 0; tmp != NULL && ind < maxNodesInGrid; tmp = vtx[ind++]) {
					fprintf(stderr,"noed\n");
					int dist = distBetween(v,tmp);
					if(dist < distance) {
						distance = dist;
						nearestVertex = tmp;
					}
					
					tmp = vtx[i];
				}
			}
		}
	}
	
	return nearestVertex;
}


Vertex* insertSegment(Segment *seg, int lag) {
	int segLength = distBetween(seg->u, seg->v);
	float coef = ((float)segLength-lag)/(float)segLength;
	Vertex *nearestVertex = NULL;
	Vertex tmpEnd, *va, *vb;
	int intersec = 0; // Booléen si intersection = 1 sinon = 0;
	
	va = seg->u;
	vb = seg->v;
	
	seg = seg;
	lag = lag;
	// ------- TODO à compléter et à vérifier.
	/*Segment **segs = grid_getNearSegments(rpb->rn->v->x,rpb->rn->v->y);
	Segment *seg = segs[0];
	int s = 0;
	
	while(seg != NULL) {
		Vertex *intersection = intersectionBetween(rpb->rn->v,rne->v,seg->u,seg->v);
		
		if(intersection != NULL) {
			// Créer un nœd, l'insérer au segment qui à causé l'intersection.
			// Ce nœd deviens le point d'arriver du segment à placer : rne;
			intersec = 1;
		}
		seg = segs[s++];
	}*/
	// -------
	if(intersec == 0) {
		tmpEnd.x = va->x + coef*(vb->x - va->x);
		tmpEnd.y = va->y + coef*(vb->y - va->y);
		
		nearestVertex = grid_getNearestVertex(&tmpEnd);
		
		if(nearestVertex != NULL && distBetween(nearestVertex,vb) < lag)
			vb = nearestVertex;
	}
		
	grid_insertVertex(va);
	grid_insertVertex(vb);
	return NULL;
}


int distBetween(Vertex *v, Vertex *u) {
	return sqrt((v->x-u->x)*(v->x-u->x)+(v->y-u->y)*(v->y-u->y));
}

Vertex** grid_getNearVertices(Vertex *v) {
	return vGrid[toX(v)][toY(v)];
}


Vertex** grid_getNearVertices2(int x, int y) {
	return vGrid[x][y];
}


/* Récupère tout les segement potentiellement sécant avec un segment ayant pour arrivée x et y.
 */
Segment** grid_getNearSegments(int x, int y) {
	Vertex **vtx, *tmpVtx;
	Segment** segs = (Segment**) malloc(sizeof(Segment)*9*maxNodesInGrid);
	int i, j, s, k, l;
	l=0;
	l=l;
	s = 0;

	for(i=x-1;i<x+2;i++) {
		for(j=y-1;j<y+2;j++) {
			if(x >= 0 && x < nbXSubDivision && y >= 0 && y < nbYSubDivision) {
				vtx = grid_getNearVertices2(i,j);
				k = 0;
				tmpVtx = vtx[0];
				/*
				// TODO Tester si le segment existe déjà dans la liste pour ne pas l'insérer en double.
				
				while(tmpVtx != NULL) {
					for(l=0;l<tmpVtx->nbIntersec;l++) {
						if(tmpVtx->intersec[l]->next != NULL) {
							segs[s]->u = tmpVtx->v;
							segs[s]->v = tmpVtx->intersec[l]->next->v;
						}
						s++;
						if(tmpvtx->intersec[l]->previous != NULL) {
							segs[s]->u = tmpVtx->v;
							segs[s]->v = tmpVtx->intersec[l]->previous->v;
						}
					}
					tmpVtx = vtx[k++];
				}*/
			}
		}
	}
	return segs;
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

/* ***************************** */
// Nouvelle version :

#define vertices_array_size 40
#define segments_array_size 1024
typedef struct Map {
	Vertex vertices[vertices_array_size];
	Segment segments[segments_array_size];
	int vertices_firstUnseen;
	int vertices_firstFree;
	int segments_firstFree;
	// TODO : champ grid & co. On peut même l'utiliser à la place de
	// vertices.
} Map;

Vertex* vertex_init(Map* m, int x, int y) {
	// TODO : s'il y a déjà un point dans la case de la grille pour
	// `(x,y)`, le renvoyer sans rien modifier.
	Vertex* v = &(m->vertices[m->vertices_firstFree++]);
	// TODO : insérer v dans la grille de m.
	m=m;
	
	v->x = x;
	v->y = y;
	v->s = NULL;
	return v;
}

Segment* segment_init(Map* m, Vertex* u, Vertex* v) {
	Segment* s = &(m->segments[m->segments_firstFree++]);
	s->u = u;
	s->v = v;
	s->nextU = u->s;
	s->nextV = v->s;
	u->s = s;
	v->s = s;
	return s;
}

Segment* segment_to(Map* m, Vertex* u, int x, int y) {
	Vertex* v = vertex_init(m, x, y);
	Segment* s = segment_init(m, u, v);
	return s;
}

void fv(Map* m, Vertex *from) {
	// Tracer une ou des routes, en utilisant segment_to.
	if(from->s == NULL)
		return;
		
	Vertex *existing = from->s->u == from ? from->s->v : from->s->u;
	//fprintf(stderr,"bonjour\n");
	// Segment dans la continuation
	 //Vertex new1 = vertex_add(from, vertex_substract(from, existing)); // from + (from - existing)
	 Vertex new1 = { .x = from->x + (from->x - existing->x),
					 .y = from->y + (from->y - existing->y),
					 .s = NULL };
	
	segment_to(m, from, new1.x, new1.y);
	
	// Segment perpendiculaire
	polarCoord *polar = ctp(from, existing);
	polar->angle += 90;
	cartesianCoord *c = ptc(from,polar->angle,polar->length);
	Vertex new2 = { .x = c->x, .y = c->y};

	segment_to(m, from, new2.x, new2.y);
}

void segment_display(Segment* s) {
	printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" />",
		   s->u->x, s->u->y, s->v->x, s->v->y);
}

void forceFields() {
	Map m;
	m.vertices[0] = (Vertex){ .x = 400, .y = 300, .s = NULL};
	m.vertices[1] = (Vertex){ .x = 410, .y = 310, .s = NULL};
	m.vertices_firstUnseen = 1;
	m.vertices_firstFree = 2;

	m.segments[0] = (Segment){ .u = &(m.vertices[0]), .v = &(m.vertices[1]), .nextU = NULL, .nextV = NULL};
	m.vertices[0].s = &(m.segments[0]);
	m.vertices[1].s = &(m.segments[0]);
	m.segments_firstFree = 1;
	
	grid_initvGrid(800, 600, 40);
	// TODO : insérer vertices[0] dans la grille.
	
	int i;
	for (i = 0; i < vertices_array_size; i++) {
		if (m.vertices_firstUnseen >= m.vertices_firstFree)
			break;
		fv(&m, &(m.vertices[m.vertices_firstUnseen++]));
	}
	
	grid_drawGrid();
	for (i = 0; i < m.segments_firstFree; i++) {
		segment_display(&(m.segments[i]));
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
