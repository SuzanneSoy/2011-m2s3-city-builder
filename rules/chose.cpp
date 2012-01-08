#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {
}

// TODO : Le destructeur est-il vraiment nécessaire ?
// TODO : Vu que children et triangles contiennent des pointeurs, le .clear() risque de ne pas les désallouer !
Chose::~Chose() {
    children.clear();
    triangles.clear();
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

bool Chose::merge() {
    children.clear();
	// triangles.clear();
    return true;
}

void Chose::addGPUTriangle(Vertex left, Vertex top, Vertex right, char r, char g, char b) {
	triangles.push_back(new GPUTriangle(left, top, right, r, g, b));
}

void Chose::addGPUTriangle(Triangle t, char r, char g, char b) {
	addGPUTriangle(t[LEFT], t[TOP], t[RIGHT], r, g, b);
}

void Chose::addGPUQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, char r, char g, char b) {
    this->addGPUTriangle(nw,ne,se,r,g,b);
    this->addGPUTriangle(se,sw,nw,r,g,b);
}

void Chose::addGPUQuad(Quad q, char r, char g, char b) {
	addGPUQuad(q[NE], q[SE], q[SW], q[NW], r, g, b);
}

void Chose::addGPUOcto(Vertex ne, Vertex se, Vertex sw, Vertex nw,
                    Vertex neh, Vertex seh, Vertex swh, Vertex nwh, char r, char g, char b) {
	addGPUOcto(Quad(ne,se,sw,nw), Quad(neh,seh,swh,nwh), r, g, b);
}

void Chose::addGPUOcto(Quad q, Quad qh, char r, char g, char b) {
    this->addGPUQuad(q[NE], q[SE], q[SW], q[NW], r, g, b);
    this->addGPUQuad(qh[NE], qh[SE], qh[SW], qh[NW], r, g, b);
    for (int i = 0; i < 4; i++)
    	this->addGPUQuad(q[NE+i], q[SE+i], qh[SE+i], qh[NE+i], r, g, b);
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

void Chose::displayNormals() {
	if (children.size() > 0) {
		std::vector<Chose*>::iterator it;
		for (it = children.begin(); it != children.end(); ++it) {
			(*it)->displayNormals();
		}
	} else {
		std::vector<GPUTriangle*>::iterator it;
		for (it = triangles.begin(); it != triangles.end(); ++it) {
			(*it)->displayNormal();
		}
	}
}

void Chose::addBBPoint(const Vertex v) {
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

void Chose::addBBPoints(const Triangle t) {
	addBBPoint(t[LEFT]);
	addBBPoint(t[TOP]);
	addBBPoint(t[RIGHT]);
}

void Chose::addBBPoints(const Quad q) {
	addBBPoint(q[NE]);
	addBBPoint(q[SE]);
	addBBPoint(q[SW]);
	addBBPoint(q[NW]);
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
	addGPUOcto(
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
