#include "all_includes.hh"

QuartierTri::QuartierTri(Vertex left, Vertex top, Vertex right) : Chose() {
	addEntropy(left, top, right);
	c[0] = left;
	c[1] = top;
	c[2] = right;
}

QuartierTri::~QuartierTri() {
	children.clear();
	triangles.clear();
}

void QuartierTri::getBoundingBoxPoints() {
	addBBPoint(c[0]);
	addBBPoint(c[1]);
	addBBPoint(c[2]);
	addBBPoint(c[0] + Vertex(0,0,1000)); // TODO
	addBBPoint(c[1] + Vertex(0,0,1000));
	addBBPoint(c[2] + Vertex(0,0,1000));
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
	addTriangle(new GPUTriangle(c[0], c[1], c[2], 0xf0, 0xc0, 0xc0));
}
