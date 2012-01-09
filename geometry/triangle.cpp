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
	float at = angle();
	float a3 = Triangle(c[TOP],c[RIGHT],c[LEFT]).angle();
	float a1 = Angle::Pi - at - a3;
	return std::min(std::min(a1, at), a3);
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

Triangle Triangle::insetLTR(float offset) const {
	return (*this).inset(LEFTSIDE, offset).inset(RIGHTSIDE, offset).inset(BASE, offset);
}

Triangle operator+(const Triangle& t, const Vertex& v) {
	return Triangle(t[LEFT] + v, t[TOP] + v, t[RIGHT] + v);
}

Vertex Triangle::randomPoint(int seed, int n) const {
	float rndl = hashInRange(seed, n, 0, 100);
	float rndr = hashInRange(seed, hash2(n, 42), 0, 100 - rndl);
	return c[TOP] + (c[LEFT] - c[TOP]) * (rndl/100.f) + (c[RIGHT] - c[TOP]) * (rndr/100.f);
}
