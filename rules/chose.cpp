#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {
}

void Chose::clearChildren() {
	std::vector<Chose*>::iterator it;
	for (it = children.begin(); it != children.end(); it++)
		delete *it;
	children.clear();
}

void Chose::clearTriangles() {
	std::vector<GPUTriangle*>::iterator it;
	for (it = triangles.begin(); it != triangles.end(); it++)
		delete *it;
	triangles.clear();
}

Chose::~Chose() {
	clearChildren();
	clearTriangles();
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

void Chose::merge() {
	clearChildren();
}

void Chose::addGPUTriangle(Vertex left, Vertex top, Vertex right, unsigned int rgb) {
	triangles.push_back(new GPUTriangle(left, top, right, Couleurs::r(rgb), Couleurs::g(rgb), Couleurs::b(rgb)));
}

void Chose::addGPUTriangle(Triangle t, unsigned int rgb) {
	addGPUTriangle(t[LEFT], t[TOP], t[RIGHT], rgb);
}

void Chose::addGPUQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, unsigned int rgb) {
	this->addGPUTriangle(nw, ne, se, rgb);
	this->addGPUTriangle(se, sw, nw, rgb);
}

void Chose::addGPUQuad(Quad q, unsigned int rgb) {
	addGPUQuad(q[NE], q[SE], q[SW], q[NW], rgb);
}

void Chose::addGPUFourQuads(Quad q, Quad qh, unsigned int rgb) {
	for (int i = 0; i < 4; i++)
		addGPUQuad(Quad(qh[NE+i], q[NE+i], q[SE+i], qh[SE+i]), rgb);
}

void Chose::addGPUThreeQuads(Triangle t, Triangle th, unsigned int rgb) {
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(th[LEFT+i], t[LEFT+i], t[TOP+i], th[TOP+i]), rgb);
}

void Chose::addGPUOcto(Vertex ne, Vertex se, Vertex sw, Vertex nw,
		Vertex neh, Vertex seh, Vertex swh, Vertex nwh, unsigned int rgb) {
	addGPUOcto(Quad(ne,se,sw,nw), Quad(neh,seh,swh,nwh), rgb);
}

void Chose::addGPUOcto(Quad q, Quad qh, unsigned int rgb) {
	this->addGPUQuad(q[SE], q[NE], q[NW], q[SW], rgb);
	this->addGPUQuad(qh[NE], qh[SE], qh[SW], qh[NW], rgb);
	for (int i = 0; i < 4; i++)
		this->addGPUQuad(q[NE+i], q[SE+i], qh[SE+i], qh[NE+i], rgb);
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
	float thisSplitFactor = Dimensions::splitFactor * LODFactor();
	// TODO : adapt mergeFactor to Camera::moveSensitivity
	float thisMergeFactor = thisSplitFactor * std::max(1.01f, Dimensions::mergeFactor);
	float nonFacingFactor = 2.f/3.f;
	lod.firstBBPoint = true;
	getBoundingBoxPoints();
	float size[3];
	float center[3];
	for (int i = 0; i < 3; i++) {
		size[i] = lod.aabb[2*i+1] - lod.aabb[2*i];
		center[i] = (lod.aabb[2*i] + lod.aabb[2*i+1])/2.f;
	}
	float areaFacing[3];
	for (int i = 0; i < 3; i++)
		areaFacing[i] = size[(i+1)%3]*size[(i+1)%3];
	for (int i = 0; i < 3; i++) {
		float pseudoLength = std::max(size[i]/2.f, std::sqrt(areaFacing[i] + areaFacing[(i+1)%3] * nonFacingFactor + areaFacing[(i+1)%3] * nonFacingFactor));
		float splitDistance = thisSplitFactor * pseudoLength;
		float mergeDistance = thisMergeFactor * pseudoLength;
		lod.splitBox[2*i]   = center[i] - splitDistance;
		lod.splitBox[2*i+1] = center[i] + splitDistance;
		lod.mergeBox[2*i]   = center[i] - mergeDistance;
		lod.mergeBox[2*i+1] = center[i] + mergeDistance;
	}
}

float Chose::LODFactor() {
	return 1.f;
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
			hash2(seed, 42) & 0xffffff
	);
}

unsigned int Chose::initialSeed = random_seed();
