typedef struct Vertex {
	int x;
	int y;
	//int z;
} Vertex;

typedef enum Cardinaux {
	N = 0,
	E = 1,
	S = 2,
	O = 3
} Cardinaux;

typedef enum Diagonales {
	NE = 0,
	SE = 1,
	SO = 2,
	NO = 3
} Diagonales;

typedef struct IO {
	int in;
	int out;
} IO;
