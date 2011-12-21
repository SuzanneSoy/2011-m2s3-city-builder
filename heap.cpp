Heap::Heap()
	: buckets(new HeapNode*[1]), lastAllocatedBucket(-1),
	  bucketArraySize(1), lastNode(-1) {
}

void Heap::setId(int id) { this->id = id; }

void Heap::insert(int key, Chose* value) {
	// std::cout << "INSERT " << (int)(value) << " into " << id << std::endl;
	int _d_node = value->lod.heaps[id];
	if (_d_node <= lastNode && _d_node >= 0 &&
		buckets[getBucket(_d_node)][getIndex(_d_node)].value == value) {
		std::cout << "ERROR ! Trying to insert " << (int)(value)
				  << " but it is already here "
				  << (int)(buckets[getBucket(_d_node)][getIndex(_d_node)].value)
				  << std::endl;
	}
	// std::cout << "ENTER insert" << std::endl;
	++lastNode;
	if (getBucket(lastNode) > lastAllocatedBucket) {
		allocateBucket();
	}
	buckets[getBucket(lastNode)][getIndex(lastNode)].key = key;
	buckets[getBucket(lastNode)][getIndex(lastNode)].value = value;
	siftUp(lastNode);
	// std::cout << "EXIT insert" << std::endl;
}

void handler();
int global = 0;
void Heap::remove(Chose* value) {
	// std::cout << "ENTER remove id=" << id << " " << (int)(value) << " " << value->lod.heaps[id] << "/" << lastNode << std::endl;
	int node = value->lod.heaps[id];
	if (buckets[getBucket(node)][getIndex(node)].value != value) {
		std::cout << "ERROR ! Trying to remove " << (int)(value)
				  << " but found " << (int)(buckets[getBucket(node)][getIndex(node)].value)
				  << std::endl;
	}

	if (node == lastNode) { // On a supprimé le dernier noeud.
		--lastNode;
		// + 1 pour garder au moins un bucket "en cache".
		if (getBucket(lastNode) + 1 < lastAllocatedBucket)
			freeBucket();
		std::cout << "Remove exit A";
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
	std::cout << "Remove exit B";
}

Chose* Heap::popIfLessThan(int key) {
	std::cout << "Enter Pop " << id << " lastNode=" << lastNode;
	for (int i = 0; i <= lastNode; i++)
		std::cout << " "
				  << (int)(buckets[getBucket(i)][getIndex(i)].key) << "_"
				  << (int)(buckets[getBucket(i)][getIndex(i)].value);
	std::cout << std::endl;
	if (lastNode >= 0 && buckets[0][0].key < key) {
		Chose* ret = buckets[0][0].value;
		std::cout << "Pop " << ret->lod.heaps[id] << std::endl;
		remove(ret);
		std::cout << "Exit A Pop " << id << " lastNode=" << lastNode << " return=" << (int)(ret);
		for (int i = 0; i <= lastNode; i++)
			std::cout << " "
					  << (int)(buckets[getBucket(i)][getIndex(i)].key) << "_"
					  << (int)(buckets[getBucket(i)][getIndex(i)].value);
		std::cout << std::endl;
		return ret;
	}
	std::cout << "Exit B Pop " << id << " lastNode=" << lastNode << std::endl;
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
		// std::cout << "SET " << (int)(n->value) << " id=" << id << " to " << node << std::endl;
		node = p;
	}
	// après les break; qui sortent de la boucle, on a déjà actualisé
	// le pointeur `n` vers buckets[getBucket(node)][getIndex(node)].
	n->value->lod.heaps[id] = node;
	// std::cout << "SET " << (int)(n->value) << " id=" << id << " to " << node << std::endl;
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
		// std::cout << "SET " << (int)(n->value) << " id=" << id << " to " << node << std::endl;
		node = (exchRight ? rc : lc);
	}
	// après les break; qui sortent de la boucle, on a déjà actualisé
	// le pointeur `n` vers buckets[getBucket(node)][getIndex(node)].
	n->value->lod.heaps[id] = node;
	// std::cout << "SET " << (int)(n->value) << " id=" << id << " to " << node << std::endl;
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
