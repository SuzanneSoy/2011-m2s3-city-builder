#include "all_includes.hh"

BatimentQuadMaisonPont::BatimentQuadMaisonPont(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
	c[NE] = ne;
	c[SE] = se;
	c[SW] = sw;
	c[NW] = nw;
    this->height = height;
}

BatimentQuadMaisonPont::~BatimentQuadMaisonPont() {
    children.clear();
    triangles.clear();
}

void BatimentQuadMaisonPont::getBoundingBoxPoints() {
    addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,height)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,height));
	addBBPoint(c[SW] + Vertex(0,0,height));
	addBBPoint(c[NW] + Vertex(0,0,height));
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

    Vertex se = qa.c[0];
    Vertex sw = qa.c[1];
    Vertex nw = qa.c[2];
    Vertex ne = qa.c[3];

    addChild(new BatimentQuadJardin(c[SE],c[SW],c[NW],c[NE]));
    addChild(new BatimentQuadBlock(ne,se,sw,nw,partHeight));

    se = qb.c[0];
    sw = qb.c[1];
    nw = qb.c[2];
    ne = qb.c[3];

    addChild(new BatimentQuadBlock(ne,se,sw,nw,partHeight));

    se = qh.c[0] + Vertex(0,0,partHeight);
    sw = qh.c[1] + Vertex(0,0,partHeight);
    nw = qh.c[2] + Vertex(0,0,partHeight);
    ne = qh.c[3] + Vertex(0,0,partHeight);

    addChild(new BatimentQuadBlock(ne,se,sw,nw,partHeight));

    se = qc.c[0];
    sw = qc.c[1];
    nw = qc.c[2];
    ne = qc.c[3];

    addChild(new BatimentQuadPont(se,sw,nw,ne,partHeight));

    Vertex seh = qh.c[0] + Vertex(0,0,2*partHeight);
    Vertex swh = qh.c[1] + Vertex(0,0,2*partHeight);
    Vertex nwh = qh.c[2] + Vertex(0,0,2*partHeight);
    Vertex neh = qh.c[3] + Vertex(0,0,2*partHeight);

    addChild(new BatimentQuadToit(seh,swh,nwh,neh,150));

	return true;
}

void BatimentQuadMaisonPont::triangulation() {
	//triangles.reserve(2);
	float h = 2.5*height/3.;
	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]).makeParallelogram();
    Vertex seh = q.c[SE] + Vertex(0,0,h);
    Vertex swh = q.c[SW] + Vertex(0,0,h);
    Vertex nwh = q.c[NW] + Vertex(0,0,h);
    Vertex neh = q.c[NE] + Vertex(0,0,h);

    addQuad(c[SE],c[SW],c[NW],c[NE],0x80,0x80,0x80);
    addOcto(q.c[NE],q.c[SE],q.c[SW],q.c[NW],neh,seh,swh,nwh,0xF1,0xE0,0xE0);

    Vertex ce = seh + (neh - seh)/2 + Vertex(0,0,0.5*height/3.);
    Vertex cw = swh + (nwh - swh)/2 + Vertex(0,0,0.5*height/3.);

    addTriangle(new GPUTriangle(swh,nwh,cw,0xF1,0xE0,0xE0));
    addTriangle(new GPUTriangle(neh,seh,ce,0xF1,0xE0,0xE0));

    addQuad(neh,nwh,cw,ce,0xE0,0x20,0x00);
    addQuad(swh,seh,ce,cw,0xE0,0x20,0x00);

}
