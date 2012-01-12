#ifndef _GEOMETRY_DIRECTIONS_HH_
#define _GEOMETRY_DIRECTIONS_HH_

class EnsembleCardinaux {
protected:
	char v;
	EnsembleCardinaux(char _v) : v(_v) {}
public:
	friend EnsembleCardinaux operator| (const EnsembleCardinaux ec1, const EnsembleCardinaux ec2) {
		return EnsembleCardinaux(ec1.v | ec2.v);
	}
	friend EnsembleCardinaux operator& (const EnsembleCardinaux ec1, const EnsembleCardinaux ec2) {
		return EnsembleCardinaux(ec1.v & ec2.v);
	}
	friend bool operator== (const EnsembleCardinaux ec1, const EnsembleCardinaux ec2) {
		return (ec1.v == ec2.v);
	}
	friend bool operator!= (const EnsembleCardinaux ec1, const EnsembleCardinaux ec2) {
		return (ec1.v != ec2.v);
	}
};

class Cardinal : public EnsembleCardinaux {
private:
	static const char rotationTable[9];
public:
	Cardinal(int x) : EnsembleCardinaux((char)(1 << (x & 3))) {}
	operator int () const {
		return rotationTable[(int)v];
	}
	friend Cardinal operator+ (const Cardinal c, const int n) {
		return Cardinal(rotationTable[(int)c.v] + n);
	}
	friend Cardinal operator- (const Cardinal c, const int n) {
		return Cardinal(rotationTable[(int)c.v] - n);
	}
};

const Cardinal N = Cardinal(0);
const Cardinal E = Cardinal(1);
const Cardinal S = Cardinal(2);
const Cardinal W = Cardinal(3);

// Plus ou moins la même chose que Cardinal.
class Coin {
private:
	char v;
	static const char rotationTable[9];
public:
	Coin(int x) : v((char)(1 << (x & 3))) {}
	operator int () const {
		return (int)rotationTable[(int)v];
	}
	friend Coin operator+ (const Coin c, const int n) {
		return Coin(rotationTable[(int)c.v] + n);
	}
	friend Coin operator- (const Coin c, const int n) {
		return Coin(rotationTable[(int)c.v] - n);
	}
	friend bool operator== (const Coin c1, const Coin c2) {
		return (c1.v == c2.v);
	}
	friend bool operator!= (const Coin c1, const Coin c2) {
		return (c1.v != c2.v);
	}
};

const Coin NE = Coin(0);
const Coin SE = Coin(1);
const Coin SW = Coin(2);
const Coin NW = Coin(3);

// Pour les triangles, c'est quasiment identique, il y a sûrement moyen de factoriser ça.

class EnsembleCotesTriangle {
protected:
	char v;
	EnsembleCotesTriangle(char _v) : v(_v) {}
public:
	friend EnsembleCotesTriangle operator| (const EnsembleCotesTriangle ec1, const EnsembleCotesTriangle ec2) {
		return EnsembleCotesTriangle(ec1.v | ec2.v);
	}
	friend EnsembleCotesTriangle operator& (const EnsembleCotesTriangle ec1, const EnsembleCotesTriangle ec2) {
		return EnsembleCotesTriangle(ec1.v & ec2.v);
	}
	friend bool operator== (const EnsembleCotesTriangle ec1, const EnsembleCotesTriangle ec2) {
		return (ec1.v == ec2.v);
	}
	friend bool operator!= (const EnsembleCotesTriangle ec1, const EnsembleCotesTriangle ec2) {
		return (ec1.v != ec2.v);
	}
};

class CoteTriangle : public EnsembleCotesTriangle {
private:
	static const char rotationTable[5];
public:
	CoteTriangle(int x) : EnsembleCotesTriangle((char)(1 << (((x % 3) + 3) % 3))) {}
	operator int () const {
		return rotationTable[(int)v];
	}
	friend CoteTriangle operator+ (const CoteTriangle c, const int n) {
		return CoteTriangle(rotationTable[(int)c.v] + n);
	}
	friend CoteTriangle operator- (const CoteTriangle c, const int n) {
		return CoteTriangle(rotationTable[(int)c.v] - n);
	}
};

const CoteTriangle LEFTSIDE = CoteTriangle(0);
const CoteTriangle RIGHTSIDE = CoteTriangle(1);
const CoteTriangle BASE = CoteTriangle(2);

// Plus ou moins la même chose que CoteTriangle.
class SommetTriangle {
private:
	char v;
	static const char rotationTable[5];
public:
	SommetTriangle(int x) : v((char)(1 << (((x % 3) + 3) % 3))) {}
	operator int () const {
		return (int)rotationTable[(int)v];
	}
	friend SommetTriangle operator+ (const SommetTriangle c, const int n) {
		return SommetTriangle(rotationTable[(int)c.v] + n);
	}
	friend SommetTriangle operator- (const SommetTriangle c, const int n) {
		return SommetTriangle(rotationTable[(int)c.v] - n);
	}
	friend bool operator== (const SommetTriangle c1, const SommetTriangle c2) {
		return (c1.v == c2.v);
	}
	friend bool operator!= (const SommetTriangle c1, const SommetTriangle c2) {
		return (c1.v != c2.v);
	}
};

const SommetTriangle LEFT = SommetTriangle(0);
const SommetTriangle TOP = SommetTriangle(1);
const SommetTriangle RIGHT = SommetTriangle(2);

#endif
