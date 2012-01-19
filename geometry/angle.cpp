#include "all_includes.hh"

float Angle::r2d(float rad) { return rad / Pi * 180; }
float Angle::d2r(float deg) { return deg / 180 * Pi; }

Angle3D::Angle3D() : h(Vertex(1,0,0)), l(Vertex(0,1,0)), u(Vertex(0,0,1)) {}
Angle3D::Angle3D(Vertex _h, Vertex _l, Vertex _u) : h(_h), l(_l), u(_u) {}

// Formules : http://www.nbb.cornell.edu/neurobio/land/OldStudentProjects/cs490-94to95/hwchen/
Angle3D Angle3D::rotateH(float angle) const {
	return Angle3D(h, l*std::cos(angle) + u*std::sin(angle), l*-std::sin(angle) + u*std::cos(angle));
}

Angle3D Angle3D::rotateL(float angle) const {
	return Angle3D(h*std::cos(angle) + u*std::sin(angle), l, h*-std::sin(angle) + u*std::cos(angle));
}

Angle3D Angle3D::rotateU(float angle) const {
	return Angle3D(h*std::cos(angle) + l*-std::sin(angle), h*std::sin(angle) + l*std::cos(angle), u);
}
