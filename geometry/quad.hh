#ifndef _GEOMETRY_QUAD_HH_
#define _GEOMETRY_QUAD_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class Quad {
    private:
	Vertex c[4];

    public :
	Quad();
	Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	inline Vertex& operator[] (Coin x) {
		return c[x];
	}
	inline const Vertex& operator[] (Coin x) const {
		return c[x];
	}
	inline Quad operator>> (int rot) const {
			return Quad(c[NE - rot], c[SE - rot], c[SW - rot], c[NW - rot]);
	}
	inline Quad operator<< (int rot) const {
			return Quad(c[NE + rot], c[SE + rot], c[SW + rot], c[NW + rot]);
	}
	friend Quad operator+(const Quad& t, const Vertex& v);
	Quad inset(Cardinal side, float offset) const;
	Quad insetNESW(float offsetN, float offsetE, float offsetS, float offsetW) const;
	Quad insetNESW(float offset) const;
	float minLengthNS();
	float minLengthEW();
	float maxLengthNS();
	float maxLengthEW();
	float minLength();
	float maxLength();
	float minAngle();
	float maxAngle();
	void cutCornerCorner(Coin from) const;
	Quad makeParallelogram();
};


#endif
