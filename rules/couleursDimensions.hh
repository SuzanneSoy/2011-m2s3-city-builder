#ifndef _RULES_COLULEURSDIMENSIONS_HH_
#define _RULES_COLULEURSDIMENSIONS_HH_

#include "all_includes.hh"

class Couleurs {
public:
	static unsigned int rgb(unsigned char r, unsigned char g, unsigned char b) {
		return r * 0x10000 | g* 0x100 | b;
	}
	static unsigned char r(unsigned int color) { return ((color >> 16) & 0xff); };
	static unsigned char g(unsigned int color) { return ((color >> 8) & 0xff); };
	static unsigned char b(unsigned int color) { return (color & 0xff); };
	static unsigned int mix(unsigned int colorA, unsigned int colorB, float mixA) {
		float mixB = 1 - mixA;
		return rgb(
				(unsigned char)(r(colorA) * mixA + r(colorB) * mixB),
				(unsigned char)(g(colorA) * mixA + g(colorB) * mixB),
				(unsigned char)(b(colorA) * mixA + b(colorB) * mixB)
		);
	};
	static const unsigned int mur = 0xF1E3AD;
	static const unsigned int plafond = 0xA39E8B;
	static const unsigned int plancher = 0xA5A079;
	static const unsigned int toit = 0x961618;
	static const unsigned int route = 0x363636;
	static const unsigned int trottoir = 0x666666;
	static const unsigned int bordureTrottoir = 0xAAAAAA;
	static const unsigned int herbe = 0x0c4010;
	static const unsigned int feuillage = 0x11AA22;
	static const unsigned int pomme = 0xAA2211;
	static const unsigned int tronc = 0x906050;
	static const unsigned int cielHaut = 0x3c14ff;
	static const unsigned int cielBas = 0x7F7FFF;
	static const unsigned int fog; // définie dans couleurs.cpp .
};

class Dimensions {
public:
	static const unsigned int largeurRoute = 200;
	static const unsigned int largeurTrottoir = 140;
	static const unsigned int hauteurEtage = 300;
	static const unsigned int maxEtages = 5;
	static const unsigned int hauteurToit = 200;
	static const unsigned int hauteurTrottoir = 20;
	static const unsigned int hauteurMaxBatiment = hauteurTrottoir + hauteurEtage * 2 + hauteurToit;
	static const unsigned int minSurfaceSousBatiment = 100 * 100*100; // 100 m²
	static const unsigned int minRayonPlace = 50 * 100; // 60 m
	static const unsigned int maxRayonPlace = 2 * minRayonPlace; // 60 m

	// Qualité
	static const float splitFactor;
	static const float mergeFactor;
	static const unsigned int windowWidth = 1024;
	static const unsigned int windowHeight = 768;
	static const float frontFrustum;
	static const float backFrustum;
};

#endif
