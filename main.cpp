#include "all_includes.hh"

// TODO : probabilités des différents types de bâtiments.
// TODO : midpoint displacement sur les probabilités des différents types de bâtiments.
// TODO : largeur des routes : ???

// Quadrilatere(corner[4])
//  -> croix de routes
//  -> bâtiment
//  -> bâtiment dans le "bout" le plus "étroit", et lignes  dans une seule direction dans le reste.

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
	Vertex nw(0, size, 0);
	Chose* c = QuartierQuad::factory(Chose::initialSeed, 0, ne, se, sw, nw);
	// c->subdivide();
	recursiveSubdivide(c);

	View *v = new View(c);
	Vertex cc = v->camera.cameraCenter;
	float camera[3] = {cc.x, cc.y, cc.z};
	camera[0] = camera[0];
	Lod lod;
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	return 0;
}
