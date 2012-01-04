#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {
}

// TODO : Est-ce vraiment nécessaire ?
Chose::~Chose() {
    children.clear();
    triangles.clear();
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

void Chose::addGPUTriangle(GPUTriangle* t) {
	triangles.push_back(t);
}

bool Chose::merge() {
    children.clear();
	// triangles.clear();
    return true;
}

void Chose::addGPUQuad(Vertex u, Vertex v, Vertex w, Vertex x, char r, char g, char b) {
    this->addGPUTriangle(new GPUTriangle(u,x,w,r,g,b));
    this->addGPUTriangle(new GPUTriangle(w,v,u,r,g,b));
}

void Chose::addGPUQuad(Quad q, char r, char g, char b) {
	addGPUQuad(q[NE], q[SE], q[SW], q[NW], r, g, b);
}

void Chose::addGPUOcto(Vertex a, Vertex b, Vertex c, Vertex d,
                    Vertex e, Vertex f, Vertex g, Vertex h, char red, char green, char blue) {
    this->addGPUQuad(a,b,c,d,red,green,blue);
    this->addGPUQuad(e,f,g,h,red,green,blue);
    this->addGPUQuad(b,a,e,f,red,green,blue);
    this->addGPUQuad(c,b,f,g,red,green,blue);
    this->addGPUQuad(d,c,g,h,red,green,blue);
    this->addGPUQuad(a,d,h,e,red,green,blue);
}

void Chose::addGPUOcto(Quad q1, Quad q2, char red, char green, char blue) {
	addGPUOcto(q1[NE], q1[SE], q1[SW], q1[NW], q2[NE], q2[SE], q2[SW], q2[NW], red, green, blue);
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
