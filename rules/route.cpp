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

/*
void Route::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(ne, nw, sw, 0x36, 0x36, 0x36));
	addTriangle(new Triangle(sw, se, ne, 0x36, 0x36, 0x36));
}*/

// Version avec trottoirs.
void Route::triangulation() {
	triangles.reserve(6);
	Vertex nne, nnw, nse, nsw;				// Nouvel emplacement de la route.
	Vertex pvLne, pvLnw, pvLsw, pvLse;		// Trottoir Nord (pv => pavement)
	Vertex pvRne, pvRnw, pvRsw, pvRse;		// Trottoir Sud (pv => pavement)
	
	pvLnw = nw;
	pvLsw = sw;
	pvRne = ne;
	pvRse = se;
	pvLne = nw + ((ne - nw)/6);
	pvLse = sw + ((se - sw)/6);
	pvRnw = ne - ((ne - nw)/6);
	pvRsw = se - ((se - sw)/6);
	nnw = pvLne;
	nsw = pvLse;
	nne = pvRnw;
	nse = pvRsw;
	
	addTriangle(new Triangle(pvLne, pvLnw, pvLsw, 0xEE, 0xEE, 0x00));
	addTriangle(new Triangle(pvLsw, pvLse, pvLne, 0xEE, 0xEE, 0x00));
	addTriangle(new Triangle(pvRne, pvRnw, pvRsw, 0xEE, 0xEE, 0x00));
	addTriangle(new Triangle(pvRsw, pvRse, pvRne, 0xEE, 0xEE, 0x00));
	
	addTriangle(new Triangle(nne, nnw, nsw, 0x36, 0x36, 0x36));
	addTriangle(new Triangle(nsw, nse, nne, 0x36, 0x36, 0x36));	
}
