#include "all_includes.hh"

RouteQuadCarrefour::RouteQuadCarrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne,se,sw,nw);
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

RouteQuadCarrefour::~RouteQuadCarrefour() {
    children.clear();
    triangles.clear();
}

void RouteQuadCarrefour::getBoundingBoxPoints() {
	addBBPoint(corner[NE]);
	addBBPoint(corner[SE]);
	addBBPoint(corner[SW]);
	addBBPoint(corner[NW]);
	addBBPoint(corner[NE] + Vertex(0,0,1000)); // TODO
	addBBPoint(corner[SE] + Vertex(0,0,1000));
	addBBPoint(corner[SW] + Vertex(0,0,1000));
	addBBPoint(corner[NW] + Vertex(0,0,1000));
}

bool RouteQuadCarrefour::split() {
	return false;
}

void RouteQuadCarrefour::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corner[NE], corner[NW], corner[SW], 0x36, 0x36, 0x36));
	addTriangle(new Triangle(corner[SW], corner[SE], corner[NE], 0x36, 0x36, 0x36));
}
