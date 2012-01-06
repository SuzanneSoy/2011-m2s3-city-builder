#ifndef _GEOMETRY_TRIANGLE_HH_
#define _GEOMETRY_TRIANGLE_HH_

#include "all_includes.hh"

class Triangle {
	private :
	Vertex c[3];

	public :
	Triangle();
	Triangle(Vertex left, Vertex top, Vertex right);
	inline Vertex& operator[] (SommetTriangle x) {
		return c[x];
	}
	inline const Vertex& operator[] (SommetTriangle x) const {
		return c[x];
	}
	inline Triangle operator>> (int rot) const {
		return Triangle(c[LEFT - rot], c[TOP - rot], c[RIGHT - rot]);
	}
	inline Triangle operator<< (int rot) const {
		return Triangle(c[LEFT + rot], c[TOP + rot], c[RIGHT + rot]);
	}
	friend Triangle operator+(const Triangle& t, const Vertex& v);
	float cosAngle() const; // cosinus de l'angle en c[1].
	float angle() const; // angle en c[1], en degrés. TODO : le calcul ne donne que des angles entre 0 et 180 !
	float minAngle() const; // angle minimum du triangle (en c[0], c[1] ou c[2]).
	float minLength() const;
	float maxLength() const;
	Triangle inset(CoteTriangle side, float offset) const;
	void display();
};

#endif
