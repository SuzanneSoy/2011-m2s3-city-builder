#ifndef _HEAP_HH_
#define _HEAP_HH_

struct HeapNode {
	float key;
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
	void allocateBucket(); // Allocate into lastAllocatedBucket+1
	void freeBucket(); // free lastAllocatedBucket
	void siftUp(int node);
	void siftDown(int node);
	inline int parent(int node) { return (node - 1)/2; }
	inline int leftchild(int node) { return node * 2 + 1; }
	inline int rightchild(int node) { return node * 2 + 2; }
public:
	int factor;
	Heap();
	void insert(float key, Chose* value);
	void remove(Chose* value);
	Chose* popIfLessThan(float key);
	bool lessThan(float a, float b); // Renvoie true ssi a < b dans l'ordre du tas.
	void init(int id, int factor); // factor = -1 pour tas Min, 1 pour tas max
};

#endif
