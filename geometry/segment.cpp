#include "all_includes.hh"

Segment::Segment(Vertex u, Vertex v): u(u), v(v) {}

float Segment::length() {
	return (u-v).norm();
}

Segment Segment::reduce(float value) {
    float reduc = (float)length()/(float)value;
    return Segment(u,u+((v - u) / reduc));
}

float Segment::width() {
	return std::abs(u.x - v.x);
}

float Segment::height() {
	return std::abs(u.y - v.y);
}

Vertex Segment::randomPos(int seed, int n, float a, float b) {
	float pos = floatInRange(seed, n, a, b);
	return (u * pos + v * (1-pos));
}
