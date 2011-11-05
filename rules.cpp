#include <iostream>
#include "rules.h"
#include "hash.h"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class RectangleRoutes {
public:
	Vertex ne;
	Vertex so;
	IO io [4];
	int seed;
public:
	RectangleRoutes(Vertex ne, Vertex so, int seed) : ne(ne), so(so), seed(seed) {}
	void display() { };
	int width() { return this->ne.x - this->so.x; }
	int height() { return this->ne.y - this->so.y; }
	void subdivide() {
		Vertex split = {
			randomInRange(this->seed, 0, this->so.x + this->width()*1/4, this->so.x + this->width()*3/4),
			randomInRange(this->seed, 1, this->so.y + this->height()*1/4, this->so.y + this->height()*3/4)
		};
		split = split;
		std::cout << this << std::endl;
		RectangleRoutes rr(ne, so, 42);
		// std::cout << rr << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << "(" << v.x << "," << v.y << ")";
}

std::ostream& operator<<(std::ostream& os, const RectangleRoutes& r) {
	int a = r.ne.x;
	a = a;
	return os << "42!";//<< r.ne << "-" << r.so;
}


	/* Carrefour(split + (1,1), split - (1,1)) */
	/* // routes au NESW du carrefour */
	/* Route((r.ne.x, split.y) + (0,1)), split + (1,1)) */
	/* Route((split.x, r.se.y) + (1,0)), split + (-1,1)) */
	/* Route((r.so.x, split.y) + (0,-1)), split + (-1,-1)) */
	/* Route((split.x, r.no.y) + (-1,0)), split + (1,-1)) */
	/* // subrectangles */
	/* RectangleRoutes(split + (1,1),   r.ne, newSeed(r.seed, 2)); */
	/* RectangleRoutes(split + (1,-1),  r.se, newSeed(r.seed, 3)); */
	/* RectangleRoutes(split + (-1,-1), r.so, newSeed(r.seed, 4)); */
	/* RectangleRoutes(split + (-1,1),  r.no, newSeed(r.seed, 5)); */

int main() {
	// Générer une tile de base
	Vertex ne = {100,0};
	Vertex so = {0,100};
	RectangleRoutes r(ne, so, 42);
	r.subdivide();
	std::cout << r << std::endl;
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	return 0;
}
