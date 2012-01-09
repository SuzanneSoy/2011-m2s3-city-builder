#ifndef _GEOMETRY_ANGLE_HH_
#define _GEOMETRY_ANGLE_HH_

namespace Angle {
	const double dPi = 3.141592653589793238462643383279;
	const float Pi = (float)(dPi);
	float r2d(float rad) { return rad / Pi * 180; }
	float d2r(float deg) { return deg / 180 * Pi; }
}

#endif
