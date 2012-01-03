#ifndef _GPU_TRIANGLE_HH_
#define _GPU_TRIANGLE_HH_

#include "all_includes.hh"

class GPUTriangle {
	public :
	Vertex c[3];
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Vertex vnormal;

public :
	GPUTriangle(Vertex left, Vertex top, Vertex right, unsigned char r, unsigned char g, unsigned char b);
	void display();

private :
	Vertex normal(Vertex left, Vertex top, Vertex right);
};

#endif
