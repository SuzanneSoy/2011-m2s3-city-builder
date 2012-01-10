Triangle::Triangle() {
}
Triangle::Triangle(Vertex left, Vertex top, Vertex right) {
	c[LEFT] = left;
	c[TOP] = top;
	c[RIGHT] = right;
}

float Triangle::cosAngle() const {
	return (c[LEFT]-c[TOP]).cosAngle(c[RIGHT]-c[TOP]);
}

float Triangle::angle() const {
	return std::acos(cosAngle());
}

float Triangle::minAngle() const {
	float at = angle();
	float ar = Triangle(c[TOP],c[RIGHT],c[LEFT]).angle();
	float al = Angle::Pi - at - ar;
	return std::min(std::min(al, at), ar);
}

float Triangle::maxAngle() const {
	float at = angle();
	float ar = Triangle(c[TOP],c[RIGHT],c[LEFT]).angle();
	float al = Angle::Pi - at - ar;
	return std::max(std::max(al, at), ar);
}

float Triangle::minLength() const {
	return std::min(std::min((c[LEFT] - c[TOP]).norm(), (c[TOP] - c[RIGHT]).norm()), (c[RIGHT] - c[LEFT]).norm());
}

float Triangle::maxLength() const {
	return std::max(std::max((c[LEFT] - c[TOP]).norm(), (c[TOP] - c[RIGHT]).norm()), (c[RIGHT] - c[LEFT]).norm());
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
	float rndl = floatInRange(seed, n, 0, 1);
	float rndr = floatInRange(seed, hash2(n, 42), 0, 1 - rndl);
	return c[TOP] + (c[LEFT] - c[TOP]) * (rndl) + (c[RIGHT] - c[TOP]) * (rndr);
}

float Triangle::surface() const {
	float hauteur = Segment(c[TOP], (c[TOP] - c[LEFT]).projectOn(c[RIGHT] - c[LEFT])).length();
	float base = Segment(c[LEFT], c[RIGHT]).length();
	return (base * hauteur) / 2.f;
}
