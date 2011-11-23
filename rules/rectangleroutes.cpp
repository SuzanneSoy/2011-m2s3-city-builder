#include "all_includes.hh"

RectangleRoutes::RectangleRoutes(Vertex ne, Vertex sw) : ne(ne), sw(sw) {
	addEntropy(ne);
	addEntropy(sw);
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
	Chose* rrne = sub(this->ne, re.corners[NW]);
	Chose* rrse = sub(re.corners[SE], rs.corners[SE]);
	Chose* rrsw = sub(rs.corners[NW], this->sw);
	Chose* rrnw = sub(Vertex(this->sw.x, this->ne.y), rn.corners[SW]);
	// TODO : stocker ces objets quelque part.
	(void)rrne;
	(void)rrse;
	(void)rrsw;
	(void)rrnw;
}

void RectangleRoutes::triangulation() {
	Vertex nw(this->sw.x, this->ne.y);
	Vertex se(this->ne.x, this->sw.y);
	new Triangle(this->sw, nw, this->ne);
	new Triangle(this->sw, se, this->ne);
}

Chose* RectangleRoutes::sub(Vertex ne, Vertex sw) {
	Segment rect = Segment(ne,sw);
	if (rect.width() < 10 || rect.height() < 10) {
		return new Batiment(ne, sw);
	} else {
		return new RectangleRoutes(ne, sw);
	}
}

std::ostream& operator<<(std::ostream& os, const RectangleRoutes* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const RectangleRoutes& r) {
	return os << "RectangleRoutes " << r.ne << "-" << r.sw;
}
