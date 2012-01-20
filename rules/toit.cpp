#include "all_includes.hh"

// TODO : les x.insetNESW_LTR(x.minLength() / 3.f) sont faux (on risque d'avoir un triangle plus petit qu'⅓), il faudrait une fonction inset qui prend un float entre 0 et 1.

ToitQuad::ToitQuad(Quad _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
}

void ToitQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c.offsetNormal(height));
}

void ToitQuad::triangulation() {
	if (c.maxAngle() > Angle::d2r(90+40) || c.minAngle() < Angle::d2r(90-40)) {
		plat();
		return;
	}
	switch (hash2(seed, -1) % 5) {
	case 0: pointCentral(); break;
	case 1: quatrePoints(); break;
	case 2: deuxPoints(); break;
	case 3: deuxPointsVerticaux(); break;
	case 4:
	default: plat(); break;
	}
}

void ToitQuad::pointCentral() {
	Quad qh = c.offsetNormal(height);
	Vertex center = qh.insetNESW(qh.minLength() / 3.f).randomPoint(seed, 0);
	for (int i = 0; i < 4; i++)
		addGPUTriangle(c[SE+i], center, c[NE+i], Couleurs::toit);
}

void ToitQuad::quatrePoints() {
	Quad ch = c.offsetNormal(height).insetNESW(c.minLength() / 3.f); // TODO : insetProportional
	addGPUQuad(ch, Couleurs::toit);
	for (int i = 0; i < 4; i++)
		addGPUQuad(ch[NE+i], c[NE+i], c[SE+i], ch[SE+i], Couleurs::toit);
}

void ToitQuad::deuxPoints() {
	// Orienter c dans le sens de la longueur d'est en ouest.
	Quad q = c >> ((c.maxLengthNS() > c.maxLengthEW()) ? 1 : 0);
	Quad qh = q.offsetNormal(height);

	float coef = height / Segment(q[NW],q[SW]).length();
    float eLength = Segment(q[NE],q[SE]).length();
    qh[NE] = q[NE] + Vertex(qh[NE]-q[NE]).setNorm(coef*eLength);
    qh[SE] = q[SE] + Vertex(qh[SE]-q[SE]).setNorm(coef*eLength);

	//Vertex w = Segment(qh[NW], qh[SW]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	//Vertex e = Segment(qh[NE], qh[SE]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);
	Vertex w = qh[SW] + Vertex(qh[NW] - qh[SW])/2;
	Vertex e = qh[SE] + Vertex(qh[NE] - qh[SE])/2;
	Vertex centerE = Segment(e,w).randomPos(seed, 2, 0.6f, 0.8f);
	Vertex centerW = Segment(e,w).randomPos(seed, 2, 0.2f, 0.4f);
	addGPUTriangle(q[SE], centerE, q[NE], Couleurs::toit);
	addGPUTriangle(q[NW], centerW, q[SW], Couleurs::toit);
	addGPUQuad(q[SE], q[SW], centerW, centerE, Couleurs::toit);
	addGPUQuad(q[NW], q[NE], centerE, centerW, Couleurs::toit);
}

void ToitQuad::deuxPointsVerticaux() {
	// Orienter c dans le sens de la longueur d'est en ouest.
	Quad q = c >> ((c.maxLengthNS() > c.maxLengthEW()) ? 1 : 0);
    Quad qh = q.offsetNormal(height);


	float coef = height / Segment(q[NW],q[SW]).length();
    float eLength = Segment(q[NE],q[SE]).length();
    qh[NE] = q[NE] + Vertex(qh[NE]-q[NE]).setNorm(coef*eLength);
    qh[SE] = q[SE] + Vertex(qh[SE]-q[SE]).setNorm(coef*eLength);

	//Vertex w = Segment(qh[NW], qh[SW]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	//Vertex e = Segment(qh[NE], qh[SE]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);
	Vertex w = qh[SW] + Vertex(qh[NW] - qh[SW])/2;
	Vertex e = qh[SE] + Vertex(qh[NE] - qh[SE])/2;




	addGPUTriangle(q[SE], e, q[NE], Couleurs::mur);
	addGPUTriangle(q[NW], w, q[SW], Couleurs::mur);
	addGPUQuad(q[SE], q[SW], w, e, Couleurs::toit);
	addGPUQuad(q[NW], q[NE], e, w, Couleurs::toit);
}

void ToitQuad::plat() {
	Quad ch = c.offsetNormal(Dimensions::hauteurToit * 0.6f);
	addGPUFourQuads(c, ch, Couleurs::toit);
	addGPUQuad(ch, Couleurs::toit);
}

ToitTri::ToitTri(Triangle _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
}

void ToitTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c.offsetNormal(height));
}

void ToitTri::triangulation() {
	if (c.maxAngle() > Angle::d2r(120) || c.minAngle() < Angle::d2r(30)) {
		plat();
		return;
	}
	plat(); return;
	switch (hash2(seed, -1) % 5) {
	case 0: pointCentral(); break;
	case 1: troisPoints(); break;
	case 2: unPointVertical(); break;
	case 3: deuxPointsVerticaux(); break;
	case 4:
	default: plat(); break;
	}
}

void ToitTri::pointCentral() {
	Triangle th = c.offsetNormal(height);
	Vertex center = th.insetLTR(th.minLength() / 3.f).randomPoint(seed, 0);
	for (int i = 0; i < 3; i++)
		addGPUTriangle(c[LEFT+i], center, c[TOP+i], Couleurs::toit);
}

void ToitTri::troisPoints() {
	Triangle th = c.offsetNormal(height).insetLTR(c.minLength() / 3.f);
	addGPUTriangle(th, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(c[LEFT+i], c[TOP+i], th[TOP+i], th[LEFT+i], Couleurs::toit);
}

void ToitTri::unPointVertical() {
	// Rotation aléatoire du triangle
	Triangle t = c >> (hash2(seed, 0) % 3);
	Triangle th = t.offsetNormal(height);
	addGPUTriangle(t[LEFT], th[TOP], t[RIGHT], Couleurs::toit);
	addGPUTriangle(t[TOP], th[TOP], t[LEFT], Couleurs::toit);
	addGPUTriangle(t[RIGHT], th[TOP], t[TOP], Couleurs::toit);
}

void ToitTri::deuxPointsVerticaux() {
	// Rotation aléatoire du triangle
	Triangle t = c >> (hash2(seed, 0) % 3);
	Triangle th = t.offsetNormal(height);
	addGPUTriangle(th[LEFT], t[TOP], th[RIGHT], Couleurs::toit);
	addGPUTriangle(t[TOP], th[LEFT], t[LEFT], Couleurs::toit);
	addGPUTriangle(t[RIGHT], th[RIGHT], t[TOP], Couleurs::toit);
}

void ToitTri::plat() {
	Triangle ch = c.offsetNormal(Dimensions::hauteurToit * 0.6f);
	addGPUThreeQuads(c, ch, Couleurs::toit);
	addGPUTriangle(c, Couleurs::toit);
}
