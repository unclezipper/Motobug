#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <vector>
#include <SDL/sdl.h>
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
		vector<SDL_Surface> frames;
		int counter = 0;
		int curframe = NULL;
		int maxframe;
	public:
		Animation(vector<SDL_surface> f);
		virtual SDL_Surface update(int dly);
		virtual SDL_Surface play(int dly);
		SDL_Surface get_frame(unsigned int i);
		SDL_Surface get_firstframe();
		SDL_Surface get_lastframe();
		
		void reset() { counter = 0; curframe = NULL; };
		
}

Animation::Animation(vector<SDL_surface> f) {
	frames = f;
	maxframe = (frames.size() - 1);
}

Animation::update(int dly) {
	if (curframe == NULL) { counter = dly; curframe = 0;}
	if (counter <= 0) {
		counter = dly;
		if (curfame == maxframe) {
			curframe = 0;
			return frames[curframe];
		} else {
			curframe++;
			return frames[curframe];
		}
	} else {
		self.counter--;
		return frames[curframe];
	}
}

Animation::play(int dly) {
	if (curframe == NULL) { counter = dly; curframe = 0;}
	if (counter <= 0) {
		counter = dly;
		if (curfame == maxframe) {
			throw ANIMATION_STOP;
		} else {
			curframe++;
			return frames[curframe];
		}
	} else {
		self.counter--;
		return frames[curframe];
	}
}

Animation::get_frame(unsigned int i) {
	return frames[i];
}

Animation::get_firstframe() {
	return frames[0];
}

Animation::get_lastframe() {
	return frames[maxframe];
}

#endif
