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
			std::cout << "=== mer  Pop " << (int)(c) << " from merge " << i << std::endl;
			for(int j = 0; j < 6; j++) {
				if(i == j) continue;
				std::cout << "=== mer  Remove " << (int)(c) << " from merge " << j << std::endl;
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
			std::cout << "=== soi  Pop " << (int)(c) << " from split " << 2*i+1 << std::endl;
			for (int a = 0; a < 18; a++) std::cout << (c->lod.heaps[a]) << " ";
			std::cout << std::endl;
			if(c->inCounter == 5) {
				for(int j = 0; j < 6; j++) {
					if(i == j) continue;
					std::cout << "=== soi1 Remove " << (int)(c)<<" from split "<< 2*j<<std::endl;
					split[2*j].remove(c);
				}
				std::cout << "CALL doSplit FROM soi" << std::endl;
				doSplit(c);
			}
			else {
				c->inCounter++;
				std::cout << "=== soi2 Insert " << (int)(c) << " into split " << 2*i << std::endl;
				split[2*i].insert(c->splitCube[i], c);
			}
		}
	}

	// Split in vers split out.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		int pos = NegateEven(camera[i>>1], i);
		while((c = split[2*i].popIfLessThan(pos))) {
			std::cout << "=== sio  Pop " << (int)(c) << " from split " << 2*i << std::endl;
			c->inCounter--;
			std::cout << "=== sio  Insert " << (int)(c) << " into split " << 2*i+1 << std::endl;
			split[2*i+1].insert(c->splitCube[i], c);
		}
	}
}

void Lod::doSplit(Chose* c) {
	std::cout << "doSplit " << (int)(c) << std::endl;
	// TODO
	c->split();
	std::vector<Chose*>::iterator it;
	for (it = c->children.begin(); it != c->children.end(); ++it) {
		(*it)->triangulation();
		(*it)->updateAABB();
		addSplitCube((*it));
	}
	std::cout << "END doSplit" << std::endl;
}

void Lod::addMergeCube(Chose* chose) {
	for(int i = 0; i < 5; i++) {
		std::cout << "+++ mer  Insert " << (int)(chose) << " into merge " << i << std::endl;
		merge[i].insert(NegateEven(chose->lod.mergeCube[i], i), chose);
	}
}

void Lod::addSplitCube(Chose* chose) {
	std::cout << "addSplitCube " << (int)chose << std::endl;
	chose->inCounter = 0;
	for(int i = 0; i < 6; i++) {
		if(NegateEven(chose->lod.splitCube[i] - camera[i>>1], i) >= 0) {
			chose->inCounter++;
			std::cout << "+++ spl1 Insert " << (int)(chose) << " into split " << 2*i << std::endl;
			split[2*i].insert(NegateEven(chose->lod.splitCube[i],i), chose);
		}
		else {
			std::cout << "+++ spl2 Insert " << (int)(chose) << " into split " << 2*i+1<<std::endl;
			split[2*i+1].insert(NegateOdd(chose->lod.splitCube[i],i), chose);
		}
	}
	// TODO : si chose->inCounter == 6, il faut le split immédiatement.
	if (chose->inCounter == 6) {
		for(int i = 0; i < 6; i++) {
			std::cout << "+++ spl3 Remove " << (int)(chose) << " from split " << 2*i << std::endl;
			split[2*i].remove(chose);
		}
		std::cout << "CALL doSplit FROM addSplitCube" << std::endl;
		doSplit(chose);
	}
}
