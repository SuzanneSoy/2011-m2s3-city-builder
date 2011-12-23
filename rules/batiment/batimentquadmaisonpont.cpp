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
    if(Segment(q.corner[0],q.corner[3]).length() < Segment(q.corner[0],q.corner[1]).length())
        q = Quad(q.corner[1],q.corner[2],q.corner[3],q.corner[0]);
    float partLength = Segment(q.corner[0],q.corner[3]).length() / 3;
    int partHeight = 2.5*height/3.;
    Quad qa = q;
    Quad qb = q;
    Quad qc = q;
    Quad qh = q;
    qa.offset(E,-2*partLength);
    qb.offset(W,-2*partLength);
    qc.offset(E, -partLength);
    qc.offset(W, -partLength);

    Vertex se = qa.corner[0];
    Vertex sw = qa.corner[1];
    Vertex nw = qa.corner[2];
    Vertex ne = qa.corner[3];

    addChild(new BatimentQuadJardin(c[SE],c[SW],c[NW],c[NE]));
    addChild(new BatimentQuadBlock(ne,se,sw,nw,partHeight));

    se = qb.corner[0];
    sw = qb.corner[1];
    nw = qb.corner[2];
    ne = qb.corner[3];

    addChild(new BatimentQuadBlock(ne,se,sw,nw,partHeight));

    se = qh.corner[0] + Vertex(0,0,partHeight);
    sw = qh.corner[1] + Vertex(0,0,partHeight);
    nw = qh.corner[2] + Vertex(0,0,partHeight);
    ne = qh.corner[3] + Vertex(0,0,partHeight);

    addChild(new BatimentQuadBlock(ne,se,sw,nw,partHeight));

    se = qc.corner[0];
    sw = qc.corner[1];
    nw = qc.corner[2];
    ne = qc.corner[3];

    addChild(new BatimentQuadPont(se,sw,nw,ne,partHeight));

    Vertex seh = qh.corner[0] + Vertex(0,0,2*partHeight);
    Vertex swh = qh.corner[1] + Vertex(0,0,2*partHeight);
    Vertex nwh = qh.corner[2] + Vertex(0,0,2*partHeight);
    Vertex neh = qh.corner[3] + Vertex(0,0,2*partHeight);

    addChild(new BatimentQuadToit(seh,swh,nwh,neh,150));

	return true;
}

void BatimentQuadMaisonPont::triangulation() {
	//triangles.reserve(2);
	float h = 2.5*height/3.;
	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]).makeParallelogram();
    Vertex seh = q.corner[SE] + Vertex(0,0,h);
    Vertex swh = q.corner[SW] + Vertex(0,0,h);
    Vertex nwh = q.corner[NW] + Vertex(0,0,h);
    Vertex neh = q.corner[NE] + Vertex(0,0,h);

    addQuad(c[SE],c[SW],c[NW],c[NE],0x80,0x80,0x80);
    addOcto(q.corner[NE],q.corner[SE],q.corner[SW],q.corner[NW],neh,seh,swh,nwh,0xF1,0xE0,0xE0);

    Vertex ce = seh + (neh - seh)/2 + Vertex(0,0,0.5*height/3.);
    Vertex cw = swh + (nwh - swh)/2 + Vertex(0,0,0.5*height/3.);

    addTriangle(new Triangle(swh,nwh,cw,0xF1,0xE0,0xE0));
    addTriangle(new Triangle(neh,seh,ce,0xF1,0xE0,0xE0));

    addQuad(neh,nwh,cw,ce,0xE0,0x20,0x00);
    addQuad(swh,seh,ce,cw,0xE0,0x20,0x00);

}
