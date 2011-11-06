#include "vertex.hh"
#include "rules.hh"
#include "hash.hh"
#include "rules/rectangleroutes.hh"

int main() {
	// Générer une tile de base
	Vertex ne(100, 100);
	Vertex sw(0, 0);
	RectangleRoutes r(ne, sw, random());
	r.subdivide();
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	return 0;
}
