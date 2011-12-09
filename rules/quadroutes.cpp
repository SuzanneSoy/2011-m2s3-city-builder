#include "all_includes.hh"

const float QuadRoutes::cosMin = std::cos((90+maxAngleDelta)/180.f*3.14159);
const float QuadRoutes::cosMax = std::cos((90-maxAngleDelta)/180.f*3.14159);

QuadRoutes::QuadRoutes(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne, se, sw, nw);
	triangulation();
}

int QuadRoutes::width() { return std::abs(this->ne.x - this->sw.x); }

int QuadRoutes::height() { return std::abs(this->ne.y - this->sw.y); }

bool QuadRoutes::subdivide() {
	children.reserve(9);

	// TODO : faire ces calculs sur des Vertex2d.
	
	int slen = (se-sw).norm();
	int nlen = (ne-nw).norm();
	int minsnlen = std::min(slen,nlen);
	// constraint: min(slen, nlen) - maxdelta*2 ≥ minchildsize
	// constraint: maxdelta ≤ min(slen,nlen)/4
	int xmaxdelta = std::min(minsnlen/4, (minsnlen-minchildsize)/2);
	float sxpos = slen/2 + hashInRange(seed, 0, -xmaxdelta, xmaxdelta);
	float nxpos = nlen/2 + hashInRange(seed, 0, -xmaxdelta, xmaxdelta);
	Vertex s = (sw * sxpos / slen) + (se * (slen - sxpos) / slen);
	Vertex n = (nw * nxpos / nlen) + (ne * (nlen - nxpos) / nlen);

	int wlen = (nw-sw).norm();
	int elen = (ne-se).norm();
	int minwelen = std::min(wlen,elen);
	// constraint: min(wlen, elen) - maxdelta*2 ≥ minchildsize
	// constraint: maxdelta ≤ min(wlen,elen)/4
	int ymaxdelta = std::min(minwelen/4, (minwelen-minchildsize)/2);
	float wypos = wlen/2 + hashInRange(seed, 0, -ymaxdelta, ymaxdelta);
	float eypos = elen/2 + hashInRange(seed, 0, -ymaxdelta, ymaxdelta);
	Vertex w = (nw * wypos / wlen) + (sw * (wlen - wypos) / wlen);
	Vertex e = (ne * eypos / elen) + (se * (elen - eypos) / elen);
	
	Vertex split = intersection(s,n,w,e);

	std::cout << "n-split-e=" << cosAngle(n,split,e) << " minmax=" << cosMax << std::endl;

	// Créer 4 quad (qne, qse, qsw, qnw), puis :
	Quad q[4] = {
		Quad(ne, e, split, n),
		Quad(se, s, split, e),
		Quad(sw, w, split, s),
		Quad(nw, n, split, w),
	};
	for (int c = NE; c <= NW; ++c) {
		q[c].offset(W,-hrw); q[c].offset(S,-hrw);
	}
	
	addChild(new Carrefour(q[NE].sw, q[SE].sw, q[SW].sw, q[NW].sw));
	addChild(new Route(q[NW].se, q[NE].nw, q[NE].sw, q[NW].sw));
	addChild(new Route(q[NE].se, q[SE].nw, q[SE].sw, q[NE].sw));
	addChild(new Route(q[SE].se, q[SW].nw, q[SW].sw, q[SE].sw));
	addChild(new Route(q[SW].se, q[NW].nw, q[NW].sw, q[SW].sw));
	addChild(sub(q[NE].ne, q[NE].se, q[NE].sw, q[NE].nw));
	addChild(sub(q[SE].ne, q[SE].se, q[SE].sw, q[SE].nw));
	addChild(sub(q[SW].ne, q[SW].se, q[SW].sw, q[SW].nw));
	addChild(sub(q[NW].ne, q[NW].se, q[NW].sw, q[NW].nw));

	return true;
}

void QuadRoutes::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(ne, nw, sw, 0xc0, 0xc0, 0xc0));
	addTriangle(new Triangle(sw, se, ne, 0xc0, 0xc0, 0xc0));
}

Chose* QuadRoutes::sub(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	if ((ne - se).norm() < minQuadSize ||
		(se - sw).norm() < minQuadSize ||
		(sw - nw).norm() < minQuadSize ||
		(nw - ne).norm() < minQuadSize) {
		return new Batiment(ne, se, sw, nw);
	} else {
		return new QuadRoutes(ne, se, sw, nw);
	}
}

std::ostream& operator<<(std::ostream& os, const QuadRoutes* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const QuadRoutes& r) {
	return os << "QuadRoutes " << r.ne << "-" << r.sw;
}
