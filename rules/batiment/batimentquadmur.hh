#ifndef _RULES_BATIMENT_BATIMENTQUADMUR_HH_
#define _RULES_BATIMENT_BATIMENTQUADMUR_HH_

#include "all_includes.hh"

class BatimentQuadMur: public Chose {
    private :
	Quad c;
	Quad ch;
	bool window;        // Contient une fenêtre ou non.
	Quad windowPos;
	Quad windowPosh;

    public :

	BatimentQuadMur(Quad c, Quad ch);
	virtual void triangulation();
	virtual bool split();
	virtual void getBoundingBoxPoints();
	void setWindow(bool val);
};

#endif

