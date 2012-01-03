#include "all_includes.hh"

RouteTriChaussee::RouteTriChaussee(Vertex left, Vertex top, Vertex right) : Chose() {
	addEntropy(left, top, right);
	corner[0] = left;
	corner[1] = top;
	corner[2] = right;
}

void RouteTriChaussee::getBoundingBoxPoints() {
	addBBPoint(corner[0]);
	addBBPoint(corner[1]);
	addBBPoint(corner[2]);
	addBBPoint(corner[0] + Vertex(0,0,1000)); // TODO
	addBBPoint(corner[1] + Vertex(0,0,1000));
	addBBPoint(corner[2] + Vertex(0,0,1000));
}

bool RouteTriChaussee::split() {
	return false;
}

void RouteTriChaussee::triangulation() {
	triangles.reserve(1);
	addTriangle(new Triangle(corner[0], corner[1], corner[2], 0x36, 0x36, 0x36));
}
