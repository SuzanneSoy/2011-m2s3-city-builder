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

    int steps = (2*1.7/0.1);
    float pas = 0.1;
    float n1 = l1.norm()/(2*1.7/0.1);
    float n2 = l2.norm()/(2*1.7/0.1);
    n1=n1;
    n2=n2;
    int middle = steps/2;
    int n;

    std::cout << std::endl << l1.norm() << std::endl;

    addTriangle(new Triangle(pb,sw,swh,0x10,0xFF,0x10));
    addTriangle(new Triangle(pa,nw,nwh,0x10,0xFF,0x10));

    for(var=-1.7,n=0; var <= 1.7; var+=pas,n++) {
        std::cout << var << std::endl;
        //std::cout << var << " \t " << nt(var,height) << std::endl;
        q.offset(W,-n2);
        a = q.corner[3] + Vertex(0,0,nt(var,height));
        b = q.corner[2] + Vertex(0,0,nt(var,height));

        addQuad(a,b,pb,pa,0xEE,0xEE,0xEE);
        if( n < middle) {
            addTriangle(new Triangle(pa,a,nwh,0xFF,0x10,0xFF));
            addTriangle(new Triangle(pb,b,swh,0xFF,0x10,0xFF));
        }
        else if(n == middle) {
            addTriangle(new Triangle(pa,a,nwh,0x10,0x10,0xFF));
            addTriangle(new Triangle(pb,b,swh,0x10,0x10,0xFF));
            addTriangle(new Triangle(a,neh,nwh,0x10,0x10,0xFF));
            addTriangle(new Triangle(b,seh,swh,0x10,0x10,0xFF));
        }
        else {
            addTriangle(new Triangle(pa,a,neh,0x10,0xFF,0xFF));
            addTriangle(new Triangle(pb,b,seh,0x10,0xFF,0xFF));
        }

        pa = a;
        pb = b;
    }

    addTriangle(new Triangle(se,pb,seh,0x10,0xFF,0x10));
    addTriangle(new Triangle(ne,pa,neh,0x10,0xFF,0x10));
}
