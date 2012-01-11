#include "all_includes.hh"

// TODO : les x.insetNESW_LTR(x.minLength() / 3.f) sont faux (on risque d'avoir un triangle plus petit qu'1/3), il faudrait une fonction inset qui prend un float entre 0 et 1.

ToitQuad::ToitQuad(Quad _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
}

void ToitQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c.offsetNormal(height));
}

void ToitQuad::triangulation() {
	switch (hash2(seed, -1) % 4) {
	case 0: pointCentral(); break;
	case 1: deuxPoints(); break;
	case 2: deuxPointsVerticaux();
	case 3:
	default: plat(); break;
	}
}

void ToitQuad::pointCentral() {
	Quad qh = c.offsetNormal(height);
	Vertex center = qh.insetNESW(qh.minLength() / 3.f).randomPoint(seed, 0);
	for (int i = 0; i < 4; i++)
		addGPUTriangle(c[NE+i], center, c[SE+i], r, g, b);
}

void ToitQuad::deuxPoints() {
	// Orienter c dans le sens de la longueur d'est en ouest.
	Quad q = c >> ((c.maxLengthNS() > c.maxLengthEW()) ? 1 : 0);
	Quad qh = q.offsetNormal(height);
	Vertex w = Segment(qh[NW], qh[SW]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	Vertex e = Segment(qh[NE], qh[SE]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);
	Vertex centerE = Segment(e,w).randomPos(seed, 2, 0.6f, 0.8f);
	Vertex centerW = Segment(e,w).randomPos(seed, 2, 0.2f, 0.4f);
	addGPUTriangle(q[NE], centerE, q[SE], r, g, b);
	addGPUTriangle(q[SW], centerW, q[NW], r, g, b);
	addGPUQuad(q[SE], q[SW], centerW, centerE, r, g, b);
	addGPUQuad(q[NW], q[NE], centerE, centerW, r, g, b);
}

void ToitQuad::deuxPointsVerticaux() {
	// Orienter c dans le sens de la longueur d'est en ouest.
	Quad q = c >> ((c.maxLengthNS() > c.maxLengthEW()) ? 1 : 0);
	Quad qh = q.offsetNormal(height);
	Vertex w = Segment(qh[NW], qh[SW]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	Vertex e = Segment(qh[NE], qh[SE]).randomPos(seed, 1, 1.f/3.f, 2.f/3.f);
	addGPUTriangle(q[NE], e, q[SE], r, g, b); // TODO : devrait être couleur mur.
	addGPUTriangle(q[SW], w, q[NW], r, g, b); // TODO : devrait être couleur mur.
	addGPUQuad(q[SE], q[SW], w, e, r, g, b);
	addGPUQuad(q[NW], q[NE], e, w, r, g, b);
}

void ToitQuad::plat() {
	addGPUQuad(c, r, g, b);
}

ToitTri::ToitTri(Triangle _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
}

void ToitTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c.offsetNormal(height));
}

void ToitTri::triangulation() {
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
		addGPUTriangle(c[LEFT+i], center, c[TOP+i], r, g, b);
}

void ToitTri::troisPoints() {
	Triangle th = c.offsetNormal(height).insetLTR(c.minLength() / 3.f);
	addGPUTriangle(th, r, g, b);
	for (int i = 0; i < 3; i++)
		addGPUQuad(c[LEFT], c[TOP], th[TOP], th[LEFT], r, g, b);
}

void ToitTri::unPointVertical() {
	// Rotation aléatoire du triangle
	Triangle t = c >> (hash2(seed, 0) % 3);
	Triangle th = t.offsetNormal(height);
	addGPUTriangle(t[LEFT], th[TOP], t[RIGHT], r, g, b);
	addGPUTriangle(t[TOP], th[TOP], t[LEFT], r, g, b);
	addGPUTriangle(t[RIGHT], th[TOP], t[TOP], r, g, b);
}

void ToitTri::deuxPointsVerticaux() {
	// Rotation aléatoire du triangle
	Triangle t = c >> (hash2(seed, 0) % 3);
	Triangle th = t.offsetNormal(height);
	addGPUTriangle(th[LEFT], t[TOP], th[RIGHT], r, g, b);
	addGPUTriangle(t[TOP], th[LEFT], t[LEFT], r, g, b);
	addGPUTriangle(t[RIGHT], th[RIGHT], t[TOP], r, g, b);
}

void ToitTri::plat() {
	addGPUTriangle(c, r, g, b);
}

