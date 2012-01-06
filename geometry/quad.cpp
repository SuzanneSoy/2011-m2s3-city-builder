#include "all_includes.hh"

Quad::Quad() {}

Quad::Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	c[NE] = ne;
	c[SE] = se;
	c[SW] = sw;
	c[NW] = nw;
}

Quad Quad::inset(Cardinal side, float offset) const {
	Quad q = (*this) << side;
	Vertex offsetDirection = (q[NW]-q[NE]).perpendicularCw();
	float distE = offset / offsetDirection.cosAngle(q[SE] - q[NE]);
	float distW = offset / offsetDirection.cosAngle(q[SW] - q[NW]);
	q[NE] = q[NE] + (q[SE] - q[NE]).setNorm(distE);
	q[NW] = q[NW] + (q[SW] - q[NW]).setNorm(distW);
	return q >> side;
}

Quad Quad::insetNESW(float offsetN, float offsetE, float offsetS, float offsetW) const {
    return (*this).inset(N,offsetN).inset(E,offsetE).inset(S,offsetS).inset(W,offsetW);
}

Quad Quad::insetNESW(float offset) const {
	return insetNESW(offset, offset, offset, offset);
}

Quad Quad::makeParallelogram() {
    int l1, l2;

    if(length(N) < length(S)) {
        if((l1 = length(E)) < (l2 = length(W))) {
            c[SW] = Segment(c[NW],c[SW]).reduce(l1).v;
            c[SE] = c[SW] + (c[NE] - c[NW]);
        }
        else if((l1 = length(E)) > (l2 = length(W))) {
            c[SE] = Segment(c[NE],c[SE]).reduce(l2).v;
            c[SW] = c[SE] + (c[NW] - c[NE]);
        }
    }
    else {
        if((l1 = length(E)) < (l2 = length(W))) {
            c[NW] = Segment(c[SW],c[NW]).reduce(l1).v;
            c[NE] = c[NW] + (c[SE] - c[SW]);
        }
        else if((l1 = length(E)) > (l2 = length(W))) {
            c[NE] = Segment(c[SE],c[NE]).reduce(l2).v;
            c[NW] = c[NE] + (c[SW] - c[SE]);
        }
    }

    return Quad(c[0],c[1],c[2],c[3]);
}

float Quad::length(Cardinal side) const {
	return Segment(c[NW+side],c[NE+side]).length();
}

float Quad::minLengthNS() const {
	return std::min(length(N), length(S));
}

float Quad::minLengthEW() const {
	return std::min(length(E), length(W));
}

float Quad::maxLengthNS() const {
	return std::max(length(N), length(S));
}

float Quad::maxLengthEW() const {
	return std::max(length(E), length(W));
}

float Quad::minLength() const {
	return std::min(minLengthNS(), minLengthEW());
}

float Quad::maxLength() const {
	return std::max(maxLengthNS(), maxLengthEW());
}

float Quad::minAngle() const {
	float a = 370; // > 360.
	for (int i = 0; i < 4; i++) {
		a = std::min(a, Triangle(c[NE+i], c[SE+i], c[SW+i]).angle());
	}
	return a;
}

float Quad::maxAngle() const {
	float a = 0;
	for (int i = 0; i < 4; i++) {
		a = std::max(a, Triangle(c[NE+i], c[SE+i], c[SW+i]).angle());
	}
	return a;
}

Quad operator+(const Quad& q, const Vertex& v) {
	return Quad(q[NE] + v, q[SE] + v, q[SW] + v, q[NW] + v);
}

void Quad::cutCornerCorner(Coin from) const {
	Triangle t1(c[from-1], c[from], c[from+1]);
	Triangle t2(c[from+1], c[from+2], c[from-1]);
	// TODO
}
