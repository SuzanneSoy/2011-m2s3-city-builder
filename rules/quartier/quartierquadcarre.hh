#ifndef _RULES_QUAD_CROIX_HH_
#define _RULES_QUAD_CROIX_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class QuartierQuadCarre : public QuartierQuad {
    private :
	static const int hrw = 250; // half road width : 2,50m.

    public :
	QuartierQuadCarre(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~QuartierQuadCarre();
	virtual bool split();
	virtual bool merge();
	virtual std::vector<Vertex*> getBoundingBoxPoints() const;
};

#endif
