#include "all_includes.hh"

QuartierQuad_::QuartierQuad_(Quad _c) : c(_c) {
	addEntropy(c);
}

void QuartierQuad_::getBoundingBoxPoints() {
	addBBPoints(c, 6000); // TODO : factoriser cette longueur (hauteur max des bâtiments).
}

bool QuartierQuad_::split() {
	bool small = c.minLength() < 3500;
	bool big = c.maxLength() >= 6000;
	bool isConcave = c.maxAngle() > Angle::d2r(160);
	bool anglesOk = c.minAngle() > Angle::d2r(90-40) && c.maxAngle() < Angle::d2r(90+40);
	bool tooWideX = c.minLengthEW() * 2 < c.maxLengthNS(); // trop allongé (côté E ou W deux fois plus petit que le côté N ou S).
	bool tooWideY = c.minLengthNS() * 2 < c.maxLengthEW(); // trop allongé (côté N ou S deux fois plus petit que le côté E ou W).
	if (isConcave)
		concave();
	else if (!big && proba(seed, -1, 1, 20))
		batiments();
	else if (!small && !anglesOk)
		angleAngle(); // TODO
	else if (!small && tooWideY)
		rect(); // TODO : Quad(c[NW], c[NE], c[SE], c[SW])
	else if (!small && tooWideX)
		rect(); // TODO : fusion avec ci-dessus
	else if (!small)
		carre();
	else
		batiments();
	return true;
}

void QuartierQuad_::triangulation() {
	Quad ci = c.insetNESW(250 + 140); // TODO : factoriser cette longueur (largeur route + largeur trottoir).
	Quad cih = c.offsetNormal(6000); // TODO : factoriser cette longueur (hauteur max des bâtiments).
	addGPUQuad(c, 0x36, 0x36, 0x36); // TODO : factoriser cette couleur (couleur de la route).
	addGPUQuad(cih, 0xF1, 0xE0, 0xE0); // TODO : factoriser cette couleur (couleur des toits).
	for (int i = 0; i < 4; i++)
		addGPUQuad(Quad(ci[NE+i], ci[SE+i], cih[SE+i], cih[NE+i]), 0xF1, 0xE3, 0xAD); // TODO : factoriser cette couleur (couleur des murs des faux bâtiments).
}

void QuartierQuad_::concave() {
	// TODO
}

void QuartierQuad_::angleCote() {
	Quad q = c << c.maxAngleCorner();
	Vertex s = Segment(q[SE], q[SW]).randomPos(seed, 1, 0.4f, 0.6f);
	Vertex w = Segment(q[SW], q[NW]).randomPos(seed, 0, 0.4f, 0.6f);
	Triangle ts(q[SE], s, q[NE]);
	Triangle tw(q[NE], w, q[NW]);
	if (ts.minAngle() > tw.minAngle()) {
		addChild(new QuartierTri_(ts));
		addChild(new QuartierQuad_(Quad(q[NE], s, q[SW], q[NW])));
	} else {
		addChild(new QuartierTri_(tw));
		addChild(new QuartierQuad_(Quad(q[NE], q[SE], q[SW], w)));
	}
}

void QuartierQuad_::angleAngle() {
	Quad q = c << c.maxAngleCorner();
	addChild(new QuartierTri_(Triangle(q[NE], q[SE], q[SW])));
	addChild(new QuartierTri_(Triangle(q[SW], q[NW], q[NE])));
}

void QuartierQuad_::rect() {
	Vertex n = Segment(c[NW], c[NE]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	Vertex s = Segment(c[SE], c[SW]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);

	addChild(new QuartierQuad_(Quad(c[NE], c[SE], s, n)));
	addChild(new QuartierQuad_(Quad(c[SW], c[NW], n, s)));
}

void QuartierQuad_::carre() {
	// TODO : insetProportionnal();
	Vertex center = c.insetNESW(c.minLength() / 4.f).randomPoint(seed, 0);
	Vertex middle[4];
	for (int i = 0; i < 4; i++)
		middle[N+i] = Segment(c[NW+i], c[NE+i]).randomPos(seed, i + 1, 0.25, 0.75);

	for (int i = 0; i < 4; i++)
		addChild(new QuartierQuad_(Quad(c[NE+i], middle[E+i], center, middle[N+i])));
}

void QuartierQuad_::batiments() {
	float hauteurTrottoir = 20; // TODO : factoriser + ajouter ça à la hauteur max d'un bâtiment dans les autres calculs.
	Quad qtrottoir = c.insetNESW(250);
	Quad qinterieur = qtrottoir.insetNESW(140);
	Quad qbatiments = qinterieur.offsetNormal(hauteurTrottoir);

	for (int i = 0; i < 4; i++) {
		addChild(new RouteQuadChaussee(Quad(c[NE+i],c[SE+i],qtrottoir[SE+i],qtrottoir[NE+i])));
		addChild(new TrottoirQuadNormal(Quad(qtrottoir[NE+i],qtrottoir[SE+i],qinterieur[SE+i],qinterieur[NE+i]),hauteurTrottoir));
	}

	// TODO :

	bool small = c.minLength() < 2500;
	bool big = c.maxLength() >= 5000;
	bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);

	if (!big && proba(seed, 0, 1, 20)) {
		addChild(new TerrainQuadHerbe(qbatiments));
	} else if (small && anglesAcceptable) {
		addChild(new BatimentQuad(qbatiments));
	} else {
		addChild(new TerrainQuadHerbe(qbatiments));
	}
}

