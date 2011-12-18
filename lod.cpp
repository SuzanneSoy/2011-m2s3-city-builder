#include "all_includes.hh"

Abr::Abr() {
}

void Abr::insert(int key, Chose* value) {
	key = key;
	value = value;
	//map.insert(key,value);
}

void Abr::remove(int key, Chose* value) {
	std::multimap<int, Chose*>::iterator it;
	std::pair<std::multimap<int, Chose*>::iterator, std::multimap<int, Chose*>::iterator> ret;
	ret = map.equal_range(key);

    for (it=ret.first; it!=ret.second; ++it) {
		if ((*it).second == value) {
			map.erase(it);
			break;
		}
	}
}

Chose* Abr::popIfLessThan(int key) {
	std::multimap<int,Chose*>::iterator it = map.begin();

	if((*it).first < key) {
		map.erase(it);
		return (*it).second;
	} else {
		return NULL;
	}
}

#define NegateEven(v, i) ((v)*(((i)&1) ? 1 : -1))

Lod::Lod(){};

Lod::Lod(float camera[3]) {
	this->camera[0] = camera[0];
	this->camera[1] = camera[1];
	this->camera[2] = camera[2];
}

void Lod::setCamera(float camera[3]) {
	this->camera[0] = camera[0];
	this->camera[1] = camera[1];
	this->camera[2] = camera[2];

	// Merge.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		int pos = NegateEven(camera[i>>1], i);
		while((c = merge[i].popIfLessThan(pos))) {
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
		while((c = split[2*i+1].popIfLessThan(pos))) {
			if(c->inCounter == 5) {
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
		while((c = split[2*i].popIfLessThan(pos))) {
			c->inCounter--;
			split[2*i+1].insert(c->splitCube[i], c);
		}
	}
}

void Lod::addMergeCube(Chose* chose, int limits[6]) {
	for(int i = 0; i < 5; i++)
		merge[i].insert(NegateEven(limits[i], i), chose);
}

void Lod::addSplitCube(Chose* chose, int limits[6]) {
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

Heap::Heap(int id)
	: id(id), buckets(new HeapNode*[1]), lastAllocatedBucket(-1),
	  bucketArraySize(1), lastNode(-1) {
}

void Heap::insert(int key, Chose* value) {
	++lastNode;
	if (getBucket(lastNode) > lastAllocatedBucket) {
		allocateBucket();
	}
	buckets[getBucket(lastNode)][getIndex(lastNode)].key = key;
	buckets[getBucket(lastNode)][getIndex(lastNode)].value = value;
	siftUp(lastNode);
}

void Heap::remove(int node) {
	--lastNode;

	if (node > lastNode) { // On a supprimé le dernier noeud.
		// + 1 pour garder au moins un bucket "en cache".
		if (getBucket(lastNode) + 1 < lastAllocatedBucket)
			freeBucket();
		return;
	}
	
	buckets[getBucket(node)][getIndex(node)] = \
		buckets[getBucket(lastNode)][getIndex(lastNode)];
	
	// + 1 pour garder au moins un bucket "en cache".
	if (getBucket(lastNode) + 1 < lastAllocatedBucket) {
		freeBucket();
	}

	siftDown(node);
}

Chose* Heap::popIfLessThan(int key) {
	if (lastNode >= 0 && buckets[0][0].key < key) {
		Chose* ret = buckets[0][0].value;
		remove(0);
		return ret;
	}
	return NULL;
}

void Heap::siftUp(int node) {
	HeapNode* n;
	HeapNode* np;
	while (true) {
		n = &(buckets[getBucket(node)][getIndex(node)]);
		if (node <= 0)
			break;
		int p = parent(node);
		np = &(buckets[getBucket(p)][getIndex(p)]);
		if (n->key >= np->key)
			break;
		HeapNode temp = *n;
		*n = *np;
		*np = temp;
		// mettre à jour le champ lod.heaps[id] de l'ancien parent qu'on
		// vient de descendre.
		n->value->lod.heaps[id] = node;
		node = p;
	}
	// après les break; qui sortent de la boucle, on a déjà actualisé
	// le pointeur `n` vers buckets[getBucket(node)][getIndex(node)].
	n->value->lod.heaps[id] = node;
}

void Heap::siftDown(int node) {
	HeapNode* n;
	HeapNode* nlc;
	HeapNode* nrc;
	while (true) {
		n = &(buckets[getBucket(node)][getIndex(node)]);
		int lc = leftchild(node);
		int rc = rightchild(node);
		nlc = &(buckets[getBucket(lc)][getIndex(lc)]);
		nrc = &(buckets[getBucket(rc)][getIndex(rc)]);
		// exchLeft et exchRight peuvent être tout deux true. Dans ce
		// cas, c'est exchRight qui gagne.
		bool exchLeft = (lc <= lastNode) && (n->key > nlc->key);
		bool exchRight = (rc <= lastNode) && (n->key > nrc->key) && (nlc->key > nrc->key);
		if ((!exchLeft) && (!exchRight))
			break;
		HeapNode temp = *n;
		if (exchRight) {
			*n = *nrc;
			*nrc = temp;
		} else {
			*n = *nlc;
			*nlc = temp;
		}
		// mettre à jour le champ lod.heaps[id] de l'ancien fils qu'on
		// vient de remonter.
		n->value->lod.heaps[id] = node;
		node = (exchRight ? rc : lc);
	}
	// après les break; qui sortent de la boucle, on a déjà actualisé
	// le pointeur `n` vers buckets[getBucket(node)][getIndex(node)].
	n->value->lod.heaps[id] = node;
}

void Heap::allocateBucket() {
	++lastAllocatedBucket;
	if (lastAllocatedBucket >= bucketArraySize) {
		HeapNode** old = buckets;
		buckets = new HeapNode*[bucketArraySize*2];
		for (int i = 0; i < lastAllocatedBucket; i++)
			buckets[i] = old[i];
		delete[] old;
		bucketArraySize *= 2;
	}
	buckets[lastAllocatedBucket] = new HeapNode[bucketSize];
}

void Heap::freeBucket() {
	delete[] buckets[lastAllocatedBucket];
	--lastAllocatedBucket;
	if (lastAllocatedBucket * 4 < bucketArraySize && bucketArraySize > 1) {
		HeapNode** old = buckets;
		buckets = new HeapNode*[bucketArraySize/2];
		for (int i = 0; i <= lastAllocatedBucket; i++)
			buckets[i] = old[i];
		delete[] old;
		bucketArraySize /= 2;
	}
}
