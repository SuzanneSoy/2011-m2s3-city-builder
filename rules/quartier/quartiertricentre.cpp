#include "all_includes.hh"

QuartierTriCentre::QuartierTriCentre(Triangle c) : QuartierTri(c) {
}

bool QuartierTriCentre::split() {
	// TODO : maxLength / 6 au lieu de 1000
	Vertex center = c.insetLTR(1000).randomPoint(seed, 0);
	Vertex edgePoint[3];
	for (int i = 0; i < 3; i++)
		edgePoint[LEFTSIDE+i] = Segment(c[LEFT+i], c[TOP+i]).randomPos(seed, i+1, 33, 67);

	Quad q[3];
	for (int i = 0; i < 3; i++) {
		q[i] = Quad(c[TOP+i], edgePoint[RIGHTSIDE+i], center, edgePoint[LEFTSIDE+i]);
		q[i] = q[i].inset(S, hrw).inset(W, hrw);
	}

	for (int i = 0; i < 3; i++) {
		addChild(QuartierQuad::factory(seed, i+4, q[i]));
		addChild(new RouteQuadChaussee(Quad(q[(i+1)%3][NW], q[(i+1)%3][SW], q[i][SW], q[i][SE])));
	}
	addChild(new RouteTriChaussee(Triangle(q[0][SW], q[1][SW], q[2][SW])));
	return true;
}
