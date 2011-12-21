#include "all_includes.hh"

TerrainQuadHerbe::TerrainQuadHerbe(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), red(0x11) {
	addEntropy(ne, se, sw, nw);
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

TerrainQuadHerbe::~TerrainQuadHerbe() {
    children.clear();
    triangles.clear();
}

void TerrainQuadHerbe::getBoundingBoxPoints() {
	addBBPoint(corner[NE]);
	addBBPoint(corner[SE]);
	addBBPoint(corner[SW]);
	addBBPoint(corner[NW]);
	addBBPoint(corner[NE] + Vertex(0,0,1000)); // TODO
	addBBPoint(corner[SE] + Vertex(0,0,1000));
	addBBPoint(corner[SW] + Vertex(0,0,1000));
	addBBPoint(corner[NW] + Vertex(0,0,1000));
}

TerrainQuadHerbe::TerrainQuadHerbe(int red, Vertex ne, Vertex se, Vertex sw, Vertex nw)
	: Chose(), red(red) {
	addEntropy(ne, se, sw, nw);
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

bool TerrainQuadHerbe::split() {
	return false;
}

void TerrainQuadHerbe::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corner[NE], corner[NW], corner[SW], red, 0xaa, 0x22));
	addTriangle(new Triangle(corner[SW], corner[SE], corner[NE], red, 0xaa, 0x22));
}
