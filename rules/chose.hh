#ifndef _RULES_CHOSE_HH_
#define _RULES_CHOSE_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class Chose {
public :
	static unsigned int initialSeed;
	unsigned int seed;
	std::vector<Chose*> children;
	std::vector<GPUTriangle*> triangles;
	LodNode lod;

public :
	void display();
	void displayNormals();
	void drawAABB(); // DEBUG
	virtual bool split() { return false; };
	virtual bool merge();
	virtual void triangulation() { clearTriangles(); };
	virtual void updateAABB();

protected :
	void addBBPoint(const Vertex v);
	void addBBPoints(const Triangle t);
	void addBBPoints(const Triangle t, float height);
	void addBBPoints(const Quad q);
	void addBBPoints(const Quad q, float height);
	virtual void getBoundingBoxPoints() = 0;
	virtual float LODFactor();
	Chose();
	~Chose();
	inline void addEntropy(unsigned int x1) {
		seed = hash2(seed, x1);
	}
	inline void addEntropy(unsigned int x1, unsigned int x2) {
		addEntropy(x1); addEntropy(x2);
	}
	inline void addEntropy(unsigned int x1, unsigned int x2, unsigned int x3) {
		addEntropy(x1, x2); addEntropy(x3);
	}
	inline void addEntropy(unsigned int x1, unsigned int x2, unsigned int x3, unsigned int x4) {
		addEntropy(x1, x2); addEntropy(x3, x4);
	}
	inline void addEntropy(Vertex v1) {
		addEntropy(float2uint(v1.x), float2uint(v1.y));
	}
	inline void addEntropy(Vertex v1, Vertex v2) {
		addEntropy(v1); addEntropy(v2);
	}
	inline void addEntropy(Vertex v1, Vertex v2, Vertex v3) {
		addEntropy(v1, v2); addEntropy(v3);
	}
	inline void addEntropy(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
		addEntropy(v1, v2); addEntropy(v3, v4);
	}
	inline void addEntropy(Quad q) {
		addEntropy(q[NE], q[SE], q[SW], q[NW]);
	}
	inline void addEntropy(Triangle t) {
		addEntropy(t[LEFT], t[TOP], t[RIGHT]);
	}
	void addChild(Chose* c);

	void addGPUTriangle(Vertex left, Vertex top, Vertex right, unsigned int rgb);
	void addGPUTriangle(Triangle t, unsigned int rgb);
	void addGPUQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, unsigned int rgb);
	void addGPUQuad(Quad q, unsigned int rgb);
	void addGPUFourQuads(Quad q, Quad qh, unsigned int rgb);
	void addGPUOcto(Vertex ne, Vertex se, Vertex sw, Vertex nw,
			Vertex neh, Vertex seh, Vertex swh, Vertex nwh,
			unsigned int rgb);
	void addGPUOcto(Quad q, Quad qh, unsigned int rgb);
private:
	void clearChildren();
	void clearTriangles();
};

#endif
