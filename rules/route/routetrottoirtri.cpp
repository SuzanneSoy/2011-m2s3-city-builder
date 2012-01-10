#include "all_includes.hh"

RouteTrottoirTri::RouteTrottoirTri(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool RouteTrottoirTri::split() {
	float th = 20;        // Terrain height.
	Triangle ttrottoir = c.insetLTR(250);
	Triangle tinterieur = ttrottoir.insetLTR(140);

	for (int i = 0; i < 3; i++) {
		addChild(new RouteQuadChaussee(Quad(c[LEFT+i],c[TOP+i],ttrottoir[TOP+i],ttrottoir[LEFT+i])));
		addChild(new TrottoirQuadNormal(Quad(ttrottoir[LEFT+i],ttrottoir[TOP+i],tinterieur[TOP+i],tinterieur[LEFT+i]),th));
	}

	addChild(factory(seed, 0, tinterieur + Vertex(0,0,th)));

	return true;
}

Chose* RouteTrottoirTri::factory(int seed, int n, Triangle c) {
	bool small = c.minLength() < 2500;
	bool big = c.maxLength() >= 5000;
	//bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);
	//bool anglesOk = c.minAngle() > Angle::d2r(90-40) && c.maxAngle() < Angle::d2r(90+40);
	//bool tooWideX = c.minLengthEW() * 2 < c.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	//bool tooWideY = c.minLengthNS() * 2 < c.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).

	if (!big && proba(seed, n, 1, 20)) {
		return new TerrainTriHerbe(c);
	} else if (small && !big) {
		return new BatimentTri(c);
	} else {
		return new TerrainTriHerbe(c);
	}
}

void RouteTrottoirTri::triangulation() {
	float h = floatInRange(seed,1,minHeight,maxHeight);
	float htoit = floatInRange(seed,2,minHeight/2,maxHeight/2);

	Triangle ch = c + Vertex(0,0,h + htoit);
	addGPUTriangle(c, 0xFF, 0xFF, 0x00);
	addGPUTriangle(ch, 0xFF, 0xFF, 0x00);
	for (int i = 0; i < 3; i++)
		addGPUQuad(c[LEFT+i], c[TOP+i], ch[TOP+i], ch[LEFT+i], 0xFF, 0xFF, 0x00);
}

void RouteTrottoirTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
}
