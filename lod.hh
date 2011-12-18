#ifndef _LOD_HH_
#define _LOD_HH_
#include "all_includes.hh"

class Abr {
	private :
	std::multimap<int, Chose*> map;

	public :
	Abr();
	void insert(int key, Chose* value);		//TODO Retourne un item*.
	void remove(int key, Chose* value);		//TODO Prend un item*.
	Chose* popIfLessThan(int key);
};


class Lod {
	private :
	Abr merge[6];	// {xMin, xMax, yMin, yMax, zMin, zMax}.
	Abr split[12];	// {xMinIn, xMinOut, xMaxIn, xMaxOut, yMinIn, yMaxOut, yMaxIn, yMaxOut, zMinIn, zMinOut, zMaxIn, zMaxOut}.
	float camera[3];

	public :
	Lod();
	Lod(float[3]);
	void addMergeCube(Chose* chose, int limits[6]);
	void addSplitCube(Chose* chose, int limits[6]);
	void setCamera(float camera[3]);
};

struct HeapNode {
	int key;
	Chose* value;
};

class Heap {
private:
	int id;
	static const int log2BucketSize = 9; // 2^9 = 512
	static const int bucketSize = (1 << log2BucketSize);
	HeapNode** buckets;
	int lastAllocatedBucket;
	int bucketArraySize;
	int lastNode;
private:
	inline int getBucket(int node) {
		return (node >> log2BucketSize);
	}
	inline int getIndex(int node) {
		return (node & (bucketSize - 1));
	}
	void allocateBucket(); // Allocate into last+1
	void freeBucket(); // free last
	void siftUp(int node);
	void siftDown(int node);
	inline int parent(int node) { return (node - 1)/2; }
	inline int leftchild(int node) { return node * 2 + 1; }
	inline int rightchild(int node) { return node * 2 + 2; }
public:
	Heap(int id);
	void insert(int key, Chose* value);
	void remove(int node);
	Chose* popIfLessThan(int key);
};

class LodNode {
public:
	int heaps[18];
	int aabb[6];
    int inCounter;
	HeapNode* splitCube[12];
	HeapNode* mergeCube[6];
};

#endif
