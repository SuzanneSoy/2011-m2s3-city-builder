#include "all_includes.hh"

RectangleRoutes::RectangleRoutes(Vertex ne, Vertex sw) : Chose(), ne(ne), sw(sw) {
	addEntropy(ne, sw);
	triangulation();
}

int RectangleRoutes::width() { return std::abs(this->ne.x - this->sw.x); }

int RectangleRoutes::height() { return std::abs(this->ne.y - this->sw.y); }

bool RectangleRoutes::subdivide() {
	children.reserve(9);
	int splitXMin = this->sw.x + std::max(4, this->width()*1/4);
	int splitXMax = this->ne.x - std::max(4, this->width()*1/4);
	int splitYMin = this->sw.y + std::max(4, this->height()*1/4);
	int splitYMax = this->ne.y - std::max(4, this->height()*1/4);
	Vertex split(
		hashInRange(this->seed, 0, splitXMin, splitXMax),
		hashInRange(this->seed, 1, splitYMin, splitYMax),
		0 // TODO
	);
	// TODO : addChild(…);
	addChild(new Carrefour(split + Vertex(1,1,0), split + Vertex(1,-1,0), split + Vertex(-1,-1,0), split + Vertex(-1,1,0)));
	// routes au NESW du carrefour
	// TODO : la plupart des zéros en z sont faux…
	Vertex roadEndN(split.x, this->ne.y, 0);
	Vertex roadEndE(this->ne.x, split.y, 0);
	Vertex roadEndS(split.x, this->sw.y, 0);
	Vertex roadEndW(this->sw.x, split.y, 0);
	// TODO : addChild(…);
	Route* rn = new Route(roadEndN + Vertex(+1,0,0), split + Vertex(+1,+1,0), split + Vertex(-1,+1,0), roadEndN + Vertex(-1,0,0)); // N
	Route* re = new Route(roadEndE + Vertex(0,+1,0), roadEndE + Vertex(0,-1,0), split + Vertex(+1,-1,0), split + Vertex(+1,+1,0)); // E
	Route* rs = new Route(split + Vertex(+1,-1,0), roadEndS + Vertex(+1,0,0), roadEndS + Vertex(-1,0,0), split + Vertex(-1,-1,0)); // S
	Route* rw = new Route(split + Vertex(-1,+1,0), split + Vertex(-1,-1,0), roadEndW + Vertex(0,-1,0), roadEndW + Vertex(0,+1,0)); // W
	addChild(rn);
	addChild(re);
	addChild(rs);
	addChild(rw);
	// Sous-quartiers
	addChild(sub(ne, re->nw)); // sous-quartier NE
	addChild(sub(re->se, rs->se)); // sous-quartier SE
	addChild(sub(rs->nw, sw)); // sous-quartier SW
	addChild(sub(rn->nw, rw->nw)); // sous-quartier NW
	return true;
}

void RectangleRoutes::triangulation() {
	triangles.reserve(2);
	Vertex nw(this->sw.x, this->ne.y, 0);
	Vertex se(this->ne.x, this->sw.y, 0);
	addTriangle(new Triangle(this->ne, nw, this->sw, 0xc0, 0xc0, 0xc0));
	addTriangle(new Triangle(this->sw, se, this->ne, 0xc0, 0xc0, 0xc0));
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
