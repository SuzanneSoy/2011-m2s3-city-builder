#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

void Chose::addTriangle(GPUTriangle* t) {
	triangles.push_back(t);
}

bool Chose::merge() {
    children.clear();
	// triangles.clear();
    return true;
}

void Chose::addQuad(Vertex u, Vertex v, Vertex w, Vertex x, char r, char g, char b) {
    this->addTriangle(new GPUTriangle(u,x,w,r,g,b));
    this->addTriangle(new GPUTriangle(w,v,u,r,g,b));
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
		std::vector<GPUTriangle*>::iterator it;
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
	float dx = lod.aabb[1] - lod.aabb[0];
	float dy = lod.aabb[3] - lod.aabb[2];
	float dz = lod.aabb[5] - lod.aabb[4];
	float volume = dx*dy*dz;
	float pseudoLength = std::max(1.f, std::pow(volume, 1.f/3.f) / 1000.f);
	float splitFactor = 24 * pseudoLength;
	float mergeFactor = 25 * pseudoLength;
	for (int i = 0; i < 3; i++) {
		float center = (lod.aabb[2*i] + lod.aabb[2*i+1]) / 2;
		lod.splitBox[2*i] = (lod.aabb[2*i] - center) * splitFactor + center;
		lod.splitBox[2*i+1] = (lod.aabb[2*i+1] - center) * splitFactor + center;
		lod.mergeBox[2*i] = (lod.aabb[2*i] - center) * mergeFactor + center;
		lod.mergeBox[2*i+1] = (lod.aabb[2*i+1] - center) * mergeFactor + center;
	}
}

// DEBUG
void Chose::drawAABB() {
	addOcto(
		Vertex(lod.splitBox[0], lod.splitBox[2], lod.splitBox[4]),
		Vertex(lod.splitBox[1], lod.splitBox[2], lod.splitBox[4]),
		Vertex(lod.splitBox[1], lod.splitBox[3], lod.splitBox[4]),
		Vertex(lod.splitBox[0], lod.splitBox[3], lod.splitBox[4]),
		Vertex(lod.splitBox[0], lod.splitBox[2], lod.splitBox[5]),
		Vertex(lod.splitBox[1], lod.splitBox[2], lod.splitBox[5]),
		Vertex(lod.splitBox[1], lod.splitBox[3], lod.splitBox[5]),
		Vertex(lod.splitBox[0], lod.splitBox[3], lod.splitBox[5]),
		hashInRange(seed, 42, 0, 256),
		hashInRange(seed, 43, 0, 256),
		hashInRange(seed, 44, 0, 256)
	);
}

unsigned int Chose::initialSeed = random_seed();
