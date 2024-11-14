void DrawScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set background color
    SDL_RenderClear(renderer);

    for (int row = 0; row < 12; row++) {
        for (int col = 0; col < 20; col++) {
            SDL_Rect tileRect = { col * 16, row * 16, 16, 16 };
            int tileType = screens[row][col];

            switch (tileType) {
                case 0:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black for empty
                    SDL_RenderFillRect(renderer, &tileRect);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Example color
                    SDL_RenderFillRect(renderer, &tileRect);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Example color
                    SDL_RenderFillRect(renderer, &tileRect);
                    break;
                // Add more cases for additional sprites or images
            }
        }
    }
    SDL_RenderPresent(renderer);
}
