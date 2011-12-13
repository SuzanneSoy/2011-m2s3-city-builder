#ifndef _QUAD_HH_
#define _QUAD_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class Quad {
    public :
	Vertex corner[4];

    public :
	Quad();
	Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	void offset(Cardinal side, int offset);
	int minLengthNS();
	int minLengthEW();
	int maxLengthNS();
	int maxLengthEW();
	int minLength();
	int maxLength();
	float minAngle();
	float maxAngle();
};


#endif
