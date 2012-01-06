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

Triangle Triangle::inset(CoteTriangle side, float offset) const {
	Quad q = Quad(c[RIGHT + side], c[LEFT + side], c[TOP + side], c[RIGHT + side]);
	q = q.inset(S, offset);
	return (Triangle(q[SE], q[SW], q[NW]) >> side);
}

Triangle operator+(const Triangle& t, const Vertex& v) {
	return Triangle(t[LEFT] + v, t[TOP] + v, t[RIGHT] + v);
}
