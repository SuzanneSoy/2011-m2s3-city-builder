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
	
	// Merge.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		int pos = NegateEven(camera[i>>1], i);
		while(c = merge[i].popIfLessThan(pos)) {
			for(int j = 0; j < 6; j++) {
				if(i == j) break;
				// TODO : sera merge[j].remove(c->mergeCube[j]);
				merge[j].remove(NegateEven(c->mergeCube[j], j), c);
			}
		}
	}
	// Split out vers split in.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		int pos = NegateEven(camera[i>>1], i+1);
		while(c = split[2*i+1].popIfLessThan(pos)) {
			if(c->inCounter = 5) {
				for(int j = 0; j < 6; j++) {
					if(i == j) break;
					// TODO : sera split[2*j].remove(c->splitCube[j]);
					split[2*j].remove(NegateEven(c->splitCube[j], j), c);
				}
			}
			else {
				c->inCounter++;
				split[2*i].insert(c->splitCube[i], c);
			}
		}
	}
	
	// Split in vers split out.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		int pos = NegateEven(camera[i>>1], i);
		while(c = split[2*i].popIfLessThan(pos)) {
			c->inCounter--;
			split[2*i+1].insert(c->splitCube[i], c);
		}
	}
}

void Lod::addMergeCube(Chose* chose, int[6] limits) {
	for(int i = 0; i < 5; i++)
		merge[i].insert(NegateEven(limits[i], i), chose);
}

void Lod::addSplitCube(Chose* chose, int[6] limits) {
	chose->inCounter = 0;
	for(int i = 0; i < 5; i++)
		if(NegateEven(limits[i],i) > camera[i>>1]) {
			chose->inCounter++;
			split[2*i].insert(NegateEven(limits[i],i), chose);
		}
		else {
			split[2*i+1].insert(NegateEven(limits[i],i+1), chose);
		}
}
