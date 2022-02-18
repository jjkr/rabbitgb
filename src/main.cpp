#include <iostream>
#include <SDL.h>
#include "cart.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    auto *window = SDL_CreateWindow("rabbitgb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }
    auto *screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00));
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                quit = true;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Exiting\n";

    return 0;
}
