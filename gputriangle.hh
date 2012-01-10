#ifndef _GPUTRIANGLE_HH_
#define _GPUTRIANGLE_HH_

#include "all_includes.hh"

class GPUTriangle {
	public :
	Triangle c;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Vertex vnormal;

public :
	GPUTriangle(Vertex left, Vertex top, Vertex right, unsigned char r, unsigned char g, unsigned char b);
	GPUTriangle(Triangle c, unsigned char r, unsigned char g, unsigned char b);
	void display() const;
	void displayNormal() const;
};

#endif
