#include "rectangleroutes.hh"
#include "../vertex.hh"
#include "../directions.hh"
#include "../hash.hh"

#include "carrefour.hh"
#include "route.hh"

RectangleRoutes::RectangleRoutes(Vertex ne, Vertex sw, int seed) : ne(ne), sw(sw), seed(seed) {
	std::cout << this << std::endl;
}

int RectangleRoutes::width() { return this->ne.x - this->sw.x; }

int RectangleRoutes::height() { return this->ne.y - this->sw.y; }

void RectangleRoutes::subdivide() {
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
	RectangleRoutes rrne(this->ne, re.corners[NW], newSeed(this->seed, 2));
	RectangleRoutes rrse(re.corners[SE], rs.corners[SE], newSeed(this->seed, 3));
	RectangleRoutes rrsw(rs.corners[NW], this->sw, newSeed(this->seed, 4));
	RectangleRoutes rrnw(Vertex(this->sw.x, this->ne.y), rn.corners[SW], newSeed(this->seed, 5));
	// Entrées/sorties par mètre carré en fonction du type de terrain ?
	// rrnw.io[N].in += …;
}

std::ostream& operator<<(std::ostream& os, const RectangleRoutes* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const RectangleRoutes& r) {
	return os << "RectangleRoutes " << r.ne << "-" << r.sw;
}
