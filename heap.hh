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
	Heap();
	void insert(int key, Chose* value);
	void remove(Chose* value);
	Chose* popIfLessThan(int key);
	void setId(int id);
};
