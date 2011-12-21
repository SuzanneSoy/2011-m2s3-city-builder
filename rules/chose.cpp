#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {
	std::cout << "NEW CHOSE " << (int)(this) << std::endl;
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

unsigned int Chose::initialSeed = 779313522;//random_seed();
