#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "string.h"
#include "stdio.h"

SDL_Window* tmp_displayWindow;
SDL_Texture* fontTexture;

extern void ClearScreen();
extern void SwapWindow();
extern void InitGL();
extern void CloseGL();
extern void LoadTexture();
extern void Test();

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);	

	InitGL();

	LoadTexture();

	int quit = 0;
	SDL_Event e;
	Uint32 ts = 0;

	while (!quit)
	{
		Uint32 startTime = SDL_GetTicks();

		const Uint8* keys = SDL_GetKeyboardState(NULL);

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = 1;
				}
			}
		}

		// Clear screen
		ClearScreen();
		
		// Draw
		Test();

		SwapWindow();

		Uint32 endTime = SDL_GetTicks();
		ts = endTime - startTime;
	}

	CloseGL();

	SDL_DestroyWindow(tmp_displayWindow);
	SDL_Quit();

	return 0;
}
