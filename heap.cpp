Heap::Heap()
	: buckets(new HeapNode*[1]), lastAllocatedBucket(-1),
	  bucketArraySize(1), lastNode(-1) {
}

void Heap::init(int id, int factor) { this->id = id; this->factor = factor; }

void Heap::insert(float key, Chose* value) {
	// { // DEBUG
	// 	int _d_node = value->lod.heaps[id];
	// 	if (_d_node <= lastNode && _d_node >= 0 &&
	// 		buckets[getBucket(_d_node)][getIndex(_d_node)].value == value) {
	// 		std::cout << "ERROR ! Trying to insert " << value;
	// 		std::cout << " but it is already here." << std::endl;
	// 	}
	// }
	++lastNode;
	if (getBucket(lastNode) > lastAllocatedBucket) {
		allocateBucket();
	}
	buckets[getBucket(lastNode)][getIndex(lastNode)].key = key;
	buckets[getBucket(lastNode)][getIndex(lastNode)].value = value;
	siftUp(lastNode);
	for (int i = 0; i <= lastNode; i++) {
		std::cout << id << " ";
		std::cout << buckets[getBucket(lastNode)][getIndex(lastNode)].key << " ";
		std::cout << buckets[getBucket(lastNode)][getIndex(lastNode)].value;
		std::cout << typeid(*(buckets[getBucket(lastNode)][getIndex(lastNode)].value)).name();
		std::cout << std::endl;
	}
}

void Heap::remove(Chose* value) {
	int node = value->lod.heaps[id];

	// { // DEBUG
	// 	if (buckets[getBucket(node)][getIndex(node)].value != value) {
	// 		std::cout << "ERROR ! Trying to remove " << value;
	// 		std::cout << " but found " << buckets[getBucket(node)][getIndex(node)].value;
	// 		std::cout << std::endl;
	// 	}
	// }

	if (node == lastNode) { // On a supprimé le dernier noeud.
		--lastNode;
		// + 1 pour garder au moins un bucket "en cache".
		if (getBucket(lastNode) + 1 < lastAllocatedBucket)
			freeBucket();
		return;
	}
	
	buckets[getBucket(node)][getIndex(node)] = \
		buckets[getBucket(lastNode)][getIndex(lastNode)];
	
	--lastNode;
	
	// + 1 pour garder au moins un bucket "en cache".
	if (getBucket(lastNode) + 1 < lastAllocatedBucket) {
		freeBucket();
	}

	siftDown(node);
}

bool Heap::lessThan(float a, float b) {
	return (a * factor < b * factor);
}

Chose* Heap::popIfLessThan(float key) {
	if (lastNode >= 0 && buckets[0][0].key * factor < key * factor) {
		Chose* ret = buckets[0][0].value;
		remove(ret);
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
		if (n->key * factor <= np->key * factor)
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
		bool exchLeft = (lc <= lastNode) && (n->key * factor < nlc->key * factor);
		bool exchRight = (rc <= lastNode) && (n->key * factor < nrc->key * factor);
		exchRight = exchRight && (nlc->key * factor < nrc->key * factor);
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
