#include "all_includes.hh"

Route::Route(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	triangulation();
}

bool Route::subdivide() {
	// TODO
	return false;
}

std::ostream& operator<<(std::ostream& os, const Route* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Route& r) {
	return os << "Route " << r.ne << "-" << r.se << "-" << r.sw << "-" << r.nw;
}

void Route::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(ne, nw, sw, 0x36, 0x36, 0x36));
	addTriangle(new Triangle(sw, se, ne, 0x36, 0x36, 0x36));
}

// Version avec trottoirs.
/*void Route::triangulation() {
	triangles.reserve(2);
	Vertex nne, nnw, nse, nsw;				// Nouvel emplacement de la route.
	
	nnw = nw + ((ne - nw)/6);
	nsw = sw + ((se - sw)/6);
	nne = ne - ((ne - nw)/6);
	nse = se - ((se - sw)/6);
	
	addChild(new TrottoirRoute(nnw, nsw, sw, nw, 20));
	addChild(new TrottoirRoute(ne, se, nse,  nne,20));
}*/
