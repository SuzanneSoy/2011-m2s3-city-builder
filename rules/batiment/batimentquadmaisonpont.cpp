#include "all_includes.hh"

BatimentQuadMaisonPont::BatimentQuadMaisonPont() {
}

BatimentQuadMaisonPont::BatimentQuadMaisonPont(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    this->ne = ne-lctr;
    this->se = se-lctr;
    this-> sw = sw-lctr;
    this->nw = nw-lctr;
    this->height = height;
	triangulation();
}

BatimentQuadMaisonPont::~BatimentQuadMaisonPont() {
    children.clear();
    triangles.clear();
}

void BatimentQuadMaisonPont::getBoundingBoxPoints() {
	// TODO
}

bool BatimentQuadMaisonPont::split() {

    Quad q = Quad(ne,se,sw,nw);
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

    se = lctr+qa.corner[0];
    sw = lctr+qa.corner[1];
    nw = lctr+qa.corner[2];
    ne = lctr+qa.corner[3];

    addChild(new BatimentQuadMaisonBlock(ne,se,sw,nw,partHeight));

    se = lctr+qb.corner[0];
    sw = lctr+qb.corner[1];
    nw = lctr+qb.corner[2];
    ne = lctr+qb.corner[3];

    addChild(new BatimentQuadMaisonBlock(ne,se,sw,nw,partHeight));

    se = lctr+qh.corner[0] + Vertex(0,0,partHeight);
    sw = lctr+qh.corner[1] + Vertex(0,0,partHeight);
    nw = lctr+qh.corner[2] + Vertex(0,0,partHeight);
    ne = lctr+qh.corner[3] + Vertex(0,0,partHeight);

    addChild(new BatimentQuadMaisonBlock(ne,se,sw,nw,partHeight));

    se = lctr+qc.corner[0];
    sw = lctr+qc.corner[1];
    nw = lctr+qc.corner[2];
    ne = lctr+qc.corner[3];

    addChild(new BatimentQuadPont(se,sw,nw,ne,partHeight));
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

bool BatimentQuadMaisonPont::merge() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
    return true;
}

void BatimentQuadMaisonPont::triangulation() {
	//triangles.reserve(2);
	float h = 2.5*height/3.;
    Vertex seh = se + Vertex(0,0,h);
    Vertex swh = sw + Vertex(0,0,h);
    Vertex nwh = nw + Vertex(0,0,h);
    Vertex neh = ne + Vertex(0,0,h);

    addOcto(ne,se,sw,nw,neh,seh,swh,nwh,0xDD,0xDD,0xDD);

    Vertex ce = seh + (neh - seh)/2 + Vertex(0,0,0.5*height/3.);
    Vertex cw = swh + (nwh - swh)/2 + Vertex(0,0,0.5*height/3.);

    addTriangle(new Triangle(swh,nwh,cw,0xDD,0xDD,0xDD));
    addTriangle(new Triangle(neh,seh,ce,0xDD,0xDD,0xDD));

    addQuad(neh,nwh,cw,ce,0xE0,0x20,0x00);
    addQuad(swh,seh,ce,cw,0xE0,0x20,0x00);

}
