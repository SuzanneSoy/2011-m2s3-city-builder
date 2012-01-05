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
	void offset(Cardinal side, int offset);
	void offsetNESW(int offsetN, int offsetE, int offsetS, int offsetW);
	float minLengthNS();
	float minLengthEW();
	float maxLengthNS();
	float maxLengthEW();
	float minLength();
	float maxLength();
	float minAngle();
	float maxAngle();
	Quad makeParallelogram();
};


#endif
