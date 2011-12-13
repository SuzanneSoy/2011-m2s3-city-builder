#include "all_includes.hh"

TrottoirQuadNormal::TrottoirQuadNormal(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height, Cardinal border) {
	this->ne = ne;
	this->nw = nw;
	this->se = se;
	this->sw = sw;
	this->height = height;
	this->border = border;
	triangulation();
}

bool TrottoirQuadNormal::subdivide() {
	// TODO
	return false;
}

void TrottoirQuadNormal::triangulation() {
	Vertex h = Vertex(0,0,height);
	Quad q = Quad(ne,se,sw,nw);

	if(border == E) {
        q.offset(E,-15);
        addTriangle(new Triangle(q.corner[0] + h, q.corner[3] + h, q.corner[2] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(q.corner[2] + h, q.corner[1] + h, q.corner[0] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(ne + h,q.corner[0] + h, q.corner[1] + h, 0xAA, 0xAA, 0xAA));
        addTriangle(new Triangle(q.corner[1] + h, se + h, ne + h, 0xAA, 0xAA, 0xAA));

        addTriangle(new Triangle(nw + h, nw, sw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + h, nw + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(ne, ne + h, se + h, 0xAA, 0xAA, 0xAA));
        addTriangle(new Triangle(se + h, se, ne, 0xAA, 0xAA, 0xAA));

        addTriangle(new Triangle(ne + h, ne, nw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(nw, nw + h, ne + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + h, se + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(se + h, se, sw, 0x66, 0x66, 0x66));
    }
    else {
        addTriangle(new Triangle(q.corner[0] + h, q.corner[3] + h, q.corner[2] + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(q.corner[2] + h, q.corner[1] + h, q.corner[0] + h, 0x66, 0x66, 0x66));

        addTriangle(new Triangle(nw + h, nw, sw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + h, nw + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(ne, ne + h, se + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(se + h, se, ne, 0x66, 0x66, 0x66));

        addTriangle(new Triangle(ne + h, ne, nw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(nw, nw + h, ne + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + h, se + h, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(se + h, se, sw, 0x66, 0x66, 0x66));
    }
}