QuartierTri_::QuartierTri_(Triangle _c) : c(_c) {
	addEntropy(c);
}

void QuartierTri_::getBoundingBoxPoints() {
	addBBPoints(c, 6000); // TODO : factoriser cette longueur (hauteur max des bâtiments).
}

bool QuartierTri_::split() {
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

void QuartierTri_::triangulation() {
	Triangle ci = c.insetLTR(250 + 140); // TODO : factoriser cette longueur (largeur route + largeur trottoir).
	Triangle cih = c.offsetNormal(6000); // TODO : factoriser cette longueur (hauteur max des bâtiments).
	addGPUTriangle(c, 0x36, 0x36, 0x36); // TODO : factoriser cette couleur (couleur de la route).
	addGPUTriangle(cih, 0xF1, 0xE0, 0xE0); // TODO : factoriser cette couleur (couleur des toits).
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(ci[LEFT+i], ci[TOP+i], cih[TOP+i], cih[LEFT+i]), 0xF1, 0xE3, 0xAD); // TODO : factoriser cette couleur (couleur des murs des faux bâtiments).
}

void QuartierTri_::centre() {
	// TODO : maxLength / 6 au lieu de 1000
	// TODO : insetProportionnal();
	Vertex center = c.insetLTR(c.maxLength() / 6).randomPoint(seed, 0);
	Vertex edge[3];
	for (int i = 0; i < 3; i++)
		edge[LEFTSIDE+i] = Segment(c[LEFT+i], c[TOP+i]).randomPos(seed, i+1, 1.f/3.f, 2.f/3.f);

	for (int i = 0; i < 3; i++)
		addChild(new QuartierQuad_(Quad(c[TOP+i], edge[RIGHTSIDE+i], center, edge[LEFTSIDE+i])));
}

void QuartierTri_::hauteur() {
	Triangle t = c << c.maxAngleCorner();
	Vertex opposite = Segment(t[TOP], t[RIGHT]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);

	addChild(new QuartierTri_(Triangle(t[TOP], opposite, t[LEFT])));
	addChild(new QuartierTri_(Triangle(t[LEFT], opposite, t[RIGHT])));
}

void QuartierTri_::trapeze() {
	Triangle t = c << c.minAngleCorner();
	Vertex left = Segment(t[LEFT], t[TOP]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	Vertex base = Segment(t[RIGHT], t[LEFT]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);

	addChild(new QuartierTri_(Triangle(base, t[TOP], left)));
	addChild(new QuartierQuad_(Quad(left, t[TOP], t[RIGHT], base)));
}

void QuartierTri_::batiments() {
	float hauteurTrottoir = 20; // TODO : factoriser + ajouter ça à la hauteur max d'un bâtiment dans les autres calculs.
	Triangle ttrottoir = c.insetLTR(250);
	Triangle tinterieur = ttrottoir.insetLTR(140);
	Triangle tbatiments = tinterieur.offsetNormal(hauteurTrottoir);

	for (int i = 0; i < 3; i++) {
		addChild(new RouteQuadChaussee(Quad(c[LEFT+i],c[TOP+i],ttrottoir[TOP+i],ttrottoir[LEFT+i])));
		addChild(new TrottoirQuadNormal(Quad(ttrottoir[LEFT+i],ttrottoir[TOP+i],tinterieur[TOP+i],tinterieur[LEFT+i]),hauteurTrottoir));
	}

	// TODO :

	bool small = tbatiments.minLength() < 3000;
	bool big = tbatiments.maxLength() >= 5000;
	bool anglesAcceptable = tbatiments.minAngle() > Angle::d2r(30) && tbatiments.maxAngle() < Angle::d2r(120);

	if (!big && proba(seed, 0, 1, 20)) {
		addChild(new TerrainTriHerbe(tbatiments));
	} else if (small && anglesAcceptable) {
		addChild(new BatimentTri(tbatiments));
	} else {
		addChild(new TerrainTriHerbe(tbatiments));
	}
}
