#include "all_includes.hh"

Quad::Quad() {}

Quad::Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	c[(int)NE] = ne;
	c[(int)SE] = se;
	c[(int)SW] = sw;
	c[(int)NW] = nw;
}

Quad Quad::inset(Cardinal side, float offset) const {
	Quad q = (*this) << int(side);
	Vertex offsetDirection = (q[NW]-q[NE]).perpendicularCw();
	float distE = offset / offsetDirection.cosAngle(q[SE] - q[NE]);
	float distW = offset / offsetDirection.cosAngle(q[SW] - q[NW]);
	q[NE] = q[NE] + (q[SE] - q[NE]).setNorm(distE);
	q[NW] = q[NW] + (q[SW] - q[NW]).setNorm(distW);
	return q >> int(side);
}

Quad Quad::insetNESW(float offsetN, float offsetE, float offsetS, float offsetW) const {
    return (*this).inset(N,offsetN).inset(E,offsetE).inset(S,offsetS).inset(W,offsetW);
}

Quad Quad::insetNESW(float offset) const {
	return insetNESW(offset, offset, offset, offset);
}

Quad Quad::insetOpp(Cardinal side, float offset) const {
    Quad q = (*this) << int(side);
    Quad qb = (*this) << int(side);

    qb = qb.inset(N,offset);
    return Quad(q[NE],qb[NE],qb[NW],q[NW]);
}

Quad Quad::makeParallelogram() const {
    float l1, l2;
    Quad q(c[NE],c[SE],c[SW],c[NW]);

    if(length(N) < length(S)) {
        if((l1 = length(E)) < (l2 = length(W))) {
            q[SW] = Segment(q[NW],q[SW]).reduce(l1).v;
            q[SE] = q[SW] + (q[NE] - q[NW]);
        }
        else if((l1 = length(E)) > (l2 = length(W))) {
            q[SE] = Segment(q[NE],q[SE]).reduce(l2).v;
            q[SW] = q[SE] + (q[NW] - q[NE]);
        }
    }
    else {
        if((l1 = length(E)) < (l2 = length(W))) {
            q[NW] = Segment(q[SW],q[NW]).reduce(l1).v;
            q[NE] = q[NW] + (q[SE] - q[SW]);
        }
        else if((l1 = length(E)) > (l2 = length(W))) {
            q[NE] = Segment(q[SE],q[NE]).reduce(l2).v;
            q[NW] = q[NE] + (q[SW] - q[SE]);
        }
    }

    return q;
}

float Quad::length(Cardinal side) const {
	return Segment(c[NW+int(side)],c[NE+int(side)]).length();
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

Vertex Quad::randomPoint(int seed, int n) const {
	Triangle ne(c[NW], c[NE], c[SE]);
	Triangle sw(c[SE], c[SW], c[NW]);
	float surfacene = ne.surface();
	float surfacesw = sw.surface();
	if (proba(seed, n, surfacene, surfacene + surfacesw)) {
		return ne.randomPoint(seed, hash2(n, 42));
	} else {
		return sw.randomPoint(seed, hash2(n, 42));
	}
}

float Quad::surface() const {
	Triangle ne(c[NW], c[NE], c[SE]);
	Triangle sw(c[SE], c[SW], c[NW]);
	std::cout << sw[LEFT] << " " << sw[TOP] << " " << sw[RIGHT] << std::endl;
	std::cout << "{" << ne.surface() << " " << sw.surface() << "}" << std::endl;
	return ne.surface() + sw.surface();
}
