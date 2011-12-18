#ifndef _RULES_BATIMENTJARDIN_HH
#define _RULES_BATIMENTJARDIN_HH

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuadJardin : public Chose {
    private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuadJardin(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~BatimentQuadJardin();
	int width();
	int height();
	virtual bool split();
	virtual bool merge();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual std::vector<Vertex*> getBoundingBoxPoints() const;
};

#endif
