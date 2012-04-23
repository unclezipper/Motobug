#include <SDL/SDL.h>

//This is the base class of all objects in the engine
//represented on-screen by a sprite.

class Object {
	public:
		//Up for debate: should this remain an int pair or should
		//it be converted to a mathlib.h->point?
		int x, y;
		SDL_Surface* image;
		
		/* An x and y offset(namely, the camera's x and y) need to be
		fed to object.blit();	*/
		Object(int x, int y);
		virtual ~Object();
		virtual void blit(SDL_Surface* screen, int x_offset, int y_offset);
		virtual void update();
};

Object::Object(int x, int y) {
this->x = x;
this->y = y;
image = NULL;
}

Object::~Object(){
}

void Object::blit(SDL_Surface* screen, int x_offset, int y_offset){
	if (image == NULL) { return; }
	SDL_Rect z;
	z.x = this->x - x_offset;
	z.y = this->y - y_offset;
	SDL_BlitSurface(this->image, NULL, screen, &z);
}

void Object::update() {
return;
}