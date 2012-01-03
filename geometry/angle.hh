namespace Angle {
	const float Pi = 3.141592653589793238462643383279;
	const double dPi = 3.141592653589793238462643383279;
	float r2d(float rad) { return rad / Pi * 180; }
	float d2r(float deg) { return deg / 180 * Pi; }
};
