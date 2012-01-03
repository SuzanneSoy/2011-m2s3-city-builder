#include "all_includes.hh"

GPUTriangle::GPUTriangle(Vertex left, Vertex top, Vertex right, unsigned char r, unsigned char g, unsigned char b)
	: r(r), g(g), b(b), vnormal(normal(left,top,right)) {
	c[0] = left;
	c[1] = top;
	c[2] = right;
}

Vertex GPUTriangle::normal(Vertex left, Vertex top, Vertex right) {
	Vertex normal = (left - top)*(top - right);
	return normal / normal.norm();
}

void GPUTriangle::display() {
	// glDisable(GL_LIGHTING);
	// glDisable(GL_TEXTURE_2D);
	// glBegin(GL_LINES);
	// glColor3ub(255,255,0);
	// Vertex v = (c[0] + c[1] + c[2]) / 3;
	// glVertex3d(v.x,v.y,v.z);
	// glVertex3d(v.x+vnormal.x*50,v.y+vnormal.y*50,v.z+vnormal.z*50);
	// glEnd( );
	// glEnable(GL_LIGHTING);

	View::setColor(r,g,b);
	glNormal3d(vnormal.x,vnormal.y,vnormal.z);
	// glBegin(GL_TRIANGLES);
	glVertex3d(c[0].x,c[0].y,c[0].z);
	glVertex3d(c[1].x,c[1].y,c[1].z);
	glVertex3d(c[2].x,c[2].y,c[2].z);
	// glEnd();
}
