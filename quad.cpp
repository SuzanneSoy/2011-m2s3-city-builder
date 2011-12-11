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

int Quad::minLengthNS() {
	return std::min(
		Segment(corner[NW],corner[NE]).length(),
		Segment(corner[SE],corner[SW]).length()
	);
}

int Quad::minLengthEW() {
	return std::min(
		Segment(corner[NE],corner[SE]).length(),
		Segment(corner[SW],corner[NW]).length()
	);
}

int Quad::maxLengthNS() {
	return std::max(
		Segment(corner[NW],corner[NE]).length(),
		Segment(corner[SE],corner[SW]).length()
	);
}

int Quad::maxLengthEW() {
	return std::max(
		Segment(corner[NE],corner[SE]).length(),
		Segment(corner[SW],corner[NW]).length()
	);
}

int Quad::minLength() {
	return std::min(minLengthNS(), minLengthEW());
}

int Quad::maxLength() {
	return std::max(maxLengthNS(), maxLengthEW());
}

float Quad::minAngle() {
	float a = 370; // > 360.
	for (int i = 0; i < 4; i++) {
		a = std::min(a, Triangle(corner[NE+i], corner[SE+i], corner[SW+i]).angle());
	}
	return a;
}

float Quad::maxAngle() {
	float a = 0;
	for (int i = 0; i < 4; i++) {
		a = std::max(a, Triangle(corner[NE+i], corner[SE+i], corner[SW+i]).angle());
	}
	return a;
}
