#include "all_includes.hh"

BatimentQuadMaisonPont::BatimentQuadMaisonPont(Quad _c, int level) : Chose(), c(_c), level(level) {
	addEntropy(c);
	levelHeight = 300;
}

void BatimentQuadMaisonPont::getBoundingBoxPoints() {
    addBBPoints(c);
	addBBPoints(c + Vertex(10,10,level*levelHeight)); // TODO
}

bool BatimentQuadMaisonPont::split() {
    int ih;
    Quad q = c.makeParallelogram();
	if(Segment(q[NE],q[NW]).length() < Segment(q[NE],q[SE]).length())
        q = q << 1;
    float partLength = Segment(q[NE],q[NW]).length() / 3;
    Quad qa = q.inset(E,2*partLength);
    Quad qb = q.inset(W,2*partLength);
    Quad qc = q.inset(E, partLength).inset(W, partLength);
    Quad qh = q;

    addChild(new BatimentQuadJardin(c));
    addChild(new BatimentQuadBlock(qa,qa + Vertex(0,0,levelHeight)));
    addChild(new BatimentQuadBlock(qb,qb + Vertex(0,0,levelHeight)));
    for(ih=1;ih<level;ih++)
        addChild(new BatimentQuadBlock((qh + Vertex(0,0,ih*levelHeight)),qh + Vertex(0,0,(ih+1)*levelHeight)));
    //addChild(new BatimentQuadPont(qc,levelHeight));
    addChild(new BatimentQuadToit(qh + Vertex(0,0,(ih+1)*levelHeight),160));

	return true;
}

void BatimentQuadMaisonPont::triangulation() {
	float h = level*levelHeight / 3.f;
	Quad q = c.makeParallelogram();
	Quad qh = q + Vertex(0,0,h);
	float htoit = Segment(q[SE],q[NE]).length() / 5;

    addGPUQuad(c,0x808080);
    addGPUOcto(q,qh,Couleurs::mur);

    Vertex ce = qh[SE] + (qh[NE] - qh[SE])/2 + Vertex(0,0,htoit);
    Vertex cw = qh[SW] + (qh[NW] - qh[SW])/2 + Vertex(0,0,htoit);

    addGPUTriangle(qh[NW],cw,qh[SW],Couleurs::mur);
    addGPUTriangle(qh[SE],ce,qh[NE],Couleurs::mur);

    addGPUQuad(qh[NE],qh[NW],cw,ce,Couleurs::toit);
    addGPUQuad(qh[SW],qh[SE],ce,cw,Couleurs::toit);
}
