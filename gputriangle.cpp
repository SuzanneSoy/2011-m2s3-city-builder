#include "all_includes.hh"

GPUTriangle::GPUTriangle(Vertex left, Vertex top, Vertex right, unsigned char _r, unsigned char _g, unsigned char _b)
	: c(left, top, right), r(_r), g(_g), b(_b), vnormal(c.normalizedNormal()) {
}

GPUTriangle::GPUTriangle(Triangle _c, unsigned char _r, unsigned char _g, unsigned char _b)
	: c(_c), r(_r), g(_g), b(_b), vnormal(c.normalizedNormal()) {
}

void GPUTriangle::display() const {
	View::setColor(r,g,b);
	glNormal3d(vnormal.x,vnormal.y,vnormal.z);
	glVertex3d(c[LEFT].x,c[LEFT].y,c[LEFT].z);
	glVertex3d(c[TOP].x,c[TOP].y,c[TOP].z);
	glVertex3d(c[RIGHT].x,c[RIGHT].y,c[RIGHT].z);
}

void GPUTriangle::displayNormal() const {
	glColor3ub(255,255,0);
	// Vertex v = (c[0] + c[1] + c[2]) / 3;
	// glVertex3d(v.x,v.y,v.z);
	// glVertex3d(v.x+vnormal.x*50,v.y+vnormal.y*50,v.z+vnormal.z*50);

	glColor3ub(255,0,0);
	Vertex v = (c[LEFT]*8 + c[TOP] + c[RIGHT]) / 10;//(c[0] + c[1] + c[2]) / 3;
	glVertex3d(v.x,v.y,v.z);
	glVertex3d(v.x+vnormal.x*50,v.y+vnormal.y*50,v.z+vnormal.z*50);

	glColor3ub(0,255,0);
	v = (c[LEFT] + c[TOP]*8 + c[RIGHT]) / 10;
	glVertex3d(v.x,v.y,v.z);
	glVertex3d(v.x+vnormal.x*50,v.y+vnormal.y*50,v.z+vnormal.z*50);

	glColor3ub(0,0,255);
	v = (c[LEFT] + c[TOP] + c[RIGHT]*8) / 10;
	glVertex3d(v.x,v.y,v.z);
	glVertex3d(v.x+vnormal.x*50,v.y+vnormal.y*50,v.z+vnormal.z*50);
}
