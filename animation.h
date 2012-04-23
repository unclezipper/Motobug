#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <vector>
#include <SDL/SDL.h>
#include "mbexcept.h"

// Bill: I will be adding more classes to this header.
// I plan to rewrite my palette swapper class from sonic-boom,
// as well as a new animation class that stores an array to be
// used for frame delays, instead of the current Animation's
// update(dly) method.

/* Usage:
	anim = Animation(list_of_SDL_Surface_objects[]);
	object.image = anim.update(5);
	object.blit;

Animation::Play runs the animation until the last frame, then
throws a StopAnimation exception. Usage:

	try {
		object.image = anim.update(5);
	}
	catch (StopAnimation){
		//Not sure if the assignment operation would carry
		//out even if an exception was thrown. Just to be
		//safe, I would do this:
		object.image = anim.get_frame(maxframe);
		//And this is probably the only sane reason to use
		//this function.
		object.kill();
	}
*/
	
class Animation {
	private:
		std::vector<SDL_Surface> frames;
		int counter;
		int curframe;
		int maxframe;
	public:
		Animation(std::vector<SDL_Surface>* f);
		virtual ~Animation();
		virtual SDL_Surface* update(int dly);
		virtual SDL_Surface* play(int dly);
		SDL_Surface* get_frame(unsigned int i);
		SDL_Surface* get_firstframe();
		SDL_Surface* get_lastframe();
		
		void reset() { counter = 0; curframe = -1; };
		
};

Animation::Animation(std::vector<SDL_Surface>* f) {
	counter = 0;
	curframe = -1;
	frames = *f;
	maxframe = (frames.size() - 1);
}

SDL_Surface* Animation::update(int dly) {
	if (curframe == -1) { counter = dly; curframe = 0;}
	if (counter <= 0) {
		counter = dly;
		if (curframe == maxframe) {
			curframe = 0;
			return &frames[curframe];
		} else {
			curframe++;
			return &frames[curframe];
		}
	} else {
		counter--;
		return &frames[curframe];
	}
}

SDL_Surface* Animation::play(int dly) {
	if (curframe == -1) { counter = dly; curframe = 0;}
	if (counter <= 0) {
		counter = dly;
		if (curframe == maxframe) {
			throw ANIMATION_STOP;
		} else {
			curframe++;
			return &frames[curframe];
		}
	} else {
		counter--;
		return &frames[curframe];
	}
}

SDL_Surface* Animation::get_frame(unsigned int i) {
	return &frames[i];
}

SDL_Surface* Animation::get_firstframe() {
	return &frames[0];
}

SDL_Surface* Animation::get_lastframe() {
	return &frames[maxframe + 1];
}

Animation::~Animation() { 
	for (int z = 0; z == (maxframe + 1); z++) {
		SDL_FreeSurface(&frames[z]);
	}
}

#endif
