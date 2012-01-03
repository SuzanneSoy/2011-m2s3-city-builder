#include "all_includes.hh"

RouteQuadChaussee::RouteQuadChaussee(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne,se,sw,nw);
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

RouteQuadChaussee::~RouteQuadChaussee() {
    children.clear();
    triangles.clear();
}

void RouteQuadChaussee::getBoundingBoxPoints() {
	addBBPoint(corner[NE]);
	addBBPoint(corner[SE]);
	addBBPoint(corner[SW]);
	addBBPoint(corner[NW]);
	addBBPoint(corner[NE] + Vertex(0,0,1000)); // TODO
	addBBPoint(corner[SE] + Vertex(0,0,1000));
	addBBPoint(corner[SW] + Vertex(0,0,1000));
	addBBPoint(corner[NW] + Vertex(0,0,1000));
}

bool RouteQuadChaussee::split() {
	return false;
}

void RouteQuadChaussee::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corner[NE], corner[NW], corner[SW], 0x36, 0x36, 0x36));
	addTriangle(new Triangle(corner[SW], corner[SE], corner[NE], 0x36, 0x36, 0x36));
}
