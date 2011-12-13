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
	Vertex tne, tnw, tse, tsw, bne, bnw, bse, bsw;
	Quad q = Quad(ne,se,sw,nw);

	if(border == E) {
        q.offset(E,-15);
        addTriangle(new Triangle(q.corner[0] + Vertex(0,0,height), q.corner[3] + Vertex(0,0,height), q.corner[2] + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(q.corner[2] + Vertex(0,0,height), q.corner[1] + Vertex(0,0,height), q.corner[0] + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(ne + Vertex(0,0,height),q.corner[0] + Vertex(0,0,height), q.corner[1] + Vertex(0,0,height), 0xAA, 0xAA, 0xAA));
        addTriangle(new Triangle(q.corner[1] + Vertex(0,0,height), se + Vertex(0,0,height), ne + Vertex(0,0,height), 0xAA, 0xAA, 0xAA));

        addTriangle(new Triangle(nw + Vertex(0,0,height), nw, sw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + Vertex(0,0,height), nw + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(ne, ne + Vertex(0,0,height), se + Vertex(0,0,height), 0xAA, 0xAA, 0xAA));
        addTriangle(new Triangle(se + Vertex(0,0,height), se, ne, 0xAA, 0xAA, 0xAA));

        addTriangle(new Triangle(ne + Vertex(0,0,height), ne, nw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(nw, nw + Vertex(0,0,height), ne + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + Vertex(0,0,height), se + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(se + Vertex(0,0,height), se, sw, 0x66, 0x66, 0x66));
    }
    else {
        addTriangle(new Triangle(q.corner[0] + Vertex(0,0,height), q.corner[3] + Vertex(0,0,height), q.corner[2] + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(q.corner[2] + Vertex(0,0,height), q.corner[1] + Vertex(0,0,height), q.corner[0] + Vertex(0,0,height), 0x66, 0x66, 0x66));

        addTriangle(new Triangle(nw + Vertex(0,0,height), nw, sw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + Vertex(0,0,height), nw + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(ne, ne + Vertex(0,0,height), se + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(se + Vertex(0,0,height), se, ne, 0x66, 0x66, 0x66));

        addTriangle(new Triangle(ne + Vertex(0,0,height), ne, nw, 0x66, 0x66, 0x66));
        addTriangle(new Triangle(nw, nw + Vertex(0,0,height), ne + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(sw, sw + Vertex(0,0,height), se + Vertex(0,0,height), 0x66, 0x66, 0x66));
        addTriangle(new Triangle(se + Vertex(0,0,height), se, sw, 0x66, 0x66, 0x66));
    }
}
