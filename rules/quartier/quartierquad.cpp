#include "all_includes.hh"

QuartierQuad::QuartierQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void QuartierQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000));
}

Chose* QuartierQuad::factory(int seed, int n, Quad c) {
	bool small = c.minLength() < 3500;
	bool big = c.maxLength() >= 6000;
	bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);
	bool concave = c.maxAngle() > Angle::d2r(160);
	bool anglesOk = c.minAngle() > Angle::d2r(90-40) && c.maxAngle() < Angle::d2r(90+40);
	bool tooWideX = c.minLengthEW() * 2 < c.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	bool tooWideY = c.minLengthNS() * 2 < c.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
	if (concave) {
		return new QuartierQuadConcave(c);
	} else if (!big && proba(seed, n, 1, 20)) {
		return new RouteTrottoirQuad(c);
	} else if (small && anglesAcceptable) {
		return new RouteTrottoirQuad(c);
	} else if (!small && !anglesOk) {
		return new QuartierQuadAngle(c);
	} else if (!small && tooWideY) {
		return new QuartierQuadRect(Quad(c[NW], c[NE], c[SE], c[SW]));
	} else if (!small && tooWideX) {
		return new QuartierQuadRect(c);
	} else if (!small) {
		return new QuartierQuadCarre(c);
	} else {
		return new RouteTrottoirQuad(c);
	}
}

bool QuartierQuad::split() {
	std::cout << "ERROR : QuartierQuad cannot be split." << std::endl;
	return false;
}

void QuartierQuad::triangulation() {
	addGPUQuad(c, 0xc0, 0xc0, 0xc0);
}
