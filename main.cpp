#include "all_includes.hh"

// TODO : bâtiments.
// TODO : split route en 2 triangles.
// TODO : split bâtiment en faces, puis en triangles.
// TODO : probabilités des différents types de bâtiments.
// TODO : midpoint displacement sur les probabilités des différents types de bâtiments.
// TODO : largeur des routes : ???

int main() {
	// Générer une tile de base
	Vertex ne(100, 100, 0);
	Vertex sw(0, 0, 0);
	RectangleRoutes r(ne, sw);
	r.subdivide();
	// tile.subdivide tant qu'on n'a pas le niveau de détail désiré.
	
	// TODO : diviser l'errorVolume par nbTriangles, pour avoir le gain/perte par triangle.
	//        Cela devrait donner des choix plus justes pour les split/merge.

	// TODO : comment une tile peut-elle s'adapter à ses voisins (lors de la triangulation) ?
	// Solution bof : maintenir une liste des voisins sur chaque segment/face, et lorsqu'un nouveau voisin est créé,
	// mettre à jour la triangulation de notre tile.
	
	// Invariants :
	// * tile.errorVolume < somme(tile.children.errorVolume) // TODO : pour ordonner deux tiles égales, on prend en compte leur profondeur.
	// * tile.nbTriangles < somme(tile.children.nbTriangles)

	// Pour trouver le split() qui rapportera le plus :
	// findMaxSplit(Vertex camera) {
	//   std::set<Chose*> ensemble(); // TODO : mettre un comparateur qui trie les éléments selon leur gain max, en ordre décroissant.
	//   std::set<Chose*>::iterator it;
	//   ensemble.insert(this);
	//   for (it = ensemble.begin(); it != ensemble.end(); it++) {
	//     // TODO : Calculer le gain min et max des fils de toutes les Chose d'ensemble.
	//     // Pour cela, écrire et utiliser int Chose::gainMinScreenSurfacePerTriangle(Vertex camera)
	//     // et int Chose::gainMax… qui calculeront le gain en utilisant la distance
	//     // du point le plus proche et le plus éloigné de la chose et de ses children.
	//     gainScreenSurfacePerTriangle(camera);
	//   }
	//   Chose* best = ensemble.begin(); // la Chose avec le plus grand gain max
	//   if (best->isLeafNode) return best;
	//   
	//   ensemble = std::set<Chose*>(ensemble.begin(), ensemble.upper_bound(best->gainMin)); // { c | c.max ≥ best.min } // TODO : comparateur
	// }

	// Pour optimiser les Chose :
	// GPUTriangles* gpu = new GPUTriangles(10);
	// while(!gpu->canCommit()) {
	//   gpu->remove(findMinMerge());
	//   gpu->commit();
	// }
	// while (42) {
	//   gpu->add(findMaxSplit());
	//   while(!gpu->canCommit()) {
	//     gpu->remove(findMinMerge());
	//   }
	//   while ((s = findMaxSplit()) && gpu->canAdd(s)) {
	//     gpu->add(s);
	//   }
	//   if (gpu->isImprovement()) {
	//     gpu->commit();
	//   } else {
	//     break; // while (42)
	//   }
	// }
	return 0;
}
