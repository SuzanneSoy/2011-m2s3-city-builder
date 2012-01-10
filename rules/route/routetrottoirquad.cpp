#include "all_includes.hh"

RouteTrottoirQuad::RouteTrottoirQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool RouteTrottoirQuad::split() {
	float th = 20;        // Terrain height.
	Quad qtrottoir = c.insetNESW(250);
	Quad qinterieur = qtrottoir.insetNESW(140);

	for (int i = 0; i < 4; i++) {
		addChild(new RouteQuadChaussee(Quad(c[NE+i],c[SE+i],qtrottoir[SE+i],qtrottoir[NE+i])));
		addChild(new TrottoirQuadNormal(Quad(qtrottoir[NE+i],qtrottoir[SE+i],qinterieur[SE+i],qinterieur[NE+i]),th));
	}

	addChild(factory(seed, 0, qinterieur + Vertex(0,0,th)));

	return true;
}

Chose* RouteTrottoirQuad::factory(int seed, int n, Quad c) {
	bool small = c.minLength() < 2500;
	bool big = c.maxLength() >= 5000;
	bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);
	//bool anglesOk = c.minAngle() > Angle::d2r(90-40) && c.maxAngle() < Angle::d2r(90+40);
	//bool tooWideX = c.minLengthEW() * 2 < c.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	//bool tooWideY = c.minLengthNS() * 2 < c.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).

	if (!big && proba(seed, n, 1, 20)) {
		return new TerrainQuadHerbe(c);
	} else if (small && anglesAcceptable) {
		return new BatimentQuad(c);
	} else {
		return new TerrainQuadHerbe(c);
	}
}

void RouteTrottoirQuad::triangulation() {
	float h = floatInRange(seed,1,minHeight,maxHeight);
	float htoit = floatInRange(seed,2,minHeight/2,maxHeight/2);

	addGPUOcto(c, c + Vertex(0,0,h + htoit), 0xFF, 0xFF, 0xFF);
}

void RouteTrottoirQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
}
