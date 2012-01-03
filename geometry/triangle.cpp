Triangle::Triangle() {
}
Triangle::Triangle(Vertex left, Vertex top, Vertex right) {
	c[0] = left;
	c[1] = top;
	c[2] = right;
}

float Triangle::cosAngle() {
	return (c[0]-c[1]).cosAngle(c[2]-c[1]);
}

float Triangle::angle() {
	return std::acos(cosAngle());
}

float Triangle::minAngle() {
	float a2 = angle();
	float a3 = Triangle(c[1],c[2],c[0]).angle();
	float a1 = Angle::Pi - a2 - a3;
	return std::min(std::min(a1, a2), a3);
}

void Triangle::offsetBase(int offset) {
	Quad q = Quad(c[1], c[0], c[2], c[1]);
	q.offset(S, -offset);
	c[0] = q.c[1];
	c[1] = q.c[0];
	c[2] = q.c[2];
}
