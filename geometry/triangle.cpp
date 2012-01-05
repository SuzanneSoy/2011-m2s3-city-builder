Triangle::Triangle() {
}
Triangle::Triangle(Vertex left, Vertex top, Vertex right) {
	c[0] = left;
	c[1] = top;
	c[2] = right;
}

float Triangle::cosAngle() const {
	return (c[0]-c[1]).cosAngle(c[2]-c[1]);
}

float Triangle::angle() const {
	return std::acos(cosAngle());
}

float Triangle::minAngle() const {
	float a2 = angle();
	float a3 = Triangle(c[1],c[2],c[0]).angle();
	float a1 = Angle::Pi - a2 - a3;
	return std::min(std::min(a1, a2), a3);
}

float Triangle::minLength() const {
	return std::min(std::min((c[0] - c[1]).norm(), (c[1] - c[2]).norm()), (c[2] - c[0]).norm());
}

float Triangle::maxLength() const {
	return std::max(std::max((c[0] - c[1]).norm(), (c[1] - c[2]).norm()), (c[2] - c[0]).norm());
}

void Triangle::offsetBase(int offset) {
	Quad q = Quad(c[1], c[0], c[2], c[1]);
	q.offset(S, -offset);
	c[0] = q[SE];
	c[1] = q[NE];
	c[2] = q[SW];
}

Triangle operator+(const Triangle& t, const Vertex& v) {
	return Triangle(t[LEFT] + v, t[TOP] + v, t[RIGHT] + v);
}
