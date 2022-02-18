#include "cart.hpp"
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

using rabbit::Cart;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

int runSDL() {
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
            switch (e.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                case SDL_MOUSEBUTTONDOWN:
                quit = true;
                default:
                ;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int main(int, char**) {
    ifstream romStream("../../carts/SuperMarioLand.gb", std::ios::binary | std::ios::ate);
    auto romEnd = romStream.tellg();
    romStream.seekg(0, std::ios::beg);
    auto romSize = romEnd - romStream.tellg();
    if (romSize == 0) {
        cout << "ROM file is empty" << endl;
        return 1;
    }
    vector<uint8_t> cartData(romSize);
    if (!romStream.read(reinterpret_cast<char*>(cartData.data()), romSize)) {
        cout << "Failed to read cart data" << endl;
        return 1;
    }
    Cart cart(cartData);
    cout << cart.cartInfo() << endl;

    return 0;
    //return runSDL();
}
