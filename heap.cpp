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

extern int debug_printlod_axis;

std::ostream& operator<<(std::ostream& os, const Heap& h) {
	for (std::set<HeapNode>::iterator it = h.bst.begin(); it != h.bst.end(); ++it) {
		int i = debug_printlod_axis;
		// TODO : put a color instead of "1"
		os << it->value->lod.center[i] << ", " << (it->value->lod.splitDistance[i])/(Dimensions::splitFactor) << ", " << 1 << std::endl;
	}
	return os;
}
