#include "all_includes.hh"

Heap::Heap() {
}

void Heap::init(int _factor) { factor = (float)_factor; }

void Heap::insert(float key, Chose* value) {
	bst.insert(HeapNode(key * factor, value));
}

void Heap::remove(float key, Chose* value) {
	bst.erase(HeapNode(key * factor, value));
}

bool Heap::lessThan(float a, float b) {
	return (a * factor < b * factor);
}

Chose* Heap::popIfLessThan(float key) {
	std::set<HeapNode>::iterator min = bst.begin();
	if (min != bst.end() && min->key < key * factor) {
		Chose* ret = min->value;
		bst.erase(min);
		return ret;
	}
	return NULL;
}
