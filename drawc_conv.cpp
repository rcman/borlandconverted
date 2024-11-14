#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TOTALSHAPE 10
#define TOTALANIMS 10
#define TOTALOBJECTS 20

struct savebg {
    int bgflag;
    Uint32 backgnd[256];
} savedarea[TOTALOBJECTS];

struct fshape {
    int w, h;
    int n, c;
    int flag;
    int rowflag;
    Uint32 shp[260];
};

struct animshape {
    int active;
    int animwidth;
    int animheight;
    int animox;
    int animoy;
    int animx;
    int animy;
    int prox;
    int animspeed;
    int currentshape;
    int oldshape;
    int max;
    int row;
    struct fshape* fshp[TOTALSHAPE];
} animobjects[TOTALANIMS];

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int Init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    gWindow = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

void DrawGrid() {
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    for (int i = 0; i < SCREEN_WIDTH; i += 40) {
        SDL_RenderDrawLine(gRenderer, i, 0, i, SCREEN_HEIGHT);
    }
    for (int j = 0; j < SCREEN_HEIGHT; j += 40) {
        SDL_RenderDrawLine(gRenderer, 0, j, SCREEN_WIDTH, j);
    }
    SDL_RenderPresent(gRenderer);
}

void BoxImage(int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
    SDL_Rect box = {x, y, w, h};
    SDL_RenderFillRect(gRenderer, &box);
    SDL_RenderPresent(gRenderer);
}

void Init_Screen() {
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);
}

void cleanup() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!Init_SDL()) {
        printf("Failed to initialize!\n");
        return -1;
    }

    Init_Screen();
    DrawGrid();

    SDL_Color boxColor = {255, 0, 0, 255};
    BoxImage(100, 100, 50, 50, boxColor);

    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    cleanup();
    return 0;
}
