#include "all_includes.hh"

Lod::Lod(Vertex camera, Chose* root) {
	for (int i = 0; i < 6; i++) merge[i].setId(i);
	for (int i = 0; i < 12; i++) split[i].setId(6+i);
	this->camera[0] = camera.x;
	this->camera[1] = camera.y;
	this->camera[2] = camera.z;
	addSplitCube(root);
	setCamera(camera);
}

void Lod::setCamera(Vertex newCamera) {
	this->camera[0] = newCamera.x;
	this->camera[1] = newCamera.y;
	this->camera[2] = newCamera.z;

	// Merge.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		int pos = NegateEven(camera[i>>1], i);
		while((c = merge[i].popIfLessThan(pos))) {
			for(int j = 0; j < 6; j++) {
				if(i == j) continue;
				merge[j].remove(c);
				// TODO
			}
		}
	}
	// Split out vers split in.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		int pos = NegateOdd(camera[i>>1], i);
		while((c = split[2*i+1].popIfLessThan(pos))) {
			if(c->inCounter == 5) {
				for(int j = 0; j < 6; j++) {
					if(i == j) continue;
					split[2*j].remove(c);
				}
				doSplit(c);
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
		while((c = split[2*i].popIfLessThan(pos))) {
			c->inCounter--;
			split[2*i+1].insert(c->splitCube[i], c);
		}
	}
}

void Lod::doSplit(Chose* c) {
	// TODO
	c->split();
	std::vector<Chose*>::iterator it;
	for (it = c->children.begin(); it != c->children.end(); ++it) {
		(*it)->triangulation();
		(*it)->updateAABB();
		addSplitCube((*it));
	}
}

void Lod::addMergeCube(Chose* chose) {
	for(int i = 0; i < 5; i++)
		merge[i].insert(NegateEven(chose->lod.mergeCube[i], i), chose);
}

void Lod::addSplitCube(Chose* chose) {
	chose->inCounter = 0;
	for(int i = 0; i < 6; i++) {
		if(NegateEven(chose->lod.splitCube[i] - camera[i>>1], i) >= 0) {
			chose->inCounter++;
			split[2*i].insert(NegateEven(chose->lod.splitCube[i],i), chose);
		} else {
			split[2*i+1].insert(NegateOdd(chose->lod.splitCube[i],i), chose);
		}
	}
	// TODO : si chose->inCounter == 6, il faut le split immédiatement.
	if (chose->inCounter == 6) {
		for(int i = 0; i < 6; i++) {
			split[2*i].remove(chose);
		}
		doSplit(chose);
	}
}
