#include "all_includes.hh"

BatimentQuadPont::BatimentQuadPont() {
}

BatimentQuadPont::BatimentQuadPont(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    this->ne = ne-lctr;
    this->se = se-lctr;
    this-> sw = sw-lctr;
    this->nw = nw-lctr;
    this->height = height;
	triangulation();
}

BatimentQuadPont::~BatimentQuadPont() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

std::vector<Vertex*> BatimentQuadPont::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool BatimentQuadPont::split() {

	return true;
}

bool BatimentQuadPont::merge() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
    return true;
}

float ct(float x) {
    return  -(1.*cosh(x/1.))+1;
}

float nt(double x, int height) {
    return (ct(x) + -ct(-1.7))/(ct(0)+ -ct(-1.7)) * height;
}

void BatimentQuadPont::triangulation() {
	//triangles.reserve(2);
    float var;
    Quad q = Quad(ne,se,sw,nw);
    Vertex a,b;
    Vertex pa = nw;
    Vertex pb = sw;
    Vertex neh = ne + Vertex(0,0,height+100);
    Vertex seh = se + Vertex(0,0,height+100);
    Vertex swh = sw + Vertex(0,0,height+100);
    Vertex nwh = nw + Vertex(0,0,height+100);
    Vertex l1 = ne - nw;
    Vertex l2 = sw - se;

    float pas = 0.1;
    int steps = (2*1.7/pas);
    float n2 = l2.norm()/(2*1.7/pas);
    n2=n2;
    int middle = steps/2;
    int n;

    std::cout << std::endl << l1.norm() << std::endl;

    addTriangle(new Triangle(lctr+pb,lctr+sw,lctr+swh,0x10,0xFF,0x10));
    addTriangle(new Triangle(lctr+pa,lctr+nw,lctr+nwh,0x10,0xFF,0x10));

    for(var=-1.7,n=0; var <= 1.7; var+=pas,n++) {
        std::cout << var << std::endl;
        //std::cout << var << " \t " << nt(var,height) << std::endl;
        q.offset(W,-n2);
        a = q.corner[3] + Vertex(0,0,nt(var,height));
        b = q.corner[2] + Vertex(0,0,nt(var,height));

        addQuad(lctr+a,lctr+b,lctr+pb,lctr+pa,0xEE,0xEE,0xEE);

        if( n < middle) {
            addTriangle(new Triangle(lctr+pa,lctr+a,lctr+nwh,0xFF,0x10,0xFF));
            addTriangle(new Triangle(lctr+pb,lctr+b,lctr+swh,0xFF,0x10,0xFF));
        }
        else if(n == middle) {
            addTriangle(new Triangle(lctr+pa,lctr+a,lctr+nwh,0x10,0x10,0xFF));
            addTriangle(new Triangle(lctr+pb,lctr+b,lctr+swh,0x10,0x10,0xFF));
            addTriangle(new Triangle(lctr+a,lctr+neh,lctr+nwh,0x10,0x10,0xFF));
            addTriangle(new Triangle(lctr+b,lctr+seh,lctr+swh,0x10,0x10,0xFF));
        }
        else {
            addTriangle(new Triangle(lctr+pa,lctr+a,lctr+neh,0x10,0xFF,0xFF));
            addTriangle(new Triangle(lctr+pb,lctr+b,lctr+seh,0x10,0xFF,0xFF));
        }

        pa = a;
        pb = b;
    }

    addTriangle(new Triangle(lctr+se,lctr+pb,lctr+seh,0x10,0xFF,0x10));
    addTriangle(new Triangle(lctr+ne,lctr+pa,lctr+neh,0x10,0xFF,0x10));
}
