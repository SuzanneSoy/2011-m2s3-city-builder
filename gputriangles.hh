#ifndef _GPUTRIANGLES_HH_
#define _GPUTRIANGLES_HH_

#include "all_includes.hh"

class GPUTriangles {
private:
	int current;
	int aim;
	int maxSize;
	Triangle* triangles;

	int nToAdd;
	int nTrianglesToAdd;
	Chose** cToAdd;

	int nTrianglesToRemove;
	int nToRemove;
	Chose** cToRemove;
public:
	GPUTriangles(int maxSize);
	void add(Chose*);
	void remove(Chose*);
	void commit();
	// Renvoie true si on peut commit, false s'il y a trop de triangles.
	bool canCommit();
	bool canAdd(Chose* c);
};

#endif
