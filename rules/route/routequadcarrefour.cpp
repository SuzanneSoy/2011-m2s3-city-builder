#include "all_includes.hh"

RouteQuadCarrefour::RouteQuadCarrefour(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void RouteQuadCarrefour::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

void RouteQuadCarrefour::triangulation() {
	addGPUQuad(c, 0x36, 0x36, 0x36);
}
