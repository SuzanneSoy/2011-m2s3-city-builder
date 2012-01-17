#ifndef _RULES_ARCHITECTURE_BATIMENT_HH_
#define _RULES_ARCHITECTURE_BATIMENT_HH_

#include "all_includes.hh"

class BatimentQuad_ : public Chose {
	Quad c;
public:
	BatimentQuad_(Quad _c);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

class BatimentTri_ : public Chose {
	Triangle c;
public:
	BatimentTri_(Triangle _c);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

class Wall;
class MasterWall;
class WallVertex {
public:
	Vertex vertex;
	MasterWall* onMasterWall;
	float posOnMasterWall;
	std::map<WallVertex*, MasterWall*> endWall;
public:
	operator Vertex() { return vertex; };
	WallVertex(Vertex _v) : vertex(_v), onMasterWall(NULL), posOnMasterWall(0) {};
	WallVertex(Vertex _v, MasterWall* _onWall, float _posOnWall) : vertex(_v), onMasterWall(_onWall), posOnMasterWall(_posOnWall) {};
	void addEndWall(WallVertex* v, MasterWall* w) { endWall.insert(std::pair<WallVertex*, MasterWall*>(v, w)); }
};

class MasterWall;
class MasterWallIterator : public std::iterator<std::input_iterator_tag, MasterWall> {
private:
	std::map<float, WallVertex*>::iterator it;
	bool reverse;
public:
	MasterWallIterator(std::map<float, WallVertex*>::iterator mwit) : it(mwit), reverse(false) {};
	MasterWallIterator(std::map<float, WallVertex*>::iterator mwit, bool _reverse) : it(mwit), reverse(_reverse) {};
	MasterWallIterator(std::map<float, WallVertex*>::reverse_iterator mwrit) : it(--(mwrit.base())), reverse(false) {};
	MasterWallIterator(const MasterWallIterator& copy) : it(copy.it), reverse(copy.reverse) {};
	bool operator==(const MasterWallIterator& mwit) const { return it == mwit.it; };
	bool operator!=(const MasterWallIterator& mwit) const { return it != mwit.it; };
	WallVertex* operator*() { return (*it).second; };
	WallVertex* operator->() { return (*it).second; };
	virtual void operator++() { if (reverse) it--; else it++; }
};

class MasterWall {
private:
	std::map<float, WallVertex*> vertices;
public:
	typedef MasterWallIterator iterator;
	MasterWall(WallVertex* u, WallVertex* v) {
		insert(0, u);
		insert(1, v);
	};
	void insert(float position, WallVertex* u) {
		vertices.insert(std::pair<float, WallVertex*>(position,u));
	};
	WallVertex* u() { return vertices.begin()->second; };
	WallVertex* v() { return vertices.rbegin()->second; };
	iterator begin() { return iterator(vertices.begin()); }
	iterator end() { return iterator(vertices.end()); }
	iterator rbegin() { return iterator(vertices.rbegin()); }
	iterator rend() { return iterator(vertices.rend()); }
	iterator find(float position) { return iterator(vertices.find(position)); }
	iterator rfind(float position) { return iterator(vertices.find(position), true); }
	iterator find(float position, bool reverse) { return iterator(vertices.find(position), reverse); }
};

class Wall {
public:
	WallVertex* u;
	WallVertex* v;
	float uPosOnMasterWall;
	float vPosOnMasterWall;
	MasterWall* master;
public:
	Wall(WallVertex* _u, WallVertex* _v) {
		u = _u;
		v = _v;
		if (u->onMasterWall != NULL && u->onMasterWall == v->onMasterWall) { // u et v au milieu de master
			master = u->onMasterWall;
			uPosOnMasterWall = u->posOnMasterWall;
			vPosOnMasterWall = v->posOnMasterWall;
		} else if (u->onMasterWall != NULL && (u->onMasterWall->u() == v || u->onMasterWall->v() == v)) { // u au milieu de master, v au bord
			master = u->onMasterWall;
			uPosOnMasterWall = u->posOnMasterWall;
			vPosOnMasterWall = (master->u() == v) ? 0 : 1;
		} else if (v->onMasterWall != NULL && (v->onMasterWall->u() == u || v->onMasterWall->v() == u)) { // v au milieu de master, u au bord
			master = v->onMasterWall;
			uPosOnMasterWall = (master->u() == u) ? 0 : 1;
			vPosOnMasterWall = v->posOnMasterWall;
		} else {
			std::map<WallVertex*, MasterWall*>::iterator it = u->endWall.find(v);
			if (it != u->endWall.end()) { // u et v au bord d'un master existant.
				master = it->second;
				uPosOnMasterWall = (master->u() == u) ? 0 : 1;
				vPosOnMasterWall = (master->u() == u) ? 1 : 0;
			} else { // u et v au bord d'un nouveau master.
				master = new MasterWall(u, v);
				uPosOnMasterWall = 0;
				vPosOnMasterWall = 1;
				u->addEndWall(v, master);
				v->addEndWall(u, master);
			}
		}
	};
	operator Segment () {
		return Segment(*u, *v);
	}
	WallVertex* randomPos(int seed, int n, float a, float b) {
		float width = vPosOnMasterWall - uPosOnMasterWall;
		float pos = floatInRange(seed, n, uPosOnMasterWall + a*width, uPosOnMasterWall + b*width);
		MasterWallIterator mwi = master->find(pos);
		if (mwi == master->end()) { // Il n'y a pas encore de WallVertex à cette position sur master.
			Vertex mu = *(master->u());
			Vertex mv = *(master->v());
			WallVertex* wv = new WallVertex(mu * pos + mv * (1-pos), master, pos);
			master->insert(pos, wv);
			return wv;
		} else { // Il y a déjà un WallVertex à cette position sur master.
			return (*mwi);
		}
	};
	typedef MasterWall::iterator iterator;
	iterator begin() { return master->find(uPosOnMasterWall, (uPosOnMasterWall > vPosOnMasterWall)); };
	iterator end() { return master->find(vPosOnMasterWall, (uPosOnMasterWall > vPosOnMasterWall)); };
};

#endif
