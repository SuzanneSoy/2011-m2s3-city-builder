#include "all_includes.hh"

// TODO : split bâtiment en faces, puis en triangles.
// TODO : probabilités des différents types de bâtiments.
// TODO : midpoint displacement sur les probabilités des différents types de bâtiments.
// TODO : largeur des routes : ???

void recursiveSubdivide(Chose* c) {
	if (c->subdivide()) {
		std::vector<Chose*>::iterator it;
		for (it = c->children.begin(); it != c->children.end(); ++it) {
			recursiveSubdivide(*it);
		}
	}
}

int main() {
	// Générer une tile de base
	Vertex ne(50, 50, 0);
	Vertex sw(0, 0, 0);
	Chose* c = new RectangleRoutes(ne, sw);
	recursiveSubdivide(c);

	new View(c);
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	return 0;
}
