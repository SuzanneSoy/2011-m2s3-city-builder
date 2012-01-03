#include "all_includes.hh"

Quad::Quad() {}

Quad::Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	c[NE] = ne;
	c[SE] = se;
	c[SW] = sw;
	c[NW] = nw;
}

void Quad::offset(Cardinal side, int offset) {
	Vertex voffset = (c[NE + side]-c[NW + side]).perpendicular().setNorm(offset);
	c[NE + side] = c[NE + side] + voffset.projectOn(c[NE + side]-c[SE + side]);
	c[NW + side] = c[NW + side] + voffset.projectOn(c[NW + side]-c[SW + side]);
}

void Quad::offsetNESW(int offsetN, int offsetE, int offsetS, int offsetW) {
    this->offset(N,offsetN);
    this->offset(E,offsetE);
    this->offset(S,offsetS);
    this->offset(W,offsetW);
}

Quad Quad::makeParallelogram() {
    int l1, l2;

    if(Segment(c[NW],c[NE]).length() < Segment(c[SE],c[SW]).length()) {
        if((l1 = Segment(c[NE],c[SE]).length()) < (l2 = Segment(c[SW],c[NW]).length())) {
            c[SW] = Segment(c[NW],c[SW]).reduce(l1).v;
            c[SE] = c[SW] + (c[NE] - c[NW]);
        }
        else if((l1 = Segment(c[NE],c[SE]).length()) > (l2 = Segment(c[SW],c[NW]).length())) {
            c[SE] = Segment(c[NE],c[SE]).reduce(l2).v;
            c[SW] = c[SE] + (c[NW] - c[NE]);
        }
    }
    else {
        if((l1 = Segment(c[NE],c[SE]).length()) < (l2 = Segment(c[SW],c[NW]).length())) {
            c[NW] = Segment(c[SW],c[NW]).reduce(l1).v;
            c[NE] = c[NW] + (c[SE] - c[SW]);
        }
        else if((l1 = Segment(c[NE],c[SE]).length()) > (l2 = Segment(c[SW],c[NW]).length())) {
            c[NE] = Segment(c[SE],c[NE]).reduce(l2).v;
            c[NW] = c[NE] + (c[SW] - c[SE]);
        }
    }

    return Quad(c[0],c[1],c[2],c[3]);
}

int Quad::minLengthNS() {
	return std::min(
		Segment(c[NW],c[NE]).length(),
		Segment(c[SE],c[SW]).length()
	);
}

int Quad::minLengthEW() {
	return std::min(
		Segment(c[NE],c[SE]).length(),
		Segment(c[SW],c[NW]).length()
	);
}

int Quad::maxLengthNS() {
	return std::max(
		Segment(c[NW],c[NE]).length(),
		Segment(c[SE],c[SW]).length()
	);
}

int Quad::maxLengthEW() {
	return std::max(
		Segment(c[NE],c[SE]).length(),
		Segment(c[SW],c[NW]).length()
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
		a = std::min(a, Triangle(c[NE+i], c[SE+i], c[SW+i]).angle());
	}
	return a;
}

float Quad::maxAngle() {
	float a = 0;
	for (int i = 0; i < 4; i++) {
		a = std::max(a, Triangle(c[NE+i], c[SE+i], c[SW+i]).angle());
	}
	return a;
}
