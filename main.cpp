#include "all_includes.hh"

// TODO : bâtiments.
// TODO : split route en 2 triangles.
// TODO : split bâtiment en faces, puis en triangles.
// TODO : probabilités des différents types de bâtiments.
// TODO : midpoint displacement sur les probabilités des différents types de bâtiments.
// TODO : largeur des routes : ???

int main() {
	// Générer une tile de base
	Vertex ne(100, 100);
	Vertex sw(0, 0);
	RectangleRoutes r(ne, sw);
	r.subdivide();
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	return 0;
}
