#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

void Chose::addTriangle(Triangle* t) {
	triangles.push_back(t);
}

bool Chose::merge() {
    children.clear();
	// triangles.clear();
    return true;
}

void Chose::addQuad(Vertex u, Vertex v, Vertex w, Vertex x, char r, char g, char b) {
    this->addTriangle(new Triangle(u,x,w,r,g,b));
    this->addTriangle(new Triangle(w,v,u,r,g,b));
}

void Chose::addOcto(Vertex a, Vertex b, Vertex c, Vertex d,
                    Vertex e, Vertex f, Vertex g, Vertex h, char red, char green, char blue) {
    this->addQuad(a,b,c,d,red,green,blue);
    this->addQuad(e,f,g,h,red,green,blue);
    this->addQuad(b,a,e,f,red,green,blue);
    this->addQuad(c,b,f,g,red,green,blue);
    this->addQuad(d,c,g,h,red,green,blue);
    this->addQuad(a,d,h,e,red,green,blue);
}

void Chose::display() {
	if (children.size() > 0) {
		std::vector<Chose*>::iterator it;
		for (it = children.begin(); it != children.end(); ++it) {
			(*it)->display();
		}
	} else {
		std::vector<Triangle*>::iterator it;
		for (it = triangles.begin(); it != triangles.end(); ++it) {
			(*it)->display();
		}
	}
}

void Chose::addBBPoint(Vertex v) {
	if (lod.firstBBPoint) {
		lod.firstBBPoint = false;
		lod.aabb[0] = v.x;
		lod.aabb[1] = v.x;
		lod.aabb[2] = v.y;
		lod.aabb[3] = v.y;
		lod.aabb[4] = v.z;
		lod.aabb[5] = v.z;
	} else {
		lod.aabb[0] = std::min(lod.aabb[0], v.x);
		lod.aabb[1] = std::max(lod.aabb[1], v.x);
		lod.aabb[2] = std::min(lod.aabb[2], v.y);
		lod.aabb[3] = std::max(lod.aabb[3], v.y);
		lod.aabb[4] = std::min(lod.aabb[4], v.z);
		lod.aabb[5] = std::max(lod.aabb[5], v.z);
	}
}

void Chose::updateAABB() {
	lod.firstBBPoint = true;
	getBoundingBoxPoints();
	for (int i = 0; i < 6; i++) {
		// TODO
		lod.splitCube[i] = lod.aabb[i];
		lod.mergeCube[i] = lod.aabb[i];
	}
}

void Chose::displayAABB() {
	updateAABB();
	if (children.size() > 0) {
		std::vector<Chose*>::iterator it;
		for (it = children.begin(); it != children.end(); ++it) {
			(*it)->displayAABB();
		}
	} else {
		// Affiche la AABB.
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[4]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[4]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[4]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[4]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[0],lod.aabb[3],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[5]);
		glVertex3d(lod.aabb[1],lod.aabb[2],lod.aabb[4]);
		glVertex3d(lod.aabb[1],lod.aabb[3],lod.aabb[4]);
	}
}

unsigned int Chose::initialSeed = 779313522;//random_seed();
