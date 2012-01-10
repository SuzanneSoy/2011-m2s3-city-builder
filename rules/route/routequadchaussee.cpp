#include "all_includes.hh"

RouteQuadChaussee::RouteQuadChaussee(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void RouteQuadChaussee::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

void RouteQuadChaussee::triangulation() {
	addGPUQuad(c, 0x36, 0x36, 0x36);
}
