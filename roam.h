#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vertex {
       int x;
       int y;
       int z;
       /* Ajouter des champs ici. */
} Vertex;

typedef struct Triangle {
       Vertex* vApex;
       Vertex* vLeft;
       Vertex* vRight;
       struct Triangle* tLeftChild;
       struct Triangle* tRightChild;
       struct Triangle* tBaseNeighbor;
       struct Triangle* tLeftNeighbor;
       struct Triangle* tRightNeighbor;
       struct Triangle* tParent;
} Triangle;

Triangle* initDefaultExample();
int interpolation(int x, int y, int x1, int y1, int x2, int y2, int ne, int se, int so, int no);
