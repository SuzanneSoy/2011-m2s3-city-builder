#include "all_includes.hh"

Segment::Segment(Vertex u, Vertex v): u(u), v(v) {}

int Segment::length() {
	return (u-v).norm();
}

Segment Segment::reduce(int value) {
    float reduc = (float)length()/(float)value;
    return Segment(u,u+((v - u) / reduc));
}

int Segment::width() {
	return std::abs(u.x - v.x);
}

int Segment::height() {
	return std::abs(u.y - v.y);
}

Vertex Segment::randomPos(int seed, int n, int a, int b) {
	int pos = hashInRange(seed, n, a, b);
	return (u * pos + v * (100-pos)) / 100;
}
