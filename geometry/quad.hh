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
	Quad insetOpp(Cardinal side, float offset) const;
	float length(Cardinal side) const;
	float minLengthNS() const;
	float minLengthEW() const;
	float maxLengthNS() const;
	float maxLengthEW() const;
	float minLength() const;
	float maxLength() const;
	Cardinal minLengthSide() const;
	Cardinal maxLengthSide() const;
	Coin concaveCorner();
	bool isConcave();
	float angle(Coin corner) const;
	float minAngle() const;
	float maxAngle() const;
	Coin minAngleCorner() const;
	Coin maxAngleCorner() const;
	Vertex randomPoint(int seed, int n) const;
	float surface() const;
	//void cutCornerCorner(Coin from) const;
	Quad makeParallelogram() const;
	Quad offsetNormal(float offset) const;
	Vertex normal() const;
	Vertex normalizedNormal() const;
	Vertex moyenne() const;
};


#endif
