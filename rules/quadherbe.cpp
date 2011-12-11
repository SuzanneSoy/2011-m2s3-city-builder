#include "all_includes.hh"

QuadHerbe::QuadHerbe(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Quadrilatere(ne, se, sw, nw), red(0x11) {
	triangulation();
}

QuadHerbe::QuadHerbe(int red, Vertex ne, Vertex se, Vertex sw, Vertex nw) : Quadrilatere(ne, se, sw, nw), red(red) {
	triangulation();
}

void QuadHerbe::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corner[NE], corner[NW], corner[SW], red, 0xaa, 0x22));
	addTriangle(new Triangle(corner[SW], corner[SE], corner[NE], red, 0xaa, 0x22));
}
