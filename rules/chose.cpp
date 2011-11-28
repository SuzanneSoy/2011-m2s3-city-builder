#include "all_includes.hh"

Chose::Chose() : seed(initialSeed) {}

std::ostream& operator<<(std::ostream& os, const Chose* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Chose& r) {
	(void)r; // unused
	return os << "Chose";
}

void Chose::initChildren(int n) {
	children = std::vector<Chose*>(n);
}

void Chose::initTriangles(int n) {
	triangles = std::vector<Triangle*>(n);
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

void Chose::useTriangles() {
	// TODO
	// Ajouter t dans la liste des triangles à envoyer au GPU.
	
	
	// Maintenir une liste "add" et une liste "delete".
	// Quand on flush les triangles, s'il y a plus de delete que de add :
	// * trier la liste delete.
	// * Choisir l'extrémité (début ou fin) vers laquelle on va rappatrier les éléments de l'autre extrémité.
	// * Écraser les delete avec les add en partant du côté vers lequel on rappatrie.
	// * Copier des éléments de l'extrémité vers les cases libres.
	// * Enregistrer l'indice min et l'indice max.
	// Problème : Pas real-time : on ne peut pas arrêter le processus n'importe quand…
}

void Chose::addTriangle(Triangle* t) {
	triangles.push_back(t);
}

/* TODO : quand on se rend compte qu'on peut utiliser plus de
   triangles (le GPU suit sans problème au FPS voulu), allouer un
   autre tableau plus grand, vers lequel on déplacera les triangles
   petit à petit (pour rester real-time).

   Pour l'instant, on alloue simplement un tableau suffisemment grand.
 */

Triangle* Chose::resetGPUTriangles(int n) {
	Chose::GPUTriangles = static_cast<Triangle*>(operator new[](n * sizeof(Triangle)));
	return Chose::GPUTriangles;
}

int Chose::nGPUTriangles = 1000;
// http://stackoverflow.com/questions/4754763/c-object-array-initialization-without-default-constructor
Triangle* Chose::GPUTriangles = Chose::resetGPUTriangles(Chose::nGPUTriangles);
