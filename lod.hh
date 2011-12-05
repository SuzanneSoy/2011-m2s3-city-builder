#include "all_includes.hh"

class Abr {
	private :
	std::multimap<int, Chose*> map;
	
	public :
	Abr();
	void insert(int key, Chose* value);		//TODO Retourne un item*.
	void remove(int key, Chose* value);		//TODO Prend un item*.
	Chose* popIfLessThan(int key);
};


class Lod {
	private :
	Abr merge[6];
	Abr split[12];
	float camera[3];
	
	public :
	Lod(float[3] camera);
	void addMergeCube(Chose* chose, int[6] limits);
	void addSplitCube(Chose* chose, int[6] limits);
	void setCamera(float[3] camera);
};
