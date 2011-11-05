#include <iostream>
#include "rules.h"
#include "hash.h"

class Carrefour;
std::ostream& operator<<(std::ostream& os, const Carrefour& c);
std::ostream& operator<<(std::ostream& os, const Carrefour* c);

class Carrefour {
public:
	Vertex corners[4];
public:
	Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
		corners[NE]=ne;
		corners[SE]=se;
		corners[SW]=sw;
		corners[NW]=nw;
		std::cout << this << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os, const Carrefour* c) { return os << *c; }
std::ostream& operator<<(std::ostream& os, const Carrefour& c) {
	return os << "Carrefour " << c.corners[NE] << "-" << c.corners[SE] << "-" << c.corners[NW] << "-" << c.corners[SW];
}

class Route;
std::ostream& operator<<(std::ostream& os, const Route& r);
std::ostream& operator<<(std::ostream& os, const Route* r);

class Route {
public:
	Vertex corners[4];
public:
	Route(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
		corners[NE]=ne;
		corners[SE]=se;
		corners[SW]=sw;
		corners[NW]=nw;
		std::cout << this << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os, const Route* r) { return os << *r; }
std::ostream& operator<<(std::ostream& os, const Route& r) {
	return os << "Route " << r.corners[NE] << "-" << r.corners[SE] << "-" << r.corners[NW] << "-" << r.corners[SW];
}

class RectangleRoutes;
std::ostream& operator<<(std::ostream& os, const RectangleRoutes& r);
std::ostream& operator<<(std::ostream& os, const RectangleRoutes* r);

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class RectangleRoutes {
public:
	Vertex ne;
	Vertex sw;
	IO io [4];
	int seed;
public:
	RectangleRoutes(Vertex ne, Vertex sw, int seed) : ne(ne), sw(sw), seed(seed) {
		std::cout << this << std::endl;
	}
	int width() { return this->ne.x - this->sw.x; }
	int height() { return this->ne.y - this->sw.y; }
	void subdivide() {
		Vertex split(
			hashInRange(this->seed, 0, this->sw.x + this->width()*1/4, this->sw.x + this->width()*3/4),
			hashInRange(this->seed, 1, this->sw.y + this->height()*1/4, this->sw.y + this->height()*3/4)
		);
		Carrefour c(split.add(1,1), split.add(1,-1), split.add(-1,-1), split.add(-1,1));
		// routes au NESW du carrefour
		Vertex roadEndN(this->ne.y, split.x);
		Vertex roadEndE(this->ne.x, split.y);
		Vertex roadEndS(this->sw.y, split.x);
		Vertex roadEndW(this->sw.x, split.y);
		Route rn(roadEndN.add(-1,0), roadEndN.add(+1,0), split.add(+1,+1), split.add(-1,+1));
		Route re(roadEndE.add(0,+1), roadEndE.add(0,-1), split.add(+1,-1), split.add(+1,+1));
		Route rs(roadEndS.add(+1,0), roadEndS.add(-1,0), split.add(-1,-1), split.add(+1,-1));
		Route rw(roadEndW.add(0,-1), roadEndW.add(0,+1), split.add(-1,+1), split.add(-1,-1));
		// Sous-quartiers
		RectangleRoutes(this->ne, re.corners[NW], newSeed(this->seed, 2));
		RectangleRoutes(re.corners[SE], rs.corners[SE], newSeed(this->seed, 3));
		RectangleRoutes(rs.corners[NW], this->sw, newSeed(this->seed, 4));
		RectangleRoutes(Vertex(this->sw.x, this->ne.y), rn.corners[SW], newSeed(this->seed, 5));
	}
};

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << "(" << v.x << "," << v.y << ")";
}

std::ostream& operator<<(std::ostream& os, const RectangleRoutes* r) { return os << *r; }
std::ostream& operator<<(std::ostream& os, const RectangleRoutes& r) {
	return os << "RectangleRoutes " << r.ne << "-" << r.sw;
}

int main() {
	// Générer une tile de base
	Vertex ne(100, 100);
	Vertex sw(0, 0);
	RectangleRoutes r(ne, sw, random());
	r.subdivide();
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	return 0;
}
