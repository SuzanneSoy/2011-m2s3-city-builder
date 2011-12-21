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
	int rand = this->seed % 20;

	if(rand <= 2) {
        Quad q = Quad(ne,se,sw,nw).makeParallelogram();
        addChild(new BatimentQuadMaisonPont(lctr+q.corner[0],lctr+q.corner[1],lctr+q.corner[2],lctr+q.corner[3],600));
	}
	else if(rand <= 15) {
        int th = 20;        // Terrain height.
        Quad q = Quad(ne,se,sw,nw);
        seed = seed;
        n = n;
        th = th;
        q.offset(N,-140);
        q.offset(E,-140);
        q.offset(S,-140);
        q.offset(W,-140);

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
	}

	return NULL;	// pour compilation, à virer.
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	h += htoit;
	Vertex neh = ne + Vertex(0,0,h);
	Vertex seh = se + Vertex(0,0,h);
	Vertex nwh = nw + Vertex(0,0,h);
	Vertex swh = sw + Vertex(0,0,h);

    addOcto(lctr+ne,lctr+se,lctr+sw,lctr+nw,lctr+neh,lctr+seh,lctr+swh,lctr+nwh,0xFF,0xFF,0x00);
}
