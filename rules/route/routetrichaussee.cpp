#include "all_includes.hh"

RouteTriChaussee::RouteTriChaussee(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void RouteTriChaussee::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

void RouteTriChaussee::triangulation() {
	addGPUTriangle(c, 0x36, 0x36, 0x36);
}
