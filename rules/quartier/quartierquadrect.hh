#ifndef _RULES_QUAD_RECT_HH_
#define _RULES_QUAD_RECT_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class QuartierQuadRect : public QuartierQuad {
    private :
	static const int hrw = 250; // half road width : 2,50m.

    public :
	QuartierQuadRect(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~QuartierQuadRect();
	virtual bool split();
};

#endif
