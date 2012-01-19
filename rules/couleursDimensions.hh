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
				r(colorA) * mixA + r(colorB) * mixB,
				g(colorA) * mixA + g(colorB) * mixB,
				b(colorA) * mixA + b(colorB) * mixB
		);
	};
	static const unsigned int mur = 0xF1E3AD;
	static const unsigned int plafond = mur;
	static const unsigned int plancher = mur;
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
	static const unsigned int hauteurMaxBatiment = hauteurTrottoir + hauteurEtage + hauteurToit;
	static const unsigned int minSurfaceSousBatiment = 100 * 100*100; // 100 m²

	// Qualité
	// TODO : devrait être 5.f et 6.f
	static const unsigned int splitFactor = 2.f;
	static const unsigned int mergeFactor = 3.f;
	static const unsigned int windowWidth = 1024;
	static const unsigned int windowHeight = 768;
	static const float frontFrustum;
	static const float backFrustum;
};

#endif
