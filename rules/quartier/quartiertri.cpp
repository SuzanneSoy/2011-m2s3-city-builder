#include "all_includes.hh"

QuartierTri::QuartierTri(Vertex left, Vertex top, Vertex right) : Chose() {
	addEntropy(left, top, right);
	corner[0] = left;
	corner[1] = top;
	corner[2] = right;
}

QuartierTri::~QuartierTri() {
	children.clear();
	triangles.clear();
}

void QuartierTri::getBoundingBoxPoints() {
	addBBPoint(corner[0]);
	addBBPoint(corner[1]);
	addBBPoint(corner[2]);
	addBBPoint(corner[0] + Vertex(0,0,1000)); // TODO
	addBBPoint(corner[1] + Vertex(0,0,1000));
	addBBPoint(corner[2] + Vertex(0,0,1000));
}

Chose* QuartierTri::factory(int seed, int n, Vertex left, Vertex top, Vertex right) {
	(void)seed;
	(void)n;
	// TODO
	return new QuartierTri(left, top, right);
}

bool QuartierTri::split() {
	return false;
}

void QuartierTri::triangulation() {
	triangles.reserve(1);
	addTriangle(new Triangle(corner[0], corner[1], corner[2], 0xf0, 0xc0, 0xc0));
}
