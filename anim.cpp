#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTALSHAPE 100
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Struct for sprites
struct Sprite {
    int shipox, shipoy, shipx, shipy;
    int oldspr, curspr;
    int shipspeed;
    SDL_Rect rect;
};

// Shape structure
struct fshape {
    int w, h;
    SDL_Texture* texture;
} fshp[TOTALSHAPE];

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Sprite shipanim[40];
int numspr = 36;

// Function to initialize SDL
bool Init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("SDL2 Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

// Function to load shapes (textures)
void LoadShapes() {
    // Here you would load images into fshp[].texture for each shape
    // Assuming each shape is 16x16, replace with your own images
    for (int i = 0; i < TOTALSHAPE; i++) {
        fshp[i].w = 16;
        fshp[i].h = 16;
        fshp[i].texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, fshp[i].w, fshp[i].h);
        // Fill texture with dummy data, replace with real loading
        SDL_SetRenderTarget(renderer, fshp[i].texture);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    SDL_SetRenderTarget(renderer, NULL);
}

// Function to free resources
void FreeResources() {
    for (int i = 0; i < TOTALSHAPE; i++) {
        if (fshp[i].texture) {
            SDL_DestroyTexture(fshp[i].texture);
        }
    }
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// Initialize array of sprites
void InitArray() {
    srand((unsigned)time(NULL));
    for (int i = 0; i < numspr; i++) {
        shipanim[i].shipx = rand() % SCREEN_WIDTH;
        shipanim[i].shipy = rand() % SCREEN_HEIGHT;
        shipanim[i].curspr = rand() % TOTALSHAPE;
        shipanim[i].shipspeed = rand() % 5 + 1;
        shipanim[i].rect = {shipanim[i].shipx, shipanim[i].shipy, fshp[0].w, fshp[0].h};
    }
}

// Draw screen grid (sample)
void DrawScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw each sprite in its position
    for (int i = 0; i < numspr; i++) {
        Sprite& spr = shipanim[i];
        if (fshp[spr.curspr].texture) {
            SDL_RenderCopy(renderer, fshp[spr.curspr].texture, NULL, &spr.rect);
        }
    }

    SDL_RenderPresent(renderer);
}

// Function to animate sprites (move and wrap around screen)
void Animate() {
    for (int i = 0; i < numspr; i++) {
        Sprite& spr = shipanim[i];
        spr.shipx += spr.shipspeed;
        spr.shipy += spr.shipspeed;
        if (spr.shipx > SCREEN_WIDTH) spr.shipx = 0;
        if (spr.shipy > SCREEN_HEIGHT) spr.shipy = 0;
        spr.rect.x = spr.shipx;
        spr.rect.y = spr.shipy;
    }
}

int main(int argc, char* args[]) {
    if (!Init_SDL()) {
        printf("Failed to initialize!\n");
        return 1;
    }
    LoadShapes();
    InitArray();

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        Animate();
        DrawScreen();
        SDL_Delay(16); // Limit to ~60 FPS
    }

    FreeResources();
    return 0;
}
