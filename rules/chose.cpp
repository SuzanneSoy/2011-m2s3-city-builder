#include "all_includes.hh"

Chose::Chose() : seed(initialSeed) {}

std::ostream& operator<<(std::ostream& os, const Chose* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Chose& r) {
	(void)r; // unused
	return os << "Chose";
}
