#include "all_includes.hh"

BatimentQuadPont::BatimentQuadPont(Quad c, int height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadPont::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
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
    Quad ch = c + Vertex(0,0,height+20);
    Vertex l1 = c[NE] - c[NW];
    Vertex l2 = c[SW] - c[SE];

    float pas = 0.1;
    int steps = (3.14/pas);
    float n2 = l2.norm()/(3.14/pas);
    n2=n2;
    int middle = steps/2;
    int n;

    addGPUTriangle(new GPUTriangle(c[SW],pb,ch[SW],0xD0,0xD0,0xD0));
    addGPUTriangle(new GPUTriangle(pa,c[NW],ch[NW],0xD0,0xD0,0xD0));

    for(var=-1.7,n=0; var <= 1.7; var+=pas,n++) {
        q.offset(W,-n2);
        a = q.c[3] + Vertex(0,0,nt(var,height));
        b = q.c[2] + Vertex(0,0,nt(var,height));

        addGPUQuad(a,b,pb,pa,0xD0,0xD0,0xD0);

        if( n < middle) {
            addGPUTriangle(new GPUTriangle(pa,a,ch[NW],0xD0,0xD0,0xD0));
            addGPUTriangle(new GPUTriangle(b,pb,ch[SW],0xD0,0xD0,0xD0));
        }
        else if(n == middle) {
            addGPUTriangle(new GPUTriangle(pa,a,ch[NW],0xD0,0xD0,0xD0));
            addGPUTriangle(new GPUTriangle(b,pb,ch[SW],0xD0,0xD0,0xD0));
            addGPUTriangle(new GPUTriangle(a,ch[NE],ch[NW],0xD0,0xD0,0xD0));
            addGPUTriangle(new GPUTriangle(b,ch[SW],ch[SE],0xD0,0xD0,0xD0));
        }
        else {
            addGPUTriangle(new GPUTriangle(pa,a,ch[NE],0xD0,0xD0,0xD0));
            addGPUTriangle(new GPUTriangle(b,pb,ch[SE],0xD0,0xD0,0xD0));
        }

        pa = a;
        pb = b;
    }

    addGPUTriangle(new GPUTriangle(c[SE],pb,ch[SE],0xD0,0xD0,0xD0));
    addGPUTriangle(new GPUTriangle(c[NE],pa,ch[NE],0xD0,0xD0,0xD0));
}
