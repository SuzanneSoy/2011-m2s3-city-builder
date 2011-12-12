#ifndef _RULES_QUAD_ANGLE_HH_
#define _RULES_QUAD_ANGLE_HH_

#include "all_includes.hh"

// QuadAngle est un quadrilatère avec des angles malfichus (< 90-40 ou > 90+40).
class QuartierQuadAngle : public QuartierQuad {
private:
	static const int hrw = 150; // half road width : 2,50m.
public:
	QuartierQuadAngle(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
private:
	void cutAngle();
};

#endif
