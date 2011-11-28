#ifndef _RULES_CHOSE_HH_
#define _RULES_CHOSE_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class Chose {
public:
	static const unsigned int initialSeed = 42;
	unsigned int seed;
	std::vector<Chose*> children;
	std::vector<Triangle*> triangles;
public:
	Chose();
	inline void addEntropy(unsigned int x1) { seed = hash2(seed, x1); }
	inline void addEntropy(unsigned int x1, unsigned int x2) { addEntropy(x1); addEntropy(x2); }
	inline void addEntropy(unsigned int x1, unsigned int x2, unsigned int x3) { addEntropy(x1, x2); addEntropy(x3); }
	inline void addEntropy(unsigned int x1, unsigned int x2, unsigned int x3, unsigned int x4) { addEntropy(x1, x2); addEntropy(x3, x4); }
	inline void addEntropy(Vertex v1) { addEntropy(v1.x, v1.y); }
	inline void addEntropy(Vertex v1, Vertex v2) { addEntropy(v1); addEntropy(v2); }
	inline void addEntropy(Vertex v1, Vertex v2, Vertex v3) { addEntropy(v1, v2); addEntropy(v3); }
	inline void addEntropy(Vertex v1, Vertex v2, Vertex v3, Vertex v4) { addEntropy(v1, v2); addEntropy(v3, v4); }
	void addChild(Chose* c);
	void addTriangle(Triangle* t);
	virtual bool subdivide() = 0;
	virtual void triangulation() = 0;
	void display();
};

std::ostream& operator<<(std::ostream& os, const Chose& r);
std::ostream& operator<<(std::ostream& os, const Chose* r);

#endif
