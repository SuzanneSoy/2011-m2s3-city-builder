#include "all_includes.hh"

RouteQuadCarrefour::RouteQuadCarrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne,se,sw,nw);
	triangulation();
}

RouteQuadCarrefour::~RouteQuadCarrefour() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

std::vector<Vertex*> RouteQuadCarrefour::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool RouteQuadCarrefour::split() {
	// TODO
	return false;
}

bool RouteQuadCarrefour::merge() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
    return true;
}

void RouteQuadCarrefour::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(ne, nw, sw, 0x36, 0x36, 0x36));
	addTriangle(new Triangle(sw, se, ne, 0x36, 0x36, 0x36));
}
