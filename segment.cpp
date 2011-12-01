#include "all_includes.hh"

Segment::Segment(Vertex u, Vertex v): u(u), v(v) {}

int Segment::length() {
	return (u-v).norm();
}

int Segment::width() {
	return std::abs(u.x - v.x);
}

int Segment::height() {
	return std::abs(u.y - v.y);
}
