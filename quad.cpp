#include "all_includes.hh"

Quad::Quad() {}

Quad::Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

void Quad::offset(/*Cardinal*/int side, int offset) {
	Vertex voffset = (corner[NE + side]-corner[NW + side]).perpendicular().setNorm(offset);
	corner[NE + side] = corner[NE + side] + voffset.projectOn(corner[NE + side]-corner[SE + side]);
	corner[NW + side] = corner[NW + side] + voffset.projectOn(corner[NW + side]-corner[SW + side]);
}
