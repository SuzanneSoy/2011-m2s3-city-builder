#include "all_includes.hh"

Quadrilatere::Quadrilatere(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
	triangulation();
}

Chose* Quadrilatere::factory(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	if (Segment(ne,se).length() < 2500 ||
		Segment(se,sw).length() < 2500 ||
		Segment(sw,nw).length() < 2500 ||
		Segment(nw,ne).length() < 2500) {
		return new Batiment(ne, se, sw, nw);
	} else {
		return new QuadCroix(ne, se, sw, nw);
	}
}

bool Quadrilatere::subdivide() {
	return false;
}

void Quadrilatere::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corner[NE], corner[NW], corner[SW], 0xc0, 0xc0, 0xc0));
	addTriangle(new Triangle(corner[SW], corner[SE], corner[NE], 0xc0, 0xc0, 0xc0));
}

