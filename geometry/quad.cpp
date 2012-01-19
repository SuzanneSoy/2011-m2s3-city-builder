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
	Vertex offsetDirection = Triangle(q[NE], q[NW], q[NW] + q.normal()).normal();
	Vertex e = q[SE] - q[NE];
	Vertex w = q[SW] - q[NW];
	float distE = offset / offsetDirection.cosAngle(e);
	float distW = offset / offsetDirection.cosAngle(w);
	q[NE] = q[NE] + e.setNorm(distE);
	q[NW] = q[NW] + w.setNorm(distW);
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

Cardinal Quad::minLengthSide() const {
	float ln = length(N);
	float le = length(E);
	float ls = length(S);
	float lw = length(W);
	if (ln < le && ln < ls && ln < lw) return N;
	else if (le < ls && le < lw) return E;
	else if (ls < lw) return S;
	else return W;
}

Cardinal Quad::maxLengthSide() const {
	float ln = length(N);
	float le = length(E);
	float ls = length(S);
	float lw = length(W);
	if (ln > le && ln > ls && ln > lw) return N;
	else if (le > ls && le > lw) return E;
	else if (ls > lw) return S;
	else return W;
}

float Quad::angle(Coin corner) const {
	return Triangle(c[NW+corner], c[NE+corner], c[SE+corner]).angle();
}

float Quad::minAngle() const {
	float ane = angle(NE);
	float ase = angle(SE);
	float asw = angle(SW);
	float anw = 2*Angle::Pi - (ane + ase + asw);
	return std::min(std::min(ane, ase), std::min(asw, anw));
}

float Quad::maxAngle() const {
	float ane = angle(NE);
	float ase = angle(SE);
	float asw = angle(SW);
	float anw = 2*Angle::Pi - (ane + ase + asw);
	return std::max(std::max(ane, ase), std::max(asw, anw));
}

Coin Quad::minAngleCorner() const {
	float ane = angle(NE);
	float ase = angle(SE);
	float asw = angle(SW);
	float anw = 2*Angle::Pi - (ane + ase + asw);
	if (ane < ase && ane < asw && ane < anw) return NE;
	else if (ase < asw && ase < anw) return SE;
	else if (asw < anw) return SW;
	else return NW;
}

Coin Quad::maxAngleCorner() const {
	float ane = angle(NE);
	float ase = angle(SE);
	float asw = angle(SW);
	float anw = 2*Angle::Pi - (ane + ase + asw);
	if (ane > ase && ane > asw && ane > anw) return NE;
	else if (ase > asw && ase > anw) return SE;
	else if (asw > anw) return SW;
	else return NW;
}

Coin Quad::concaveCorner() {
    Vertex nne = Triangle(c[NW], c[NE], c[SE]).normalizedNormal();
    Vertex nse = Triangle(c[NE], c[SE], c[SW]).normalizedNormal();
    Vertex nsw = Triangle(c[SE], c[SW], c[NW]).normalizedNormal();
    Vertex nnw = Triangle(c[SW], c[NW], c[NE]).normalizedNormal();

    float dne1 = (nnw - nne).norm();
    float dne2 = (nse - nne).norm();
    float dse1 = (nne - nse).norm();
    float dse2 = (nsw - nse).norm();
    float dsw1 = (nse - nsw).norm();
    float dsw2 = (nnw - nsw).norm();
    float dnw1 = (nsw - nnw).norm();
    float dnw2 = (nne - nnw).norm();

    if(dne1 >= 1.5 && dne2 >= 1.5)
        return NE;
    else if(dse1 >= 1.5 && dse2 >= 1.5)
        return SE;
    else if(dsw1 >= 1.5 && dsw2 >= 1.5)
        return SW;
    else if(dnw1 >= 1.5 && dnw2 >= 1.5)
        return NW;
    else
    	return maxAngleCorner();
}

bool Quad::isConcave() {
    Vertex nne = Triangle(c[NW], c[NE], c[SE]).normalizedNormal();
    Vertex nse = Triangle(c[NE], c[SE], c[SW]).normalizedNormal();
    Vertex nsw = Triangle(c[SE], c[SW], c[NW]).normalizedNormal();
    Vertex nnw = Triangle(c[SW], c[NW], c[NE]).normalizedNormal();

    float dne1 = (nnw - nne).norm();
    float dse1 = (nne - nse).norm();
    float dsw1 = (nse - nsw).norm();
    float dnw1 = (nsw - nnw).norm();

    if(dne1 >= 1.5 || dse1 >= 1.5 || dsw1 >= 1.5 || dnw1 >= 1.5)
        return true;

    return (maxAngle() > Angle::d2r(160));
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
	return ne.surface() + sw.surface();
}

Quad Quad::insetProportionnal(float prop) {
    Quad rQuad= *this;

    Vertex bc = Segment(Segment(c[NW],c[NE]).center(),Segment(c[SW],c[SE]).center()).center();
    prop = prop;

    rQuad[NW] = Segment(bc,c[NW]).at(prop);
    rQuad[NE] = Segment(bc,c[NE]).at(prop);
    rQuad[SE] = Segment(bc,c[SE]).at(prop);
    rQuad[SW] = Segment(bc,c[SW]).at(prop);
    return rQuad;
}

Quad Quad::offsetNormal(float offset) const {
	return ((*this) + Triangle(c[NE], c[SE], c[SW]).normal().setNorm(offset));
}

Vertex Quad::normal() const {
	return Triangle(c[NE], c[SE], c[SW]).normal();
}

Vertex Quad::normalizedNormal() const {
	return Triangle(c[NE], c[SE], c[SW]).normalizedNormal();
}

Vertex Quad::moyenne() const {
	return ((c[NE] + c[SE] + c[SW] + c[NW]) / 4.f);
}
