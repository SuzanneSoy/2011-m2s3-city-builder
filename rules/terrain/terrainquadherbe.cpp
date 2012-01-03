#include "all_includes.hh"

TerrainQuadHerbe::TerrainQuadHerbe(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	c[NE] = ne;
	c[SE] = se;
	c[SW] = sw;
	c[NW] = nw;
}

void TerrainQuadHerbe::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,1000)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,1000));
	addBBPoint(c[SW] + Vertex(0,0,1000));
	addBBPoint(c[NW] + Vertex(0,0,1000));
}

bool TerrainQuadHerbe::split() {
	return false;
}

void TerrainQuadHerbe::triangulation() {
	triangles.reserve(2);
	addTriangle(new GPUTriangle(c[NE], c[NW], c[SW], 0x11, 0xaa, 0x22));
	addTriangle(new GPUTriangle(c[SW], c[SE], c[NE], 0x11, 0xaa, 0x22));
}
