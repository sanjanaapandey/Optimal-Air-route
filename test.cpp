#include <SDL2/SDL.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Simple SDL2", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_Delay(3000); // Wait for 3 seconds

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

