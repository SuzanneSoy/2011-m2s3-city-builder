#include "all_includes.hh"

BatimentQuadToit::BatimentQuadToit(Quad _c, int _type) : Chose(), c(_c), type(_type) {
	addEntropy(c);
}

void BatimentQuadToit::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

void BatimentQuadToit::triangulation() {
    if(type == 1) {
        if(c.minLengthNS() < c.minLengthEW())
            c = c << 1;
        c = c.inset(N, -20).inset(S,-20);
        height = c.minLengthEW() / 5;
        Vertex ce = c[SE] + (c[NE] - c[SE])/2 + Vertex(0,0,height);
        Vertex cw = c[SW] + (c[NW] - c[SW])/2 + Vertex(0,0,height);

        addGPUTriangle(c[NW],cw,c[SW],0xF1,0xE0,0xE0);
        addGPUTriangle(c[SE],ce,c[NE],0xF1,0xE0,0xE0);

        addGPUQuad(c[NE],c[NW],c[SW],c[SE],0xF1,0xE0,0xE0);
        addGPUQuad(c[NE],c[NW],cw,ce,0xE0,0x20,0x00);
        addGPUQuad(c[SW],c[SE],ce,cw,0xE0,0x20,0x00);
    }
}
