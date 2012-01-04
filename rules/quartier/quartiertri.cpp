#include "all_includes.hh"

QuartierTri::QuartierTri(Triangle c) : Chose(), c(c) {
	addEntropy(c);
}

void QuartierTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

Chose* QuartierTri::factory(int seed, int n, Triangle c) {
	(void)seed;
	(void)n;
	// TODO
	return new QuartierTri(c);
}

bool QuartierTri::split() {
	return false;
}

void QuartierTri::triangulation() {
	triangles.reserve(1);
	addGPUTriangle(new GPUTriangle(c[LEFT], c[TOP], c[RIGHT], 0xf0, 0xc0, 0xc0));
}
