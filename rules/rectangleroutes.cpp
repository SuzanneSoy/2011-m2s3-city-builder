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
		hashInRange(this->seed, 1, this->sw.y + this->height()*1/4, this->sw.y + this->height()*3/4),
		0 // TODO
	);
	// TODO : addChild(…);
	new Carrefour(split + Vertex(1,1,0), split + Vertex(1,-1,0), split + Vertex(-1,-1,0), split + Vertex(-1,1,0));
	// routes au NESW du carrefour
	// TODO : la plupart des zéros en z sont faux…
	Vertex roadEndN(this->ne.y, split.x, 0);
	Vertex roadEndE(this->ne.x, split.y, 0);
	Vertex roadEndS(this->sw.y, split.x, 0);
	Vertex roadEndW(this->sw.x, split.y, 0);
	// TODO : addChild(…);
	Route* rn = new Route(roadEndN + Vertex(-1,0,0), roadEndN + Vertex(+1,0,0), split + Vertex(+1,+1,0), split + Vertex(-1,+1,0)); // N
	Route* re = new Route(roadEndE + Vertex(0,+1,0), roadEndE + Vertex(0,-1,0), split + Vertex(+1,-1,0), split + Vertex(+1,+1,0)); // E
	Route* rs = new Route(roadEndS + Vertex(+1,0,0), roadEndS + Vertex(-1,0,0), split + Vertex(-1,-1,0), split + Vertex(+1,-1,0)); // S
	Route* rw = new Route(roadEndW + Vertex(0,-1,0), roadEndW + Vertex(0,+1,0), split + Vertex(-1,+1,0), split + Vertex(-1,-1,0)); // W
	// Sous-quartiers
	addChild(sub(rn->corners[NE], re->corners[NE])); // sous-quartier NE
	addChild(sub(re->corners[SE], rs->corners[SE])); // sous-quartier SE
	addChild(sub(rs->corners[SW], rw->corners[SW])); // sous-quartier SW
	addChild(sub(rw->corners[NW], rn->corners[NW])); // sous-quartier NW
}

void RectangleRoutes::triangulation() {
	Vertex nw(this->sw.x, this->ne.y, 0);
	Vertex se(this->ne.x, this->sw.y, 0);
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
