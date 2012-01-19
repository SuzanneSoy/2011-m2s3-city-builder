#include "all_includes.hh"

Segment::Segment(Vertex _u, Vertex _v): u(_u), v(_v) {}

float Segment::length() {
	return (u-v).norm();
}

Segment Segment::reduce(float value) {
    float reduc = (float)length()/(float)value;
    return Segment(u,u+((v - u) / reduc));
}

Vertex Segment::at(float proportiannalDist) {
    return Segment(u,u+((v-u)*proportiannalDist)).v;
}

Vertex Segment::center() {
    return at(1./2.);
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

Segment operator+(const Segment& s, const Vertex& voff) {
	return Segment(s.u + voff, s.v + voff);
}
