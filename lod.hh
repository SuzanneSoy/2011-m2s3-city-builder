#ifndef _LOD_HH_
#define _LOD_HH_

#include "all_includes.hh"

class Lod {
private :
	// TODO : puisqu'on utilise *soit* la mergeBox, *soit* la
	// splitBox, réutiliser le heap In pour merge.
	Heap merge[6];    // {xMin, xMax, yMin, yMax, zMin, zMax}.
	Heap splitIn[6];  // {xMinIn, xMaxIn, yMinIn, yMaxIn, zMinIn, zMaxIn}.
	Heap splitOut[6]; // {xMinOut, xMaxOut, yMinOut, yMaxOut, zMinOut, zMaxOut}.
	float camera[3];
private:
	void doSplit(Chose* c);
	void doMerge(Chose* c);
public :
	Lod(Vertex camera, Chose* root);
	void addMergeCube(Chose* chose);
	void addSplitCube(Chose* chose);
	void setCamera(Vertex camera);
};

struct LodNode {
	int heaps[18];
	float aabb[6];
	float splitBox[12];
	float mergeBox[6];
    int inCounter;
	bool firstBBPoint;
};

#endif
