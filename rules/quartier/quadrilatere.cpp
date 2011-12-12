#include "all_includes.hh"

Quadrilatere::Quadrilatere(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

Chose* Quadrilatere::factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	Quad q = Quad(ne,se,sw,nw);
	bool small = q.minLength() < 2500;
	bool big = q.maxLength() >= 5000;
	bool anglesAcceptable = q.minAngle() > Angle::d2r(30) && q.maxAngle() < Angle::d2r(150);
	bool anglesOk = q.minAngle() > Angle::d2r(50) && q.maxAngle() < Angle::d2r(130);
	bool tooWideX = q.minLengthEW() * 2 < q.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	bool tooWideY = q.minLengthNS() * 2 < q.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
	if (!big && proba(seed, n, 1, 20)) {
		return new QuadHerbe(ne, se, sw, nw);
	} else if (small && anglesAcceptable) {
		return new Batiment(ne, se, sw, nw);
	} else if (!small && !anglesOk) {
		return new QuadAngle(ne, se, sw, nw);
	} else if (!small && tooWideY) {
		return new QuadRect(nw, ne, se, sw);
	} else if (!small && tooWideX) {
		return new QuadRect(ne, se, sw, nw);
	} else if (!small) {
		return new QuadCroix(ne, se, sw, nw);
	} else {
		return new QuadHerbe(ne, se, sw, nw);
	}
}

bool Quadrilatere::subdivide() {
	return false;
}

void Quadrilatere::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corner[NE], corner[NW], corner[SW], 0xc0, 0xc0, 0xc0));
	addTriangle(new Triangle(corner[SW], corner[SE], corner[NE], 0xc0, 0xc0, 0xc0));
}
