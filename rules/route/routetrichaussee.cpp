#include "all_includes.hh"

RouteTriChaussee::RouteTriChaussee(Vertex left, Vertex top, Vertex right) : Chose() {
	addEntropy(left, top, right);
	c[0] = left;
	c[1] = top;
	c[2] = right;
}

void RouteTriChaussee::getBoundingBoxPoints() {
	addBBPoint(c[0]);
	addBBPoint(c[1]);
	addBBPoint(c[2]);
	addBBPoint(c[0] + Vertex(0,0,1000)); // TODO
	addBBPoint(c[1] + Vertex(0,0,1000));
	addBBPoint(c[2] + Vertex(0,0,1000));
}

bool RouteTriChaussee::split() {
	return false;
}

void RouteTriChaussee::triangulation() {
	triangles.reserve(1);
	addTriangle(new GPUTriangle(c[0], c[1], c[2], 0x36, 0x36, 0x36));
}
