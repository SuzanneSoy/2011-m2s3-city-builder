#include "all_includes.hh"

TileTri::TileTri(Vertex left, Vertex top, Vertex right) : Chose() {
	addEntropy(left, top, right);
	corner[0] = left;
	corner[1] = top;
	corner[2] = right;
	triangulation();
}

Chose* TileTri::factory(int seed, int n, Vertex left, Vertex top, Vertex right) {
	(void)seed;
	(void)n;
	return new TileTri(left, top, right);
	// Quad q = Quad(ne,se,sw,nw);
	// bool small = q.minLength() < 2500;
	// bool big = q.maxLength() >= 5000;
	// bool anglesOk = q.minAngle() > Angle::d2r(50) && q.maxAngle() < Angle::d2r(130);
	// bool tooWideX = q.minLengthEW() * 2 < q.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	// bool tooWideY = q.minLengthNS() * 2 < q.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
	// if (!big && proba(seed, n, 1, 20)) {
	// 	return new QuadHerbe(ne, se, sw, nw);
	// } else if (small && anglesOk) {
	// 	return new Batiment(ne, se, sw, nw);
	// } else if (!anglesOk) {
	// 	return new QuadAngle(ne, se, sw, nw);
	// } else if (!small && tooWideY) {
	// 	return new QuadRect(nw, ne, se, sw);
	// } else if (!small && tooWideX) {
	// 	return new QuadRect(ne, se, sw, nw);
	// } else if (!small) {
	// 	return new QuadCroix(ne, se, sw, nw);
	// } else {
	// 	return new QuadHerbe(ne, se, sw, nw);
	// }
}

bool TileTri::subdivide() {
	return false;
}

void TileTri::triangulation() {
	triangles.reserve(1);
	addTriangle(new Triangle(corner[0], corner[1], corner[2], 0xf0, 0xc0, 0xc0));
}
