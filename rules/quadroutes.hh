#ifndef _RULES_QUADROUTES_HH_
#define _RULES_QUADROUTES_HH_

#include "all_includes.hh"

// QuadRoutes est un quadrilatère de routes avec des angles aux coins entre 70° et 110°, et des côtés de longueur >= 10.
class QuadRoutes : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	static const int hrw = 250; // half road width : 2,50m.
	static const int minchildsize = 1000;
	static const int minQuadSize = 2500;
public:
	QuadRoutes(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	int width();
	int height();
	virtual bool subdivide();
	virtual void triangulation();
	friend std::ostream& operator<<(std::ostream& os, const QuadRoutes& r);
	friend std::ostream& operator<<(std::ostream& os, const QuadRoutes* r);
private:
	Chose* sub(Vertex ne, Vertex se, Vertex sw, Vertex nw);
};


#endif
