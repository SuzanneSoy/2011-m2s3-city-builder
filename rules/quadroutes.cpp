#include "all_includes.hh"

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
	Vertex s = (sw * sxpos / slen) + (se * (slen - nxpos) / slen);
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

	// TODO : Pour offset les points des extrémités de la route w--split :
	// Vertex offset = vecteur perpendiculaire w--split, de longueur hrw.
	// Projeter `offset` sur split--n, et ajouter le résultat à split.
	// Projeter `offset` sur w--nw, et ajouter le résultat à w.

	// Projeter u sur v : (u scalaire v) / v.norm().
	// scalaire(u,v) = u.norm() * v.norm() * cos(angle(u,v))
	// Donc projeter u sur v : u.norm() * cos(angle(u,v))
	// TODO : comment calculer l'angle(u,v) ?
	
	addChild(new Carrefour(split + Vertex(hrw,hrw,0), split + Vertex(hrw,-hrw,0), split + Vertex(-hrw,-hrw,0), split + Vertex(-hrw,hrw,0)));
	// routes au NESW du carrefour
	// TODO : la plupart des zéros en z sont faux…
	Vertex roadEndN(split.x, this->ne.y, 0);
	Vertex roadEndE(this->ne.x, split.y, 0);
	Vertex roadEndS(split.x, this->sw.y, 0);
	Vertex roadEndW(this->sw.x, split.y, 0);
	// TODO : addChild(…);
	Route* rn = new Route(roadEndN + Vertex(+hrw,0,0), split + Vertex(+hrw,+hrw,0), split + Vertex(-hrw,+hrw,0), roadEndN + Vertex(-hrw,0,0)); // N
	Route* re = new Route(roadEndE + Vertex(0,+hrw,0), roadEndE + Vertex(0,-hrw,0), split + Vertex(+hrw,-hrw,0), split + Vertex(+hrw,+hrw,0)); // E
	Route* rs = new Route(split + Vertex(+hrw,-hrw,0), roadEndS + Vertex(+hrw,0,0), roadEndS + Vertex(-hrw,0,0), split + Vertex(-hrw,-hrw,0)); // S
	Route* rw = new Route(split + Vertex(-hrw,+hrw,0), split + Vertex(-hrw,-hrw,0), roadEndW + Vertex(0,-hrw,0), roadEndW + Vertex(0,+hrw,0)); // W
	addChild(rn);
	addChild(re);
	addChild(rs);
	addChild(rw);
	// Sous-quartiers
	addChild(sub(ne, re->nw)); // sous-quartier NE
	addChild(sub(re->se, rs->se)); // sous-quartier SE
	addChild(sub(rs->nw, sw)); // sous-quartier SW
	addChild(sub(rn->nw, rw->nw)); // sous-quartier NW
	return true;
}

void QuadRoutes::triangulation() {
	triangles.reserve(2);
	Vertex nw(this->sw.x, this->ne.y, 0);
	Vertex se(this->ne.x, this->sw.y, 0);
	addTriangle(new Triangle(this->ne, nw, this->sw, 0xc0, 0xc0, 0xc0));
	addTriangle(new Triangle(this->sw, se, this->ne, 0xc0, 0xc0, 0xc0));
}

Chose* QuadRoutes::sub(Vertex ne, Vertex sw) {
	Segment rect = Segment(ne,sw);
	if (rect.width() < minQuadSize || rect.height() < minQuadSize) {
		return new Batiment(ne, Vertex(ne.x, sw.y, 0), sw, Vertex(sw.x, ne.y, 0));
	} else {
		return new QuadRoutes(ne, Vertex(ne.x, sw.y, 0), sw, Vertex(sw.x, ne.y, 0));
	}
}

std::ostream& operator<<(std::ostream& os, const QuadRoutes* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const QuadRoutes& r) {
	return os << "QuadRoutes " << r.ne << "-" << r.sw;
}
