#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;


void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }

        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    // Create window and setup vsync
    SDL_Window* window = SDL_CreateWindow("Variable deltaTime Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    uint64_t ticks_last_frame = SDL_GetPerformanceCounter();
    int quitting = 0;

    // Initialize ball variables
    float ballX = SCREEN_WIDTH / 2.0;
    float ballY = SCREEN_HEIGHT / 2.0;
    float ballRadius = 20.0;
    float ballVelocityX = 100;
    float ballVelocityY = 100;

    // Get the display mode of the first screen
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    const int MAX_FPS = displayMode.refresh_rate;

    while (!quitting) {
        uint64_t ticks_now = SDL_GetPerformanceCounter();
        float deltaTime = (float)(ticks_now - ticks_last_frame) / SDL_GetPerformanceFrequency();
        ticks_last_frame = ticks_now;

        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quitting = 1;
            }
        }

        // Update game logic based on the deltaTime
        ballX += ballVelocityX * deltaTime;
        ballY += ballVelocityY * deltaTime;

        // Bounce if the ball hits the screen edge
        if (ballX - ballRadius < 0 || ballX + ballRadius > SCREEN_WIDTH) {
            ballVelocityX = -ballVelocityX;
        }

        if (ballY - ballRadius < 0 || ballY + ballRadius > SCREEN_HEIGHT) {
            ballVelocityY = -ballVelocityY;
        }

        // Render the game
        SDL_SetRenderDrawColor(renderer, 75, 86, 95, 255); // Set background color
        SDL_RenderClear(renderer);

        // Render ball
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        drawCircle(renderer, (int)ballX, (int)ballY, (int)ballRadius);

        SDL_RenderPresent(renderer);

        // Cap the frame rate to monitors refresh rate
        SDL_Delay(1000 / MAX_FPS);
    }

    // Clean and close game
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

