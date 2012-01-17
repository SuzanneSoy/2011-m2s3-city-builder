#include "all_includes.hh"

int main() {
	// Générer une tile de base
	std::cout << "Initial seed = " << Chose::initialSeed << std::endl;
	float size = 200 * 100;
	Vertex ne(size, size, 0);
	Vertex se(size, 0, 0);
	Vertex sw(0, 0, 0);
	Vertex nw(0, size, 0);
	Chose* c = new QuartierQuad(Quad(ne, se, sw, nw));
	c->triangulation();
	c->updateAABB();

	WallVertex* wvne = new WallVertex(ne);
	WallVertex* wvse = new WallVertex(se);
	WallVertex* wvsw = new WallVertex(sw);
	WallVertex* wvnw = new WallVertex(nw);
	Wall* wn = new Wall(wvnw,wvne);
	Wall* we = new Wall(wvne,wvse);
	Wall* ws = new Wall(wvse,wvsw);
	Wall* ww = new Wall(wvsw,wvnw);
	WallVertex* wvn = wn->randomPos(Chose::initialSeed, 0, 1.f/3.f, 2.f/3.f);
	WallVertex* wvs = ws->randomPos(Chose::initialSeed, 1, 1.f/3.f, 2.f/3.f);
	Wall* cut = new Wall(wvn, wvs);
	Wall* cut2 = new Wall(wvn, wvse);

	Wall::iterator it;
	for (it = wn->begin(); it != wn->end(); ++it)
		std::cout << (Vertex)(*(*it)) << std::endl;

	(void) wn;
	(void) we;
	(void) ws;
	(void) ww;
	(void) wvn;
	(void) wvs;
	(void) cut;
	(void) cut2;

	new View(c);
	return 0;
}
