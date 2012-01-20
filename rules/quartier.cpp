#include "all_includes.hh"

QuartierQuad::QuartierQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void QuartierQuad::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurMaxBatiment);
}

void QuartierQuad::split() {
	bool small = c.minLength() < 35 * 100;
	bool big = (c.minLengthNS() > 100 * 100 || c.minLengthEW() > 100 * 100) && c.minLength() > 40*100 && c.maxLength() < 300*100;
	bool isConcave = c.isConcave();
	bool nearConcave = c.maxAngle() > Angle::d2r(160);
	bool anglesOk = c.minAngle() > Angle::d2r(90-40) && c.maxAngle() < Angle::d2r(90+40);
	bool tooWideX = c.minLengthEW() * 2 < c.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	bool tooWideY = c.minLengthNS() * 2 < c.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
	bool bigPlace = c.maxLength() > Dimensions::maxRayonPlace * 4;
	bool tooBigPlace = c.maxLength() > Dimensions::maxRayonPlace * 8;
	if (isConcave)
		concave();
	else if (nearConcave)
		angleAngle();
	else if (big && anglesOk && proba(seed, -2, 0.25f))
		longueRue();
	else if (!small && !anglesOk && proba(seed, -3, 0.5f))
		angleAngle();
	else if (!small && !anglesOk)
		angleCote();
	else if (!small && (tooWideX || tooWideY))
		rect();
	else if (bigPlace && !tooBigPlace && proba(seed, -4, 0.4))
		place();
	else if (!small)
		carre();
	else
		addChild(new BatimentQuad(c));
}

void QuartierQuad::triangulation() {
	if (c.isConcave()) {
		Quad q = c << c.concaveCorner();
		triangulationConcave(Triangle(q[NE], q[SE], q[SW]));
		triangulationConcave(Triangle(q[SW], q[NW], q[NE]));
	} else {
		Quad ci = c.insetNESW(Dimensions::largeurRoute + Dimensions::largeurTrottoir);
		Quad cih = ci.offsetNormal(Dimensions::hauteurMaxBatiment);
		addGPUFourQuads(c, ci, Couleurs::route);
		addGPUQuad(cih, Couleurs::toit);
		for (int i = 0; i < 4; i++)
			addGPUQuad(Quad(ci[NE+i], ci[SE+i], cih[SE+i], cih[NE+i]), Couleurs::mur);
	}
}

void QuartierQuad::triangulationConcave(Triangle t) {
	// Même code que QuartierTri::triangulation.
	Triangle ci = t.insetLTR(Dimensions::largeurRoute + Dimensions::largeurTrottoir);
	Triangle cih = ci.offsetNormal(Dimensions::hauteurMaxBatiment);
	addGPUThreeQuads(t, ci, Couleurs::route);
	addGPUTriangle(cih, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(ci[LEFT+i], ci[TOP+i], cih[TOP+i], cih[LEFT+i]), Couleurs::mur);
}

void QuartierQuad::concave() {
	Quad q = c << c.concaveCorner();
	addChild(new QuartierTri(Triangle(q[NE], q[SE], q[SW])));
	addChild(new QuartierTri(Triangle(q[SW], q[NW], q[NE])));
}

void QuartierQuad::angleCote() {
	Quad q = c << c.maxAngleCorner();
	Vertex s = Segment(q[SE], q[SW]).randomPos(seed, 1, 0.4f, 0.6f);
	Vertex w = Segment(q[SW], q[NW]).randomPos(seed, 0, 0.4f, 0.6f);
	Triangle ts(q[SE], s, q[NE]);
	Triangle tw(q[NE], w, q[NW]);
	if (ts.minAngle() > tw.minAngle()) {
		addChild(new QuartierTri(ts));
		addChild(new QuartierQuad(Quad(q[NE], s, q[SW], q[NW])));
	} else {
		addChild(new QuartierTri(tw));
		addChild(new QuartierQuad(Quad(q[NE], q[SE], q[SW], w)));
	}
}

void QuartierQuad::angleAngle() {
	Quad q = c << c.maxAngleCorner();
	addChild(new QuartierTri(Triangle(q[NE], q[SE], q[SW])));
	addChild(new QuartierTri(Triangle(q[SW], q[NW], q[NE])));
}

