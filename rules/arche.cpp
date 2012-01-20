#include "all_includes.hh"

ArcheQuad::ArcheQuad(Quad _c, float _height, float _start, float _end, Type _type) : Chose(), c(_c), height(_height), start(_start), end(_end), type(_type) {
	if (type == RANDOM) {
		addEntropy(c);
		addEntropyf(height);
		switch (hash2(seed, 0) % 3) {
		case 0: type = OGIVE; break;
		case 1: type = BERCEAU; break;
		case 2:
		default: type = PLAT; break;
		}
	}
}

bool ArcheQuad::split() {
	if (type == PLAT)
		return false;
	if (std::abs(end - start) < 0.1 && std::abs(f(end) - f(start)) < 0.05)
		return false;
	float mid = (start + end) / 2;
	Vertex n = (c[NW] + c[NE]) / 2.f;
	Vertex s = (c[SE] + c[SW]) / 2.f;
	addChild(new ArcheQuad(Quad(n, s, c[SW], c[NW]), height, start, mid, type));
	addChild(new ArcheQuad(Quad(c[NE], c[SE], s, n), height, mid, end, type));
	return true;
}

void ArcheQuad::triangulation() {
	Quad ch = c.offsetNormal(height);
	Quad che = c.offsetNormal(f(end) * height * 0.9f);
	Quad chw = c.offsetNormal(f(start) * height * 0.9f);
	addGPUQuad(Quad(ch[NW], chw[NW], che[NE], ch[NE]), Couleurs::mur);
	addGPUQuad(Quad(ch[SE], che[SE], chw[SW], ch[SW]), Couleurs::mur);
	addGPUQuad(Quad(che[SE], che[NE], chw[NW], chw[SW]), Couleurs::mur);
}

void ArcheQuad::getBoundingBoxPoints() {
	addBBPoints(c, height);
}

float ArcheQuad::f(float x) {
	switch(type){
	case OGIVE: return std::sin(std::acos(std::abs(x - 0.5f) + 0.5f)) / std::sin(std::acos(0.5f));
	case BERCEAU: return std::sin(std::acos(2*x-1));
	case PLAT:
	default: return 1;
	}
}
