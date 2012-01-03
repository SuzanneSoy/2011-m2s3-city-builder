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
	return false;
}

void TrottoirQuadNormal::triangulation() {
	Vertex h = Vertex(0,0,height);
	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);

	if(border == E) {
        q.offset(E,-15);
        addTriangle(new GPUTriangle(q.c[0] + h, q.c[3] + h, q.c[2] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(q.c[2] + h, q.c[1] + h, q.c[0] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[NE] + h,q.c[0] + h, q.c[1] + h, 0xAA, 0xAA, 0xAA));
        addTriangle(new GPUTriangle(q.c[1] + h, c[SE] + h, c[NE] + h, 0xAA, 0xAA, 0xAA));

        addTriangle(new GPUTriangle(c[NW] + h, c[NW], c[SW], 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[SW], c[SW] + h, c[NW] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[NE], c[NE] + h, c[SE] + h, 0xAA, 0xAA, 0xAA));
        addTriangle(new GPUTriangle(c[SE] + h, c[SE], c[NE], 0xAA, 0xAA, 0xAA));

        addTriangle(new GPUTriangle(c[NE] + h, c[NE], c[NW], 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[NW], c[NW] + h, c[NE] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[SW], c[SW] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[SE] + h, c[SE], c[SW], 0x66, 0x66, 0x66));
    }
    else {
        addTriangle(new GPUTriangle(q.c[0] + h, q.c[3] + h, q.c[2] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(q.c[2] + h, q.c[1] + h, q.c[0] + h, 0x66, 0x66, 0x66));

        addTriangle(new GPUTriangle(c[NW] + h, c[NW], c[SW], 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[SW], c[SW] + h, c[NW] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[NE], c[NE] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[SE] + h, c[SE], c[NE], 0x66, 0x66, 0x66));

        addTriangle(new GPUTriangle(c[NE] + h, c[NE], c[NW], 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[NW], c[NW] + h, c[NE] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[SW], c[SW] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addTriangle(new GPUTriangle(c[SE] + h, c[SE], c[SW], 0x66, 0x66, 0x66));
    }
}
