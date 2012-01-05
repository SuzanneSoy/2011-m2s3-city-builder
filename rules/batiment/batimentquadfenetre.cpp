#include "all_includes.hh"

BatimentQuadFenetre::BatimentQuadFenetre(Quad c, int height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadFenetre::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height));
}

void BatimentQuadFenetre::triangulation() {
    // Vide laisse un trou à la place de la fenêtre.
}
