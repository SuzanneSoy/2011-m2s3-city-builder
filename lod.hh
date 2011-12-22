#ifndef _LOD_HH_
#define _LOD_HH_
#include "all_includes.hh"

class Lod {
private :
	Heap merge[6];	// {xMin, xMax, yMin, yMax, zMin, zMax}.
	Heap split[12];	// {xMinIn, xMinOut, xMaxIn, xMaxOut, yMinIn, yMaxOut, yMaxIn, yMaxOut, zMinIn, zMinOut, zMaxIn, zMaxOut}.
	float camera[3];
private:
	inline float NegateEven(float value, int evenodd) {
		return (value*((evenodd&1) ? 1 : -1));
	}
	inline float NegateOdd(float value, int evenodd) {
		return (value*((evenodd&1) ? -1 : 1));
	}
	void doSplit(Chose* c);
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
