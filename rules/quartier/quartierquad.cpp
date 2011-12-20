#include "all_includes.hh"

QuartierQuad::QuartierQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	corner[NE] = ne;
	corner[SE] = se;
	corner[SW] = sw;
	corner[NW] = nw;
}

QuartierQuad::~QuartierQuad() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

std::vector<Vertex*> QuartierQuad::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

Chose* QuartierQuad::factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	Quad q = Quad(ne,se,sw,nw);
	bool small = q.minLength() < 2500;
	bool big = q.maxLength() >= 5000;
	bool anglesAcceptable = q.minAngle() > Angle::d2r(90-60) && q.maxAngle() < Angle::d2r(90+60);
	bool anglesOk = q.minAngle() > Angle::d2r(90-40) && q.maxAngle() < Angle::d2r(90+40);
	bool tooWideX = q.minLengthEW() * 2 < q.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	bool tooWideY = q.minLengthNS() * 2 < q.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
	if (!big && proba(seed, n, 1, 20)) {
		return new TerrainQuadHerbe(ne, se, sw, nw);
	} else if (small && anglesAcceptable) {
		return new BatimentQuad(ne, se, sw, nw, N);
	} else if (!small && !anglesOk) {
		return new QuartierQuadAngle(ne, se, sw, nw);
	} else if (!small && tooWideY) {
		return new QuartierQuadRect(nw, ne, se, sw);
	} else if (!small && tooWideX) {
		return new QuartierQuadRect(ne, se, sw, nw);
	} else if (!small) {
		return new QuartierQuadCarre(ne, se, sw, nw);
	} else {
		return new TerrainQuadHerbe(ne, se, sw, nw);
	}
}

bool QuartierQuad::split() {
	return false;
}

void QuartierQuad::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corner[NE], corner[NW], corner[SW], 0xc0, 0xc0, 0xc0));
	addTriangle(new Triangle(corner[SW], corner[SE], corner[NE], 0xc0, 0xc0, 0xc0));
}
