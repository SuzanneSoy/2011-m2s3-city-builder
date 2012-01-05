#include "all_includes.hh"

BatimentQuadMaisonPont::BatimentQuadMaisonPont(Quad c, int height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadMaisonPont::getBoundingBoxPoints() {
    addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

bool BatimentQuadMaisonPont::split() {
    Quad q = c;
    q.makeParallelogram();
	if(Segment(q[NE],q[NW]).length() < Segment(q[NE],q[SE]).length())
        q = q << 1;
    float partLength = Segment(q[NE],q[NW]).length() / 3;
    int partHeight = 2.5*height/3.;
    Quad qa = q;
    Quad qb = q;
    Quad qc = q;
    Quad qh = q;
    qa.offset(E,-2*partLength);
    qb.offset(W,-2*partLength);
    qc.offset(E, -partLength);
    qc.offset(W, -partLength);

    addChild(new BatimentQuadJardin(c));
    addChild(new BatimentQuadBlock(qa,partHeight));
    addChild(new BatimentQuadBlock(qb,partHeight));
    addChild(new BatimentQuadBlock((qh + Vertex(0,0,partHeight)),partHeight));
    addChild(new BatimentQuadPont(qc,partHeight));
    addChild(new BatimentQuadToit(qh + Vertex(0,0,2*partHeight),150));

	return true;
}

void BatimentQuadMaisonPont::triangulation() {
	float h = 2.5*height/3.;
	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]).makeParallelogram();
	Quad qh = q + Vertex(0,0,h);

    addGPUQuad(c,0x80,0x80,0x80);
    addGPUOcto(q,qh,0xF1,0xE0,0xE0);

    Vertex ce = qh[SE] + (qh[NE] - qh[SE])/2 + Vertex(0,0,0.5*height/3.f);
    Vertex cw = qh[SW] + (qh[NW] - qh[SW])/2 + Vertex(0,0,0.5*height/3.f);

    addGPUTriangle(qh[NW],cw,qh[SW],0xF1,0xE0,0xE0);
    addGPUTriangle(qh[SE],ce,qh[NE],0xF1,0xE0,0xE0);

    addGPUQuad(qh[NE],qh[NW],cw,ce,0xE0,0x20,0x00);
    addGPUQuad(qh[SW],qh[SE],ce,cw,0xE0,0x20,0x00);
}
