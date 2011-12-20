#include "all_includes.hh"

BatimentQuad::BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, Cardinal entry) : Chose(), ne(ne) {
	addEntropy(ne, se, sw, nw);
	this->entry = entry;
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    this->ne = ne-lctr;
    this->se = se-lctr;
    this-> sw = sw-lctr;
    this->nw = nw-lctr;
    triangulation();
}

BatimentQuad::~BatimentQuad() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

int BatimentQuad::width() { return this->ne.x - this->sw.x; }
int BatimentQuad::height() { return this->ne.y - this->sw.y; }

std::vector<Vertex*> BatimentQuad::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool BatimentQuad::split() {
    factory(1,1,ne,se,sw,nw);
	return true;
}

bool BatimentQuad::merge() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
    return true;
}

Chose* BatimentQuad::factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	int th = 20;        // Terrain height.
	Quad q = Quad(ne,se,sw,nw);
	seed = seed;
	n = n;
	th = th;
	q.offset(N,-140);
	q.offset(E,-140);
	q.offset(S,-140);
	q.offset(W,-140);
/*
	addChild(new TrottoirQuadNormal(lctr+ne,lctr+se,lctr+q.corner[1],lctr+q.corner[0],th,E));
    addChild(new TrottoirQuadNormal(lctr+se,lctr+sw,lctr+q.corner[2],lctr+q.corner[1],th,E));
    addChild(new TrottoirQuadNormal(lctr+sw,lctr+nw,lctr+q.corner[3],lctr+q.corner[2],th,E));
    addChild(new TrottoirQuadNormal(lctr+nw,lctr+ne,lctr+q.corner[0],lctr+q.corner[3],th,E));

    q.corner[0] = q.corner[0] + Vertex(0,0,th);
    q.corner[1] = q.corner[1] + Vertex(0,0,th);
    q.corner[2] = q.corner[2] + Vertex(0,0,th);
    q.corner[3] = q.corner[3] + Vertex(0,0,th);

    addChild(new BatimentQuadJardin(lctr+q.corner[0],lctr+q.corner[1],lctr+q.corner[2],lctr+q.corner[3]));

    q.offset(this->entry,-400);

	addChild(new BatimentQuadMaison(lctr+q.corner[0],lctr+q.corner[1],lctr+q.corner[2],lctr+q.corner[3]));
*/
    addChild(new BatimentQuadPont(lctr+q.corner[0],lctr+q.corner[1],lctr+q.corner[2],lctr+q.corner[3],300));
	return NULL;	// pour compilation, à virer.
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	Vertex neh = ne + Vertex(0,0,h);
	Vertex seh = se + Vertex(0,0,h);
	Vertex nwh = nw + Vertex(0,0,h);
	Vertex swh = sw + Vertex(0,0,h);
	Vertex toit = (neh + seh + nwh + swh) / 4 + Vertex(0,0,htoit);

	// 4 Murs
	addTriangle(new Triangle(neh,seh,ne,0xf1,0xe3,0xad)); addTriangle(new Triangle(seh,se,ne,0xf1,0xe3,0xad)); // ne-se-seh-neh
	addTriangle(new Triangle(seh,swh,se,0xf1,0xe3,0xad)); addTriangle(new Triangle(swh,sw,se,0xf1,0xe3,0xad)); // se-sw-swh-seh
	addTriangle(new Triangle(swh,nwh,sw,0xf1,0xe3,0xad)); addTriangle(new Triangle(nwh,nw,sw,0xf1,0xe3,0xad)); // sw-nw-nwh-swh
	addTriangle(new Triangle(nwh,neh,nw,0xf1,0xe3,0xad)); addTriangle(new Triangle(neh,ne,nw,0xf1,0xe3,0xad)); // nw-ne-neh-nwh

	// 1 Toit
	addTriangle(new Triangle(neh,toit,seh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(seh,toit,swh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(swh,toit,nwh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(nwh,toit,neh,0x9a,0x48,0x3c));
}
