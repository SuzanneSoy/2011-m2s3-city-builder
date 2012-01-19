#include "all_includes.hh"

ArcheQuad::ArcheQuad(Quad _c, float _height, float _start, float _end) : Chose(), c(_c), height(_height), start(_start), end(_end) {
	addEntropy(c);
	addEntropy(height);
}

bool ArcheQuad::split() {
	if (std::abs(end - start) < 0.1 && std::abs(f(end) - f(start)) < 0.05)
		return false;
	float mid = (start + end) / 2;
	Vertex n = (c[NW] + c[NE]) / 2.f;
	Vertex s = (c[SE] + c[SW]) / 2.f;
	addChild(new ArcheQuad(Quad(n, s, c[SW], c[NW]), height, start, mid));
	addChild(new ArcheQuad(Quad(c[NE], c[SE], s, n), height, mid, end));
	return true;
}

void ArcheQuad::triangulation() {
	Quad ch = c.offsetNormal(height);
	Quad che = c.offsetNormal(f(end) * height * 0.9);
	Quad chw = c.offsetNormal(f(start) * height * 0.9);
	addGPUQuad(Quad(ch[NW], chw[NW], che[NE], ch[NE]), Couleurs::mur);
	addGPUQuad(Quad(ch[SE], che[SE], chw[SW], ch[SW]), Couleurs::mur);
	addGPUQuad(Quad(che[SE], che[NE], chw[NW], chw[SW]), Couleurs::cielHaut);
	/*
	// Doivent être dessiné par le bâtiment englobant.
	if (start == 0)
		addGPUQuad(Quad(c[SW], c[NW], chw[NW], chw[SW]), Couleurs::mur);
	if (end == 1)
		addGPUQuad(Quad(c[NE], c[SE], che[SE], che[NE]), Couleurs::mur);
	*/
}

void ArcheQuad::getBoundingBoxPoints() {
	addBBPoints(c, height);
}

float ArcheQuad::f(float x) {
	return berceau(x);
	switch(hash2(seed, 0) % 2){
	case 0: return ogive(x);
	case 1:
	default: return berceau(x);
	}
}

float ArcheQuad::ogive(float x) {
	// TODO : mettre x à l'échelle
	return sin(acos(abs(x / 2.f) + 1.f/2.f));
}

float ArcheQuad::berceau(float x) {
	return sin(acos(2*x-1));
}
