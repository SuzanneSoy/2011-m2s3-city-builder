#include "all_includes.hh"

RouteQuadCarrefour::RouteQuadCarrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne,se,sw,nw);
	triangulation();
}

bool RouteQuadCarrefour::subdivide() {
	// TODO
	return false;
}

void RouteQuadCarrefour::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(ne, nw, sw, 0x36, 0x36, 0x36));
	addTriangle(new Triangle(sw, se, ne, 0x36, 0x36, 0x36));
}
