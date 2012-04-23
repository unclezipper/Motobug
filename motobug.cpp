#include <SDL/SDL.h>
#include <vector>
#include "animation.h"
#include "object.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

int main( int argc, char* args[] )
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }

    //Set up the screen
    SDL_Surface* screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return 1;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Motobug", NULL );

    //Load the images
    std::vector<SDL_Surface> images;
	images.push_back(*SDL_LoadBMP("sonicstand0.bmp"));
	images.push_back(*SDL_LoadBMP("sonicstand1.bmp"));
	images.push_back(*SDL_LoadBMP("sonicstand4.bmp"));
	images.push_back(*SDL_LoadBMP("sonicstand5.bmp"));
	images.push_back(*SDL_LoadBMP("sonicstand7.bmp"));
	
	Animation ani(&images);
	Object obj(60,90);
	obj.image = ani.get_firstframe();
	obj.blit(screen,0,0);
	SDL_Event event;

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit == true;
				SDL_Quit();
				return 0;
			}
		}
	obj.image = ani.update(90);
	obj.blit(screen,0,0);
	SDL_Flip(screen);
}

    //Quit SDL
    SDL_Quit();

    return 0;
}
