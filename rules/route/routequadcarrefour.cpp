#include "all_includes.hh"

RouteQuadCarrefour::RouteQuadCarrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne,se,sw,nw);
	c[NE] = ne;
	c[SE] = se;
	c[SW] = sw;
	c[NW] = nw;
}

RouteQuadCarrefour::~RouteQuadCarrefour() {
    children.clear();
    triangles.clear();
}

void RouteQuadCarrefour::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,1000)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,1000));
	addBBPoint(c[SW] + Vertex(0,0,1000));
	addBBPoint(c[NW] + Vertex(0,0,1000));
}

bool RouteQuadCarrefour::split() {
	return false;
}

void RouteQuadCarrefour::triangulation() {
	triangles.reserve(2);
	addTriangle(new GPUTriangle(c[NE], c[NW], c[SW], 0x36, 0x36, 0x36));
	addTriangle(new GPUTriangle(c[SW], c[SE], c[NE], 0x36, 0x36, 0x36));
}
