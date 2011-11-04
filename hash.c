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

unsigned int hash3(unsigned int seed, int x, int y) {
	return hash2(seed,hash2(x, y));
}