void QuartierQuad::rect() {
	Quad q = c << c.maxLengthSide();
	Vertex n = Segment(q[NW], q[NE]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	Vertex s = Segment(q[SE], q[SW]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);

	addChild(new QuartierQuad(Quad(q[NE], q[SE], s, n)));
	addChild(new QuartierQuad(Quad(q[SW], q[NW], n, s)));
}

void QuartierQuad::carre() {
	Vertex center = c.insetProportionnal(0.33f).randomPoint(seed, 0);
	Vertex middle[4];
	for (int i = 0; i < 4; i++)
		middle[N+i] = Segment(c[NW+i], c[NE+i]).randomPos(seed, i + 1, 0.25f, 0.75f);

	for (int i = 0; i < 4; i++)
		addChild(new QuartierQuad(Quad(c[NE+i], middle[E+i], center, middle[N+i])));
}

void QuartierQuad::place() {
	Vertex center = c.insetProportionnal(0.25f).randomPoint(seed, 0);
	Vertex middle[4];
	for (int i = 0; i < 4; i++)
		middle[N+i] = Segment(c[NW+i], c[NE+i]).randomPos(seed, i + 1, 0.45f, 0.55f);

	Vertex smallOcto[8];
	Vertex interieur[8];
	Vertex bigOcto[8];
	float r = floatInRange(seed, 12345, Dimensions::minRayonPlace, Dimensions::maxRayonPlace);
	float shift = std::tan(Angle::Pi/8.f) * r;
	for (int i = 0; i < 4; i++) {
		Quad q(c[NE+i], middle[E+i], center, middle[N+i]);
		smallOcto[2*i]   = q.inset(W, shift).inset(S, r)[SW];
		smallOcto[2*i+1] = q.inset(S, shift).inset(W, r)[SW];
		bigOcto[2*i]     = q.inset(W, shift).inset(S, r)[NW];
		bigOcto[2*i+1]   = q.inset(S, shift).inset(W, r)[SE];
		Triangle t = Triangle(smallOcto[2*i+1], center, smallOcto[2*i]).inset(BASE, Dimensions::largeurRoute + Dimensions::largeurTrottoir);
		interieur[2*i] = t[RIGHT];
		interieur[2*i+1] = t[LEFT];
	}

	for (int i = 0; i < 4; i++) {
		addChild(new QuartierQuad(Quad(bigOcto[2*i], smallOcto[2*i], smallOcto[((2*i-1) + 8) % 8], bigOcto[((2*i-1) + 8) % 8])));
		addChild(new QuartierQuad(Quad(smallOcto[2*i+1], smallOcto[2*i], bigOcto[2*i], bigOcto[2*i+1])));
		addChild(new QuartierTri(Triangle(bigOcto[2*i], c[NE+i], bigOcto[2*i+1])));
	}
	for (int i = 0; i < 8; i++) {
		addChild(new RouteTrottoirQuad(Quad(smallOcto[i], smallOcto[(i+1)%8], interieur[(i+1)%8], interieur[i])));
		addChild(new TerrainTri(Triangle(interieur[(i+1)%8], center, interieur[i])));
	}
}

void QuartierQuad::longueRue() {
	Quad q = c << c.maxLengthSide();
	Vertex e = Segment(q[NE], q[SE]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	Vertex w = Segment(q[SW], q[NW]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);
	Quad qn = Quad(q[NE], e, w, q[NW]).inset(S, 7*100);
	Quad qs = Quad(q[SW], w, e, q[SE]).inset(S, 7*100);

	addChild(new QuartierQuad(qn));
	addChild(new QuartierQuad(qs));
	addChild(new BatimentQuad(Quad(qn[SE], qs[SW], qs[SE], qn[SW]))); // TODO
}

QuartierTri::QuartierTri(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void QuartierTri::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurMaxBatiment);
}

void QuartierTri::split() {
	bool small = c.minLength() < 80 * 100;
	bool big = c.maxLength() >= 150 * 100;
	float minAngle = c.minAngle();
	float maxAngle = c.maxAngle();
	bool equilateral = maxAngle < Angle::d2r(60+15) && minAngle > Angle::d2r(60-15);
	bool angleObtus = maxAngle > Angle::d2r(120);
	bool angleAigu = minAngle < Angle::d2r(30);
	bool anglesAcceptable = !angleAigu && !angleObtus;
	if (!big && proba(seed, -1, 0.05f)) {
		addChild(new BatimentTri(c));
	} else if (big && anglesAcceptable) {
		switch (hash2(seed, -2) % 3) {
		case 0: centre(); break;
		case 1: hauteur(); break;
		case 2:
		default: trapeze(); break;
		}
	} else if (!small && equilateral) {
		centre();
	} else if (!small && angleObtus) {
		hauteur();
	} else if (!small) {
		trapeze();
	} else {
		addChild(new BatimentTri(c));
	}
}

void QuartierTri::triangulation() {
	Triangle ci = c.insetLTR(Dimensions::largeurRoute + Dimensions::largeurTrottoir);
	Triangle cih = ci.offsetNormal(Dimensions::hauteurMaxBatiment);
	addGPUThreeQuads(c, ci, Couleurs::route);
	addGPUTriangle(cih, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(ci[LEFT+i], ci[TOP+i], cih[TOP+i], cih[LEFT+i]), Couleurs::mur);
}

void QuartierTri::centre() {
	// TODO : maxLength / 6 au lieu de 1000
	// TODO : insetProportionnal();
	Vertex center = c.insetLTR(c.maxLength() / 6).randomPoint(seed, 0);
	Vertex edge[3];
	for (int i = 0; i < 3; i++)
		edge[LEFTSIDE+i] = Segment(c[LEFT+i], c[TOP+i]).randomPos(seed, i+1, 1.f/3.f, 2.f/3.f);

	for (int i = 0; i < 3; i++)
		addChild(new QuartierQuad(Quad(c[TOP+i], edge[RIGHTSIDE+i], center, edge[LEFTSIDE+i])));
}

void QuartierTri::hauteur() {
	Triangle t = c << c.maxAngleCorner();
	Vertex opposite = Segment(t[TOP], t[RIGHT]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);

	addChild(new QuartierTri(Triangle(t[TOP], opposite, t[LEFT])));
	addChild(new QuartierTri(Triangle(t[LEFT], opposite, t[RIGHT])));
}

void QuartierTri::trapeze() {
	Triangle t = c << c.minAngleCorner();
	Vertex left = Segment(t[LEFT], t[TOP]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	Vertex base = Segment(t[RIGHT], t[LEFT]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);

	addChild(new QuartierTri(Triangle(base, t[LEFT], left)));
	addChild(new QuartierQuad(Quad(base, left, t[TOP], t[RIGHT])));
}
