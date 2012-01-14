#include "all_includes.hh"

QuartierQuad::QuartierQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void QuartierQuad::getBoundingBoxPoints() {
	addBBPoints(c, 600); // TODO : factoriser cette longueur (hauteur max des bâtiments).
}

bool QuartierQuad::split() {
	bool small = c.minLength() < 3500;
	bool isConcave = c.isConcave();
	bool nearConcave = c.maxAngle() > Angle::d2r(160);
	bool anglesOk = c.minAngle() > Angle::d2r(90-40) && c.maxAngle() < Angle::d2r(90+40);
	bool tooWideX = c.minLengthEW() * 2 < c.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	bool tooWideY = c.minLengthNS() * 2 < c.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
	if (isConcave)
		concave();
	else if (nearConcave)
		angleAngle();
	else if (!small && !anglesOk && proba(seed, -2, 1, 2))
		angleAngle();
	else if (!small && !anglesOk)
		angleCote();
	else if (!small && (tooWideX || tooWideY))
		rect();
	else if (!small)
		carre();
	else
		batiments();
	return true;
}

void QuartierQuad::triangulation() {
	if (c.isConcave()) {
		Quad q = c << c.concaveCorner();
		triangulationConcave(Triangle(q[NE], q[SE], q[SW]));
		triangulationConcave(Triangle(q[SW], q[NW], q[NE]));
	} else {
		Quad ci = c.insetNESW(250 + 140); // TODO : factoriser cette longueur (largeur route + largeur trottoir).
		Quad cih = ci.offsetNormal(600); // TODO : factoriser cette longueur (hauteur max des bâtiments).
		addGPUQuad(c, Couleurs::route);
		addGPUQuad(cih, Couleurs::toit);
		for (int i = 0; i < 4; i++)
			addGPUQuad(Quad(ci[NE+i], ci[SE+i], cih[SE+i], cih[NE+i]), Couleurs::mur);
	}
}

void QuartierQuad::triangulationConcave(Triangle t) {
	// Même code que QuartierTri::triangulation.
	Triangle ci = t.insetLTR(250 + 140); // TODO : factoriser cette longueur (largeur route + largeur trottoir).
	Triangle cih = ci.offsetNormal(600); // TODO : factoriser cette longueur (hauteur max des bâtiments).
	addGPUTriangle(t, Couleurs::route);
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
	// TODO : insetProportionnal();
	Vertex center = c.insetNESW(c.minLength() / 4.f).randomPoint(seed, 0);
	Vertex middle[4];
	for (int i = 0; i < 4; i++)
		middle[N+i] = Segment(c[NW+i], c[NE+i]).randomPos(seed, i + 1, 0.25, 0.75);

	for (int i = 0; i < 4; i++)
		addChild(new QuartierQuad(Quad(c[NE+i], middle[E+i], center, middle[N+i])));
}

void QuartierQuad::batiments() {
	float hauteurTrottoir = 20; // TODO : factoriser + ajouter ça à la hauteur max d'un bâtiment dans les autres calculs.
	Quad qtrottoir = c.insetNESW(250);
	Quad qinterieur = qtrottoir.insetNESW(140);
	Quad qbatiments = qinterieur.offsetNormal(hauteurTrottoir);

	for (int i = 0; i < 4; i++) {
		addChild(new RouteQuad(Quad(c[NE+i],c[SE+i],qtrottoir[SE+i],qtrottoir[NE+i])));
		addChild(new TrottoirQuad(Quad(qtrottoir[NE+i],qtrottoir[SE+i],qinterieur[SE+i],qinterieur[NE+i]),hauteurTrottoir));
	}

	// TODO :

	bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);

	if (anglesAcceptable && proba(seed, 0, 19, 20)) {
		addChild(new BatimentQuad(qbatiments));
	} else {
		addChild(new TerrainQuad(qbatiments));
	}
}

QuartierTri::QuartierTri(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void QuartierTri::getBoundingBoxPoints() {
	addBBPoints(c, 600); // TODO : factoriser cette longueur (hauteur max des bâtiments).
}

bool QuartierTri::split() {
	bool small = c.minLength() < 5000;
	bool big = c.maxLength() >= 10000;
	float minAngle = c.minAngle();
	float maxAngle = c.maxAngle();
	bool equilateral = maxAngle < Angle::d2r(60+15) && minAngle > Angle::d2r(60-15);
	bool angleObtus = maxAngle > Angle::d2r(120);
	bool angleAigu = minAngle < Angle::d2r(30);
	bool anglesAcceptable = !angleAigu && !angleObtus;
	if (!big && proba(seed, -1, 1, 20)) {
		batiments(); // TODO : RouteTrottoirTri(c);
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
		batiments();
	}
	return true;
}

void QuartierTri::triangulation() {
	Triangle ci = c.insetLTR(250 + 140); // TODO : factoriser cette longueur (largeur route + largeur trottoir).
	Triangle cih = ci.offsetNormal(600); // TODO : factoriser cette longueur (hauteur max des bâtiments).
	addGPUTriangle(c, Couleurs::route);
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

void QuartierTri::batiments() {
	return;
	float hauteurTrottoir = 14; // TODO : factoriser + ajouter ça à la hauteur max d'un bâtiment dans les autres calculs.
	Triangle ttrottoir = c.insetLTR(250);
	Triangle tinterieur = ttrottoir.insetLTR(140);
	Triangle tbatiments = tinterieur.offsetNormal(hauteurTrottoir);

	for (int i = 0; i < 3; i++) {
		addChild(new RouteQuad(Quad(c[LEFT+i],c[TOP+i],ttrottoir[TOP+i],ttrottoir[LEFT+i])));
		addChild(new TrottoirQuad(Quad(ttrottoir[LEFT+i],ttrottoir[TOP+i],tinterieur[TOP+i],tinterieur[LEFT+i]),hauteurTrottoir));
	}

	// TODO :

	bool small = tbatiments.minLength() < 3000;
	bool big = tbatiments.maxLength() >= 5000;
	bool anglesAcceptable = tbatiments.minAngle() > Angle::d2r(30) && tbatiments.maxAngle() < Angle::d2r(120);

	if (!big && proba(seed, 0, 1, 20)) {
		addChild(new TerrainTri(tbatiments));
	} else if (small && anglesAcceptable) {
		addChild(new BatimentTri(tbatiments));
	} else {
		addChild(new TerrainTri(tbatiments));
	}
}
