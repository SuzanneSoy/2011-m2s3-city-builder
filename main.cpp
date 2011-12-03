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
	std::cout << "Initial seed = " << Chose::initialSeed << std::endl;
	int size = 20000;
	Vertex ne(size, size, 0);
	Vertex se(size, 0, 0);
	Vertex sw(0, 0, 0);
	Vertex nw(0, size*2, 0);
	Chose* c = new QuadRoutes(ne,se,sw,nw);
	// c->subdivide();
	recursiveSubdivide(c);

	new View(c);
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	return 0;
}
