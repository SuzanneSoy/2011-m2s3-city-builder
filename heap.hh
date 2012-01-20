#ifndef _HEAP_HH_
#define _HEAP_HH_

#include "all_includes.hh"

class HeapNode {
public:
	HeapNode(float _key, Chose* _value) : key(_key), value(_value) {};
	float key;
	Chose* value;
	friend bool operator< (const HeapNode &a, const HeapNode &b) {
		return (a.key < b.key || (a.key >= b.key && a.key <= b.key && a.value < b.value));
	}
};

class Heap {
private:
	std::set<HeapNode> bst;
	float factor; // -1.f ou +1.f
public:
	Heap();
	void insert(float key, Chose* value);
	void remove(float key, Chose* value);
	Chose* popIfLessThan(float key);
	bool lessThan(float a, float b); // Renvoie true ssi a < b dans l'ordre du tas.
	void init(int factor); // factor = -1 pour tas Min, 1 pour tas max
};

#endif
