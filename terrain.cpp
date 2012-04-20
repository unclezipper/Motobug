#include <SDL/SDL.h>
#include "terrain.h"

Terrain::Terrain(int X, int Y, unsigned int W, unsigned int H){
	origin.x = X;
	origin.y = Y;
	w = W;
	h = H;
}

Vector* Terrain::add_vector(unsigned int x, unsigned int y, unsigned int x2, unsigned int y2) {
Vector i(x, y, x2, y2);
vectors.push_back(i);
return &vectors.back();
}

Vector* Terrain::add_vector(unsigned int x, unsigned int y, unsigned int x2, unsigned int y2, int type) {
Vector i(x, y, x2, y2, type);
vectors.push_back(i);
return &vectors.back();
}

Vector* Terrain::add_vector(point v1, point v2) {
Vector i(v1.x, v1.y, v2.x, v2.y);
vectors.push_back(i);
return &vectors.back();
}

Vector* Terrain::add_vector(point v1, point v2, int type) {
Vector i(v1.x, v1.y, v2.x, v2.y, type);
vectors.push_back(i);
return &vectors.back();
}

void Terrain::del_vector(unsigned int index) {
vectors.erase(vectors.begin() + index);
}

void Terrain::move(point n_o) {
	origin = n_o;
}

void Terrain::resize(unsigned int nw, unsigned int nh) {
	w = nw;
	h = nh;
}