#include "all_includes.hh"

Abr::Abr() {
}

Abr::insert(int key, Chose* value) {
	map.insert(key,value);
}

Abr::remove(int key, Chose* value) {
	pair<multimap<int,Chose*>::iterator,multimap<int,Chose*>::iterator> ret;
	ret = map.equal_range(key);
    for (it=ret.first; it!=ret.second; ++it) {
		if ((*it).second == value) {
			map.erase(it);
			break;
		}
	}
}

Abr::popIfLessThan(int key) {
	std::multimap<int,Chose*>::iterator it = map.begin();
	
	if((*it).first < key) {
		map.erase(it);
		return (*it).second;
	} else {
		return NULL;
	}
}


#define NegateEven(v, i) ((v)*(((i)&1) ? 1 : -1))

Lod::Lod(float[3] camera) {
	this->camera = camera;
}

void Lod::setCamera(float[3] camera) {
	this->camera = camera;
	
	for(int i = 0; i < 5; i++) {
		Chose* c;
		int pos = NegateEven(camera[i>>1], i);
		while(c = merge[i].popIfLessThan(pos)) {
			for(int j = 0; j < 5; j++) {
				if(i == j) break;
				// TODO : sera merge[j].remove(c->mergeCube[j]);
				merge[j].remove(NegateEven(c->mergeCube[j], j), c);
			}
		}
	}
}

void Lod::addMergeCube(Chose* chose, int[6] limits) {
	for(int i = 0; i < 5; i++)
		merge.insert(NegateEven(limits[i], i), chose);
}

void Lod::addSplitCube(int[6] limits) {
	
}
