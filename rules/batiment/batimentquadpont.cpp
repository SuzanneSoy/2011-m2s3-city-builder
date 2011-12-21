#include "all_includes.hh"

BatimentQuadPont::BatimentQuadPont(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
    c[NE] = ne;
    c[SE] = se;
    c[SW] = sw;
    c[NW] = nw;
    this->height = height;
}

BatimentQuadPont::~BatimentQuadPont() {
    children.clear();
    triangles.clear();
}

void BatimentQuadPont::getBoundingBoxPoints() {
	// TODO !
}

bool BatimentQuadPont::split() {
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
    Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
    Vertex a,b;
    height -= 20;
    Vertex pa = c[NW];
    Vertex pb = c[SW];
    Vertex neh = c[NE] + Vertex(0,0,height+20);
    Vertex seh = c[SE] + Vertex(0,0,height+20);
    Vertex swh = c[SW] + Vertex(0,0,height+20);
    Vertex nwh = c[NW] + Vertex(0,0,height+20);
    Vertex l1 = c[NE] - c[NW];
    Vertex l2 = c[SW] - c[SE];

    float pas = 0.1;
    int steps = (2*1.7/pas);
    float n2 = l2.norm()/(2*1.7/pas);
    n2=n2;
    int middle = steps/2;
    int n;

    addTriangle(new Triangle(pb,c[SW],swh,0xD0,0xD0,0xD0));
    addTriangle(new Triangle(pa,c[NW],nwh,0xD0,0xD0,0xD0));

    for(var=-1.7,n=0; var <= 1.7; var+=pas,n++) {
        q.offset(W,-n2);
        a = q.corner[3] + Vertex(0,0,nt(var,height));
        b = q.corner[2] + Vertex(0,0,nt(var,height));

        addQuad(b,a,pa,pb,0xD0,0xD0,0xD0);

        if( n < middle) {
            addTriangle(new Triangle(a,pa,nwh,0xD0,0xD0,0xD0));
            addTriangle(new Triangle(pb,b,swh,0xD0,0xD0,0xD0));
        }
        else if(n == middle) {
            addTriangle(new Triangle(a,pa,nwh,0xD0,0xD0,0xD0));
            addTriangle(new Triangle(pb,b,swh,0xD0,0xD0,0xD0));
            addTriangle(new Triangle(a,nwh,neh,0xD0,0xD0,0xD0));
            addTriangle(new Triangle(b,seh,swh,0xD0,0xD0,0xD0));
        }
        else {
            addTriangle(new Triangle(a,pa,neh,0xD0,0xD0,0xD0));
            addTriangle(new Triangle(pb,b,seh,0xD0,0xD0,0xD0));
        }

        pa = a;
        pb = b;
    }

    addTriangle(new Triangle(c[SE],pb,seh,0xD0,0xD0,0xD0));
    addTriangle(new Triangle(c[NE],pa,neh,0xD0,0xD0,0xD0));
}
