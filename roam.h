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
