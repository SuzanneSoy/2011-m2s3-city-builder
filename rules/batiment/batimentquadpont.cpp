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
    return (ct(x) + -ct(-M_PI/2.))/(ct(0)+ -ct(-M_PI/2.)) * height;
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
    float pas = (M_PI / 60);
    float n1 = l1.norm()/pas;
    float n2 = l2.norm()/pas;
    n1=n1;

    std::cout << std::endl << std::endl;

    for(var=-M_PI/2; var <= M_PI/2; var+=pas) {
        if(var == 0) continue;
        std::cout << var << " \t " << nt(var,height) << std::endl;
        q.offset(W,-n2);
        a = q.corner[3] + Vertex(0,0,nt(var,height));
        b = q.corner[2] + Vertex(0,0,nt(var,height));

        addQuad(a,b,pb,pa,0xFF,0xFF,0xFF);
        if( var < 0) {
            addTriangle(new Triangle(pa,a,nwh,0xFF,0xFF,0xFF));
            addTriangle(new Triangle(pb,b,swh,0xFF,0xFF,0xFF));
        }
        else {
            addTriangle(new Triangle(pa,a,neh,0xFF,0xFF,0xFF));
            addTriangle(new Triangle(pb,b,seh,0xFF,0xFF,0xFF));
        }

        pa = a;
        pb = b;
    }
}
