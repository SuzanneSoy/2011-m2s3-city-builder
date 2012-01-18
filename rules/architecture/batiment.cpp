#include "all_includes.hh"

BatimentQuad_::BatimentQuad_(Quad _c, bool _isSub, bool _we, bool _ws, bool _ww, bool _wn)
        : Chose(), c(_c), isSub(_isSub), we(_we), ws(_ws), ww(_ww), wn(_wn) {
	addEntropy(c);
}

bool BatimentQuad_::split() {
	int minSurface = 100 * 100 * 10;
	Quad q = c;
	//Quad q = c << c.maxLengthSide();
	if(c.maxLengthNS() < c.maxLengthEW()) {
        q = c >> 1;
        bool t = we;
        we = ws; ws = ww; ww = wn; wn = t;
	}

    //std::cout << "w : " << we << " " << ws << " " << ww << " " << wn << std::endl;
	if((we || ws || ww || wn) && q.surface() > 2 * minSurface) {
		Vertex n = Segment(q[NW], q[NE]).randomPos(seed, 0, 1.f/3.f, 1.f/2.f);
		Vertex s = Segment(q[SE], q[SW]).randomPos(seed, 1, 1.f/3.f, 1.f/2.f);

        addChild(new BatimentQuad_(Quad(q[NE], q[SE], s, n), true,we&&true,ws&&true,false,wn&&true));
        addChild(new BatimentQuad_(Quad(n, s,q[SW],q[NW]), true,false,ws&&true,ww&&true,wn&&true));
	} else {
		Quad ch = c.offsetNormal(Dimensions::hauteurEtage);
		ch = ch.insetNESW(30);
		if(we || ws || ww || wn)
            addChild(new ToitQuad(ch, Dimensions::hauteurToit));
        else
            addChild(new BatimentQuadJardin(ch));
	}

	return true;
}

void BatimentQuad_::triangulation() {
	Quad ch = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUQuad(ch, Couleurs::toit);
	for (int i = 0; i < 4; i++)
		addGPUQuad(Quad(c[NE+i], c[SE+i], ch[SE+i], ch[NE+i]), Couleurs::mur);
}

void BatimentQuad_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}

BatimentTri_::BatimentTri_(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool BatimentTri_::split() {
	return false;
}

void BatimentTri_::triangulation() {
	Triangle th = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUTriangle(th, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(c[LEFT+i], c[TOP+i], th[TOP+i], th[LEFT+i]), Couleurs::mur);
}

void BatimentTri_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}
