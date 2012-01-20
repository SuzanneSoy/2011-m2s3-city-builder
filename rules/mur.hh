#ifndef _RULES_MUR_HH_
#define _RULES_MUR_HH_

#include "all_includes.hh"

class MurQuad: public Chose {
private :
	Quad c;
	Quad ch;
	bool window;        // Contient une fenêtre ou non.
	Quad windowPos;
	Quad windowPosh;
	bool top;
	bool bottom;
	bool door;

public :

	MurQuad(Quad c, Quad ch, bool _window=false, bool _top=false, bool _bottom=false, bool _door=false);
	virtual void triangulation();
	virtual bool split();
	virtual void getBoundingBoxPoints();
	void setWindowOrDoor();
};

class PlancherPlafond: public Chose {
public:
	enum Type {
		PLANCHER,
		PLAFOND
	};
private:
	Quad c;
	Type type;

public:
	PlancherPlafond(Quad _c, Type _type);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif

