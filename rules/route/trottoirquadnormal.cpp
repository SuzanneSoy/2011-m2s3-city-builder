#include "all_includes.hh"

TrottoirQuadNormal::TrottoirQuadNormal(Quad c, int height, Cardinal border) : Chose(), c(c), height(height), border(border) {
}

void TrottoirQuadNormal::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

void TrottoirQuadNormal::triangulation() {
	Vertex h = Vertex(0,0,height);
	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);

	if(border == E) {
        q.offset(E,-15);
        addGPUTriangle(new GPUTriangle(q.c[0] + h, q.c[3] + h, q.c[2] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(q.c[2] + h, q.c[1] + h, q.c[0] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[NE] + h, q.c[0] + h, q.c[1] + h, 0xAA, 0xAA, 0xAA));
        addGPUTriangle(new GPUTriangle(q.c[1] + h, c[SE] + h, c[NE] + h, 0xAA, 0xAA, 0xAA));

        addGPUTriangle(new GPUTriangle(c[NW] + h, c[NW], c[SW], 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[SW], c[SW] + h, c[NW] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[NE], c[NE] + h, c[SE] + h, 0xAA, 0xAA, 0xAA));
        addGPUTriangle(new GPUTriangle(c[SE] + h, c[SE], c[NE], 0xAA, 0xAA, 0xAA));

        addGPUTriangle(new GPUTriangle(c[NE] + h, c[NE], c[NW], 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[NW], c[NW] + h, c[NE] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[SW], c[SW] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[SE] + h, c[SE], c[SW], 0x66, 0x66, 0x66));
    } else {
        addGPUTriangle(new GPUTriangle(q.c[0] + h, q.c[3] + h, q.c[2] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(q.c[2] + h, q.c[1] + h, q.c[0] + h, 0x66, 0x66, 0x66));

        addGPUTriangle(new GPUTriangle(c[NW] + h, c[NW], c[SW], 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[SW], c[SW] + h, c[NW] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[NE], c[NE] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[SE] + h, c[SE], c[NE], 0x66, 0x66, 0x66));

        addGPUTriangle(new GPUTriangle(c[NE] + h, c[NE], c[NW], 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[NW], c[NW] + h, c[NE] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[SW], c[SW] + h, c[SE] + h, 0x66, 0x66, 0x66));
        addGPUTriangle(new GPUTriangle(c[SE] + h, c[SE], c[SW], 0x66, 0x66, 0x66));
    }
}
