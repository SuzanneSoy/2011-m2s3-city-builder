#include "all_includes.hh"

// TODO : probabilités des différents types de bâtiments.
// TODO : midpoint displacement sur les probabilités des différents types de bâtiments.
// TODO : largeur des routes : ???

// Quadrilatere(corner[4])
//  -> croix de routes
//  -> bâtiment
//  -> bâtiment dans le "bout" le plus "étroit", et lignes  dans une seule direction dans le reste.

void recursiveSubdivide(Chose* c) {
	if (c->split()) {
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
	Chose::initialSeed = 1889676033;
	Chose* c = QuartierQuad::factory(Chose::initialSeed, 0, ne, se, sw, nw);
	c->triangulation();
	c->updateAABB();
	c->drawAABB();
	// c->split();
	// recursiveSubdivide(c);
	
	// Heap h(1);
	// (void)h;
	// h.insert(43,c);
	// h.insert(42,c->children[0]);
	// h.popIfLessThan(42); // NULL
	// h.popIfLessThan(43); // c->children[0]
	// h.popIfLessThan(44); // c
	// h.popIfLessThan(44); // NULL
	
	new View(c);
	// Vertex cc = v->camera.cameraCenter;
	// float camera[3] = {cc.x, cc.y, cc.z};
	// Lod lod(camera);
	return 0;
}
