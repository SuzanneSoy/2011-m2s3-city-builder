#ifndef _RULES_BATIMENT_Mur_HH_
#define _RULES_BATIMENT_Mur_HH_

#include "all_includes.hh"

class MurQuad: public Chose {
    private :
	Quad c;
	Quad ch;
	bool window;        // Contient une fenêtre ou non.
	Quad windowPos;
	Quad windowPosh;

    public :

	MurQuad(Quad c, Quad ch, bool _windows=false);
	virtual void triangulation();
	virtual bool split();
	virtual void getBoundingBoxPoints();
	void setWindow();
};

#endif

