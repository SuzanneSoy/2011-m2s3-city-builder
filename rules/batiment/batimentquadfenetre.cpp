#include "all_includes.hh"

BatimentQuadFenetre::BatimentQuadFenetre(Quad _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
}

void BatimentQuadFenetre::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height));
}

void BatimentQuadFenetre::triangulation() {
    // Vide laisse un trou à la place de la fenêtre.
}
