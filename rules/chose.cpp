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

void Chose::addGPUTriangle(Vertex left, Vertex top, Vertex right, unsigned char r, unsigned char g, unsigned char b) {
	triangles.push_back(new GPUTriangle(left, top, right, r, g, b));
}

void Chose::addGPUTriangle(Triangle t, unsigned char r, unsigned char g, unsigned char b) {
	addGPUTriangle(t[LEFT], t[TOP], t[RIGHT], r, g, b);
}

void Chose::addGPUQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, unsigned char r, unsigned char g, unsigned char b) {
    this->addGPUTriangle(nw,ne,se,r,g,b);
    this->addGPUTriangle(se,sw,nw,r,g,b);
}

void Chose::addGPUQuad(Quad q, unsigned char r, unsigned char g, unsigned char b) {
	addGPUQuad(q[NE], q[SE], q[SW], q[NW], r, g, b);
}

void Chose::addGPUOcto(Vertex ne, Vertex se, Vertex sw, Vertex nw,
                    Vertex neh, Vertex seh, Vertex swh, Vertex nwh, unsigned char r, unsigned char g, unsigned char b) {
	addGPUOcto(Quad(ne,se,sw,nw), Quad(neh,seh,swh,nwh), r, g, b);
}

void Chose::addGPUOcto(Quad q, Quad qh, unsigned char r, unsigned char g, unsigned char b) {
    this->addGPUQuad(q[SE], q[NE], q[NW], q[SW], r, g, b);
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

void Chose::addBBPoints(const Triangle t, float height) {
	addBBPoints(t);
	addBBPoints(t.offsetNormal(height));
}

void Chose::addBBPoints(const Quad q) {
	addBBPoint(q[NE]);
	addBBPoint(q[SE]);
	addBBPoint(q[SW]);
	addBBPoint(q[NW]);
}

void Chose::addBBPoints(const Quad q, float height) {
	addBBPoints(q);
	addBBPoints(q.offsetNormal(height));
}

void Chose::updateAABB() {
	lod.firstBBPoint = true;
	getBoundingBoxPoints();
	float dx = lod.aabb[1] - lod.aabb[0];
	float dy = lod.aabb[3] - lod.aabb[2];
	float dz = lod.aabb[5] - lod.aabb[4];
	// TODO pour la pseudoLength sur l'axe x, utiliser y*z, pseudolength_y = x*z, pseudolength_z = x*y.
	float pseudoLength = std::sqrt(dx*dy + dy*dz + dx*dz);
	float splitIncrement = 5 * pseudoLength;
	float mergeIncrement = 6 * pseudoLength;
	for (int i = 0; i < 3; i++) {
		lod.splitBox[2*i] = lod.aabb[2*i] - splitIncrement;
		lod.splitBox[2*i+1] = lod.aabb[2*i+1] + splitIncrement;
		lod.mergeBox[2*i] = lod.aabb[2*i] - mergeIncrement;
		lod.mergeBox[2*i+1] = lod.aabb[2*i+1] + splitIncrement;
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
		hash2(seed, 42) & 255,
		hash2(seed, 43) & 255,
		hash2(seed, 44) & 255
	);
}

unsigned int Chose::initialSeed = random_seed();
