#include "all_includes.hh"

int random_seed() {
	static bool initialized = false;
	if (!initialized) {
		initialized = true;
		srand(time(NULL));
	}
	return rand();
}

// Ce hash donne des bons résultats sur tous les bits de l'entier
// généré (pas d'artefacts, répartition homogène des 0 et des 1).
unsigned int hash2(unsigned int a, unsigned int b) {
	unsigned int h = 1;
	int i;
	for (i = 0; i < 32; i+=8) {
		a = a*h + 1;
		b = b*h + 1;
		// marche aussi avec 65521.
		h = (h << 6) + (h << 16) - h + ((a >> i) & 0xff); // h * 65599 + ieme octet de a
		h = (h << 6) + (h << 16) - h + ((b >> i) & 0xff); // h * 65599 + ieme octet de b
	}
	return h;
}

float floatInRange(int seed, int n, float a, float b) {
	// 24 bits de précision, ça devrait suffire pour la plupart des utilisations.
	return (float)(hash2(seed, n) & 0xffffff) / (float)(0x1000000) * (b-a) + a;
}

bool proba(int seed, int n, float proba) {
	return floatInRange(seed, n, 0, 1) < proba;
}

unsigned int float2uint(float f) {
	// TODO : il y a plein de problèmes avec cette conversion :
	// 1) Il y a plusieurs représentations possibles pour le même float,
	//    donc si on re-split un objet 10 minutes après et qu'on n'a pas
	//    la même représentation, on n'aura pas la même entropie pour les hash.
	// 2) On ne peut pas faire juste fi.f = f; return fi.ui; car si
	//    sizeof(int) > sizeof(float), on lira des saletés.
	// 3) De toute façon, tout ça est principalement du "undefined behaviour".
	FloatUIntUnion fi;
	for (unsigned int i = 0; i < sizeof(fi); i++) {
		// effacer la structure.
		reinterpret_cast<char*>(&fi)[i] = 0;
	}
	fi.f = f;
	return fi.ui;
}
