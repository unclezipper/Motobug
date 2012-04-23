#ifndef _TERRAIN_H_
#define _TERRAIN_H_ 1

#include <vector>
#include "mathlib.h"

enum CornerType { 
	CORNER_UPLEFT,
	CORNER_DOWNLEFT,
	CORNER_UPRIGHT,
	CORNER_DOWNRIGHT
};

class Terrain {
	public:
		Terrain(int X, int Y, unsigned int W, unsigned int H);
		Terrain(point o, unsigned int W, unsigned int H);
		virtual ~Terrain();
		
		//Misc Functions
		virtual bool blit();
		
		//Geometry management functions
		Vector* add_vector(point v1, point v2);
		Vector* add_vector(point v1, point v2, int type);
		Vector* add_vector(unsigned, unsigned, unsigned, unsigned);
		Vector* add_vector(unsigned, unsigned, unsigned, unsigned, int);
		
		virtual void del_vector(unsigned int index);
		
		
		//point* add_vertex(unsigned int X, unsigned int Y);
		//virtual void del_vertex(unsigned int index);
		//virtual void mov_vertex(unsigned int index, unsigned int nx, unsigned int ny);

		virtual void resize(unsigned int nw, unsigned int nh);
		virtual void move(point n_o);
	
		//std::vector<point> vertices;
		std::vector<Vector> vectors;
		
	protected:
		point origin;
		unsigned int w, h;
};

class Rectangle: protected Terrain {
	public:
		Rectangle(int x, int y, unsigned int w, unsigned int h) :
		Terrain(x,y,w,h) {
		add_vector(x,y,x+w,y);
		add_vector(x+w,y,x+w,y+h);
		add_vector(x+w,y+h,x,y+h);
		add_vector(x,y+h,x,y);
		}
		
		Rectangle(point o, unsigned int w, unsigned int h) :
		Terrain(o,w,h) {
		add_vector(o.x,o.y,o.x+w,o.y);
		add_vector(o.x+w,o.y,o.x+w,o.y+h);
		add_vector(o.x+w,o.y+h,o.x,o.y+h);
		add_vector(o.x,o.y+h,o.x,o.y);
		};
		
		virtual ~Rectangle();
};

class Triangle: protected Terrain {
	public:		
		Triangle(int X, int Y, unsigned int W, unsigned int H, CornerType tritype) :
		Terrain(X,Y,W,H) {
		//code
		}
		Triangle(point o, unsigned int w, unsigned int h, CornerType tritype) :
		Terrain(o,w,h) {
		//code
		}
		
		virtual ~Triangle();
	private:
		CornerType type;
};
#endif
