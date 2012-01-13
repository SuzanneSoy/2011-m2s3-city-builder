#include "all_includes.hh"

ArcheQuad::ArcheQuad(Quad _c, float _height, float _start, float _end) : Chose(), c(_c), height(_height), start(_start), end(_end) {
	addEntropy(c);
	addEntropy(height);
}

bool ArcheQuad::split() {
	if (std::abs(end - start) < 0.01)
		return false;
	float mid = (start + end) / 2;
	addChild(new ArcheQuad(c, height, start, mid));
	addChild(new ArcheQuad(c, height, mid, end));
	return true;
}

void ArcheQuad::triangulation() {
	Quad che = c.offsetNormal(f(end) * height);
	Quad chw = c.offsetNormal(f(start) * height);
	addGPUOcto(c, Quad(che[NE], che[SE], chw[SW], chw[NW]), Couleurs::mur);
}

void ArcheQuad::getBoundingBoxPoints() {
	addBBPoints(c, height);
}

float ArcheQuad::f(float x) {
	switch(hash2(seed, 0) % 2){
	case 0: return ogive(x);
	case 1:
	default: return berceau(x);
	}
}

float ArcheQuad::ogive(float x) {
	return sin(acos(abs(x / 2.f) + 1.f/2.f));
}

float ArcheQuad::berceau(float x) {
	return sin(acos(x));
}
