#include "all_includes.hh"

// TODO : Lorsque le GPU est suffisemment puissant pour qu'on puisse envoyer plus de maxSize triangles,
//        Tout supprimer et repartir avec un GPUTriangles vide, avec i, maxSize plus grand.
GPUTriangles::GPUTriangles(int maxSize) : current(0), aim(std::min(100, maxSize)), maxSize(maxSize) {
	triangles = static_cast<Triangle*>(operator new[](maxSize * sizeof(Triangle)));
	
	nToAdd = 0;
	nTrianglesToAdd = 0;
	cToAdd = new Chose*[maxSize];
	
	nToRemove = 0;
	nTrianglesToRemove = 0;
	cToRemove = new Chose*[maxSize];
}

void GPUTriangles::add(Chose* c) {
	cToAdd[nToAdd++] = c;
	nTrianglesToAdd += c->triangles.size();
}

void GPUTriangles::remove(Chose* c) {
	cToRemove[nToRemove++] = c;
	nTrianglesToRemove += c->triangles.size();
}

bool GPUTriangles::canAdd(Chose* c) {
	return (current + nTrianglesToAdd + ((int)c->triangles.size()) - nTrianglesToRemove <= aim);
}

bool GPUTriangles::canCommit() {
	return (current + nTrianglesToAdd - nTrianglesToRemove <= aim);
}

void GPUTriangles::commit() {
	// Supprimer les triangles du tableau, en les insérant dans une freelist
	// Trier la freelist pour insérer les nouveaux triangles au début.
	// Ajouter les triangles en consommant de la freelist
	// Compacter la fin du tableau.
	nToAdd = 0;
	nTrianglesToAdd = 0;
	nToRemove = 0;
	nTrianglesToRemove = 0;
}
