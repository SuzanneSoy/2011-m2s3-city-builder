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
	triangles.reserve(10);
	Vertex nne, nnw, nse, nsw;				// Nouvel emplacement de la route.
	Vertex pvLne, pvLnw, pvLsw, pvLse;		// Trottoir Nord (pv => pavement)
	Vertex pvRne, pvRnw, pvRsw, pvRse;		// Trottoir Sud (pv => pavement)
	Vertex pvLCne, pvLCnw, pvLCsw, pvLCse;	// Rebord du trottoir gauche.
	Vertex pvRCne, pvRCnw, pvRCsw, pvRCse;	// rebord du trottoir droit.
	
	pvLnw = nw + Vertex(0,0,20);
	pvLsw = sw + Vertex(0,0,20);
	pvRne = ne + Vertex(0,0,20);
	pvRse = se + Vertex(0,0,20);
	pvLne = nw + ((ne - nw)/6);
	pvLse = sw + ((se - sw)/6);
	pvRnw = ne - ((ne - nw)/6);
	pvRsw = se - ((se - sw)/6);
	nnw = pvLne;
	nsw = pvLse;
	nne = pvRnw;
	nse = pvRsw;
	pvLne.z += 20;
	pvLse.z += 20;
	pvRnw.z += 20;
	pvRsw.z += 20;
	pvLCnw = pvLne;
	pvLCsw = pvLse;
	pvLCne = nnw;
	pvLCse = nsw;
	pvRCnw = nne;
	pvRCsw = nse;
	pvRCne = pvRnw;
	pvRCse = pvRsw;

	
	addTriangle(new Triangle(pvLne, pvLnw, pvLsw, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(pvLsw, pvLse, pvLne, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(pvRne, pvRnw, pvRsw, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(pvRsw, pvRse, pvRne, 0x66, 0x66, 0x66));
	
	addTriangle(new Triangle(pvLCne, pvLCnw, pvLCsw, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(pvLCsw, pvLCse, pvLCne, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(pvRCne, pvRCnw, pvRCsw, 0x66, 0x66, 0x66));
	addTriangle(new Triangle(pvRCsw, pvRCse, pvRCne, 0x66, 0x66, 0x66));
	
	addTriangle(new Triangle(nne, nnw, nsw, 0x36, 0x36, 0x36));
	addTriangle(new Triangle(nsw, nse, nne, 0x36, 0x36, 0x36));	
}
