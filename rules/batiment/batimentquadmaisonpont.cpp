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
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

std::vector<Vertex*> BatimentQuadMaisonPont::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool BatimentQuadMaisonPont::split() {

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
    Quad q = Quad(ne,se,sw,nw);
    q.makeParallelogram();
    if(Segment(q.corner[0],q.corner[3]).length() < Segment(q.corner[0],q.corner[1]).length())
        q = Quad(q.corner[1],q.corner[2],q.corner[3],q.corner[0]);
    float partLength = Segment(q.corner[0],q.corner[3]).length() / 3;
    int partHeight = 300;
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

    Vertex seh = se + Vertex(0,0,partHeight);
    Vertex swh = sw + Vertex(0,0,partHeight);
    Vertex nwh = nw + Vertex(0,0,partHeight);
    Vertex neh = ne + Vertex(0,0,partHeight);

    addOcto(ne,se,sw,nw,neh,seh,swh,nwh,0xFF,0x30,0x00);

    se = lctr+qb.corner[0];
    sw = lctr+qb.corner[1];
    nw = lctr+qb.corner[2];
    ne = lctr+qb.corner[3];

    seh = se + Vertex(0,0,partHeight);
    swh = sw + Vertex(0,0,partHeight);
    nwh = nw + Vertex(0,0,partHeight);
    neh = ne + Vertex(0,0,partHeight);

    addOcto(ne,se,sw,nw,neh,seh,swh,nwh,0xFF,0x30,0x00);

    se = lctr+qh.corner[0] + Vertex(0,0,partHeight);
    sw = lctr+qh.corner[1] + Vertex(0,0,partHeight);
    nw = lctr+qh.corner[2] + Vertex(0,0,partHeight);
    ne = lctr+qh.corner[3] + Vertex(0,0,partHeight);

    seh = se + Vertex(0,0,partHeight);
    swh = sw + Vertex(0,0,partHeight);
    nwh = nw + Vertex(0,0,partHeight);
    neh = ne + Vertex(0,0,partHeight);

    addOcto(ne,se,sw,nw,neh,seh,swh,nwh,0xFF,0x30,0x00);
}
