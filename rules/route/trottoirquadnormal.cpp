#include "all_includes.hh"

TrottoirQuadNormal::TrottoirQuadNormal(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height, Cardinal border) {
    c[NE] = ne;
	c[SE] = se;
    c[SW] = sw;
    c[NW] = nw;
	this->height = height;
	this->border = border;
	// TODO : pas besoin de ce champ : il suffit d'orienter
	// correctement le trottoir lorsqu'on le crée.
}

TrottoirQuadNormal::~TrottoirQuadNormal() {
    children.clear();
    triangles.clear();
}

void TrottoirQuadNormal::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,height)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,height));
	addBBPoint(c[SW] + Vertex(0,0,height));
	addBBPoint(c[NW] + Vertex(0,0,height));
}

bool TrottoirQuadNormal::split() {
	// TODO
	return false;
}

void TrottoirQuadNormal::triangulation() {
	Vertex h = Vertex(0,0,height);
	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);

	if(border == E) {
        q.offset(E,-15);
        addTriangle(new Triangle(q.corner[0] + h, q.corner[3] + h, q.corner[2] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(q.corner[2] + h, q.corner[1] + h, q.corner[0] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[NE] + h,q.corner[0] + h, q.corner[1] + h, 0xAA, 0xAA, 0xAA));
        addTriangle(new Triangle(q.corner[1] + h, c[SE] + h, c[NE] + h, 0xAA, 0xAA, 0xAA));

        addTriangle(new Triangle(c[NW] + h, c[NW], c[SW], 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[SW], c[SW] + h, c[NW] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[NE], c[NE] + h, c[SE] + h, 0xAA, 0xAA, 0xAA));
        addTriangle(new Triangle(c[SE] + h, c[SE], c[NE], 0xAA, 0xAA, 0xAA));

        addTriangle(new Triangle(c[NE] + h, c[NE], c[NW], 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[NW], c[NW] + h, c[NE] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[SW], c[SW] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[SE] + h, c[SE], c[SW], 0x66, 0x66, 0x66));
    }
    else {
        addTriangle(new Triangle(q.corner[0] + h, q.corner[3] + h, q.corner[2] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(q.corner[2] + h, q.corner[1] + h, q.corner[0] + h, 0x66, 0x66, 0x66));

        addTriangle(new Triangle(c[NW] + h, c[NW], c[SW], 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[SW], c[SW] + h, c[NW] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[NE], c[NE] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[SE] + h, c[SE], c[NE], 0x66, 0x66, 0x66));

        addTriangle(new Triangle(c[NE] + h, c[NE], c[NW], 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[NW], c[NW] + h, c[NE] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[SW], c[SW] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(c[SE] + h, c[SE], c[SW], 0x66, 0x66, 0x66));
    }
}
