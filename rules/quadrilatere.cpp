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
	int minLength = q.minLength();
	int maxLength = q.maxLength();
	float minAngle = q.minAngle();
	float maxAngle = q.maxAngle();
	if (minLength < 2500 && maxLength > 5000 && proba(seed, n, 1, 20)) {
		return new QuadHerbe(ne, se, sw, nw);
	} else if (minLength < 2500 && minAngle > 50/180.f*3.1415926535 && maxAngle < 130/180.f*3.1415926535) { // + contrainte sur les angles
		return new Batiment(ne, se, sw, nw);
	} else if (minAngle <= 50/180.f*3.1415926535 && maxAngle >= 130/180.f*3.1415926535) {
		// angles trop pointus
		return new QuadHerbe(0xff, ne, se, sw, nw);
	} else if (minLength > 2500 &&
			   2*std::min(Segment(nw,ne).length(), Segment(se,sw).length())
			   < std::max(Segment(ne,se).length(), Segment(sw,nw).length())) {
		// trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
		return new QuadRect(nw, ne, se, sw); // TODO
	} else if (minLength > 2500 &&
			   2*std::min(Segment(ne,se).length(), Segment(sw,nw).length())
			   < std::max(Segment(nw,ne).length(), Segment(se,sw).length())) {
		// trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
		return new QuadRect(ne, se, sw, nw); // TODO
	} else if (minLength > 2500) {
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
