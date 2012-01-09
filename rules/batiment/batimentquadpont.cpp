#include "all_includes.hh"

BatimentQuadPont::BatimentQuadPont(Quad c, float height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadPont::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

float ct(float x) {
    return (float)(1 - cosh(x / 1.f));
}

float nt(float x, float height) {
    return (ct(x) + -ct(-1.7f))/(ct(0)+ -ct(-1.7f)) * height;
}

void BatimentQuadPont::triangulation() {
	//triangles.reserve(2);
    float var;
    Quad q = c;
    Vertex a,b;
    height -= 20;
    Vertex pa = c[NW];
    Vertex pb = c[SW];
    Quad ch = c + Vertex(0,0,height+20);
    Vertex l1 = c[NE] - c[NW];
    Vertex l2 = c[SW] - c[SE];

    float pas = 0.1f;
    int steps = (int)(Angle::Pi / pas);
    float n2 = l2.norm()/(Angle::Pi / pas);
    n2=n2;
    int middle = steps/2;
    int n;

    addGPUTriangle(c[SW],pb,ch[SW],0xD0,0xD0,0xD0);
    addGPUTriangle(pa,c[NW],ch[NW],0xD0,0xD0,0xD0);

    for(var=-1.7f, n=0; var <= 1.7f; var+=pas, n++) {
        q = q.inset(W,n2);
        a = q[NW] + Vertex(0,0,nt(var,height));
        b = q[SW] + Vertex(0,0,nt(var,height));

        addGPUQuad(a,b,pb,pa,0xD0,0xD0,0xD0);

        if( n < middle) {
            addGPUTriangle(pa,a,ch[NW],0xD0,0xD0,0xD0);
            addGPUTriangle(b,pb,ch[SW],0xD0,0xD0,0xD0);
        }
        else if(n == middle) {
            addGPUTriangle(pa,a,ch[NW],0xD0,0xD0,0xD0);
            addGPUTriangle(b,pb,ch[SW],0xD0,0xD0,0xD0);
            addGPUTriangle(a,ch[NE],ch[NW],0xD0,0xD0,0xD0);
            addGPUTriangle(b,ch[SW],ch[SE],0xD0,0xD0,0xD0);
        }
        else {
            addGPUTriangle(pa,a,ch[NE],0xD0,0xD0,0xD0);
            addGPUTriangle(b,pb,ch[SE],0xD0,0xD0,0xD0);
        }

        pa = a;
        pb = b;
    }

    addGPUTriangle(c[SE],pb,ch[SE],0xD0,0xD0,0xD0);
    addGPUTriangle(c[NE],pa,ch[NE],0xD0,0xD0,0xD0);
}
