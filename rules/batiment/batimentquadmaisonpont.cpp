#include "all_includes.hh"

BatimentQuadMaisonPont::BatimentQuadMaisonPont(Quad c, int height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadMaisonPont::getBoundingBoxPoints() {
    addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

bool BatimentQuadMaisonPont::split() {
    Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
    q.makeParallelogram();
    if(Segment(q.c[0],q.c[3]).length() < Segment(q.c[0],q.c[1]).length())
        q = Quad(q.c[1],q.c[2],q.c[3],q.c[0]);
    float partLength = Segment(q.c[0],q.c[3]).length() / 3;
    int partHeight = 2.5*height/3.;
    Quad qa = q;
    Quad qb = q;
    Quad qc = q;
    Quad qh = q;
    qa.offset(E,-2*partLength);
    qb.offset(W,-2*partLength);
    qc.offset(E, -partLength);
    qc.offset(W, -partLength);

    addChild(new BatimentQuadJardin(c << 1));
    addChild(new BatimentQuadBlock(qa >> 1,partHeight));
    addChild(new BatimentQuadBlock(qb >> 1,partHeight));
    addChild(new BatimentQuadBlock((qh + Vertex(0,0,partHeight)) >> 1,partHeight));
    addChild(new BatimentQuadPont(qc,partHeight));
    addChild(new BatimentQuadToit(qh + Vertex(0,0,2*partHeight),150));

	return true;
}

void BatimentQuadMaisonPont::triangulation() {
	//triangles.reserve(2);
	float h = 2.5*height/3.;
	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]).makeParallelogram();
	Quad qh = q + Vertex(0,0,h);

    addQuad(c,0x80,0x80,0x80);
    addOcto(q,qh,0xF1,0xE0,0xE0);

    Vertex ce = qh[SE] + (qh[NE] - qh[SE])/2 + Vertex(0,0,0.5*height/3.f);
    Vertex cw = qh[SW] + (qh[NW] - qh[SW])/2 + Vertex(0,0,0.5*height/3.f);

    addTriangle(new GPUTriangle(qh[SW],qh[NW],cw,0xF1,0xE0,0xE0));
    addTriangle(new GPUTriangle(qh[NE],qh[SE],ce,0xF1,0xE0,0xE0));

    addQuad(qh[NE],qh[NW],cw,ce,0xE0,0x20,0x00);
    addQuad(qh[SW],qh[SE],ce,cw,0xE0,0x20,0x00);
}
