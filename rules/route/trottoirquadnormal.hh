#ifndef _RULES_TROTTOIRROUTE_HH_
#define _RULES_TRTTOIRROUTE_HH_

#include "all_includes.hh"

class TrottoirQuadNormal : public Chose {
	private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
	int height;
	Cardinal border;

	public :
	TrottoirQuadNormal(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height, Cardinal border);
	virtual bool subdivide();
	virtual void triangulation();
	virtual std::vector<Vertex*> getBoundingBoxPoints() const;
};

#endif
