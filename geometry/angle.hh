#ifndef _GEOMETRY_ANGLE_HH_
#define _GEOMETRY_ANGLE_HH_

#include "all_includes.hh"

namespace Angle {
	const double dPi = 3.141592653589793238462643383279;
	const float Pi = (float)(dPi);
	float r2d(float rad);
	float d2r(float deg);
}

class Angle3D {
public:
	Vertex h;
	Vertex l;
	Vertex u;
	Angle3D();
	Angle3D(Vertex _h, Vertex _l, Vertex _u);
	Angle3D rotateH(float angle) const;
	Angle3D rotateL(float angle) const;
	Angle3D rotateU(float angle) const;
};

#endif
