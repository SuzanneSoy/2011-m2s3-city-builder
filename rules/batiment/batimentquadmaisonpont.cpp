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

    c[SE] = qa.corner[0];
    c[SW] = qa.corner[1];
    c[NW] = qa.corner[2];
    c[NE] = qa.corner[3];

    addChild(new BatimentQuadMaisonBlock(c[NE],c[SE],c[SW],c[NW],partHeight));

    c[SE] = qb.corner[0];
    c[SW] = qb.corner[1];
    c[NW] = qb.corner[2];
    c[NE] = qb.corner[3];

    addChild(new BatimentQuadMaisonBlock(c[NE],c[SE],c[SW],c[NW],partHeight));

    c[SE] = qh.corner[0] + Vertex(0,0,partHeight);
    c[SW] = qh.corner[1] + Vertex(0,0,partHeight);
    c[NW] = qh.corner[2] + Vertex(0,0,partHeight);
    c[NE] = qh.corner[3] + Vertex(0,0,partHeight);

    addChild(new BatimentQuadMaisonBlock(c[NE],c[SE],c[SW],c[NW],partHeight));

    c[SE] = qc.corner[0];
    c[SW] = qc.corner[1];
    c[NW] = qc.corner[2];
    c[NE] = qc.corner[3];

    addChild(new BatimentQuadPont(c[SE],c[SW],c[NW],c[NE],partHeight));
/*
    Vertex seh = qh.corner[0] + Vertex(0,0,partHeight);
    Vertex swh = qh.corner[1] + Vertex(0,0,partHeight);
    Vertex nwh = qh.corner[2] + Vertex(0,0,partHeight);
    Vertex neh = qh.corner[3] + Vertex(0,0,partHeight);

    Vertex ce = seh + (neh - seh)/2 + Vertex(0,0,0.5*height/3.);
    Vertex cw = swh + (nwh - swh)/2 + Vertex(0,0,0.5*height/3.);

    addTriangle(new Triangle(swh,nwh,cw,0xDD,0xDD,0xDD));
    addTriangle(new Triangle(neh,seh,ce,0xDD,0xDD,0xDD));

    addQuad(neh,nwh,cw,ce,0xE0,0x20,0x00);
    addQuad(swh,seh,ce,cw,0xE0,0x20,0x00);
*/
	return true;
}

void BatimentQuadMaisonPont::triangulation() {
	//triangles.reserve(2);
	float h = 2.5*height/3.;
    Vertex seh = c[SE] + Vertex(0,0,h);
    Vertex swh = c[SW] + Vertex(0,0,h);
    Vertex nwh = c[NW] + Vertex(0,0,h);
    Vertex neh = c[NE] + Vertex(0,0,h);

    addOcto(c[NE],c[SE],c[SW],c[NW],neh,seh,swh,nwh,0xDD,0xDD,0xDD);

    Vertex ce = seh + (neh - seh)/2 + Vertex(0,0,0.5*height/3.);
    Vertex cw = swh + (nwh - swh)/2 + Vertex(0,0,0.5*height/3.);

    addTriangle(new Triangle(swh,nwh,cw,0xDD,0xDD,0xDD));
    addTriangle(new Triangle(neh,seh,ce,0xDD,0xDD,0xDD));

    addQuad(neh,nwh,cw,ce,0xE0,0x20,0x00);
    addQuad(swh,seh,ce,cw,0xE0,0x20,0x00);

}
