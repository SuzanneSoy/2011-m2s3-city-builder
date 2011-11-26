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
	// * tile.errorVolume ≤ somme(tile.children.errorVolume)
	// * tile.nbTriangles < somme(tile.children.nbTriangles)

	// Pour calculer le gain d'une Chose :
	// Lorsqu'on utilise une Chose c, on la split d'abbord (on n'utilisera pas les fils tout de suite, donc pas de récursion),
	//   Calculer c.errorVolume dans le constructeur (idem pour chaque fils donc).
	//   // Calcul d'une approximation de la surface d'erreur, en considérant que l'objet est plaqué sur un plan perpendiculaire au sol.
	//   gainVolumeErreurParTriangle = (c.errorVolume / c.nbTriangles) - sum(x in c.children : x.errorVolume / x.nbTriangles)
	//   c.gainSurfaceErreurParTriangle = pow(volumeErreurParTriangle, 2.f/3.f);
	// Pour calculer son gain :
	// int gainParTriangle(distance)
	//   // Calcul de la surface de la projection de la surface d'erreur sur l'écran :
	//   return c.gainSurfaceErreurParTriangle * (frontFrustumDist * frontFrustumDist) / (dist * dist)
	
	// Pour trouver le split() qui rapportera le plus :
	// Set<Chose*> ensemble = { racine }
	//   Calculer le gain min et max des fils de toutes les Chose d'ensemble.
	//   Chose* best = la Chose avec le plus grand gain max
	//   if (best est une feuille) return best;
	//   ensemble = { c | c.max ≥ best.min }

	// Pour optimiser les Chose :
	// while (42) {
	//   Trouver la Chose dont le split() rapportera le plus
	//   if (GPUTriangles::current + nbNewTriangles > GPUTriangles::aim) {
	//     Trouver les choses avec le merge() qui coûtera le moins,
	//     En ayant suffisemment de triangles pour que
	//     (GPUTriangles::current + nbNewTriangles - nbDeleteTriangles <= GPUTriangles::aim)
	//     Faire autant de split() (qui rapportent le plus) que possible sans dépasser le nombre de triangles autorisés
	//     => De cette manière, si on a dû faire un gros merge() qui coûte cher, il sera peut-être compensé par plein de petits split().
	//     if (somme des coûts >= gain) {
	//       break; // while (42)
	//     }
	//   }
	//   Supprimer les triangles du tableau, en les insérant dans une freelist
	//   Ajouter les triangles en consommant de la freelist
	// }
	// Consommer la freeList en créant des triangles "bidon" (les trois sommets en (0,0,0) par ex.)
	return 0;
}
