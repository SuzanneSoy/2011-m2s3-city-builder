#include "all_includes.hh"

Quad::Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne,se,sw,nw);
	// triangulation();
}

Vertex& Quad::corner(Coin corner, int rotation) {
	switch ((corner + rotation) & 3) {
		case NE: return ne;
		case SE: return se;
		case SW: return sw;
		default: return nw;
	}
}

void Quad::offset(/*Cardinal*/int side, int offset) {
	Vertex voffset = (corner(NE,side)-corner(NW,side)).perpendicular().setNorm(offset);
	corner(NE,side) = corner(NE,side) + voffset.projectOn(corner(NE,side)-corner(SE,side));
	corner(NW,side) = corner(NW,side) + voffset.projectOn(corner(NW,side)-corner(SW,side));
}

bool Quad::subdivide() {
	return false;
}

void Quad::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(ne, nw, sw, 0xc0, 0xc0, 0xc0));
	addTriangle(new Triangle(sw, se, ne, 0xc0, 0xc0, 0xc0));
}
