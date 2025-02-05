#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
  puts("Available video drivers:");
  int numVideoDrivers = SDL_GetNumVideoDrivers();
  for (int i = 0; i < numVideoDrivers; i++) {
    puts(SDL_GetVideoDriver(i));
  }

  puts("Available audio drivers:");
  int numAudioDrivers = SDL_GetNumAudioDrivers();
  for (int i = 0; i < numAudioDrivers; i++) {
    puts(SDL_GetAudioDriver(i));
  }

  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  printf("Currently using audio driver %s\n", SDL_GetCurrentAudioDriver());
  printf("Currently using video driver %s\n", SDL_GetCurrentVideoDriver());
  return 0;
}
