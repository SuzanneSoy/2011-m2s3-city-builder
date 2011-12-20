#include "all_includes.hh"

QuartierTri::QuartierTri(Vertex left, Vertex top, Vertex right) : Chose() {
	addEntropy(left, top, right);
	corner[0] = left;
	corner[1] = top;
	corner[2] = right;
	triangulation();
}

QuartierTri::~QuartierTri() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

std::vector<Vertex*> QuartierTri::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
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
