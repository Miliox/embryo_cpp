#include <cstdint>
#include <iostream>
#include <string_view>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <SDL.h>
#pragma GCC diagnostic pop

constexpr std::string_view kWinTitle{"Title"};
constexpr std::int32_t     kWinPosX{SDL_WINDOWPOS_CENTERED};
constexpr std::int32_t     kWinPosY{SDL_WINDOWPOS_CENTERED};
constexpr std::int32_t     kWinWidth{640};
constexpr std::int32_t     kWinHeight{480};
constexpr std::uint32_t    kWinFlags{SDL_WINDOW_RESIZABLE};

constexpr std::uint32_t kRendererFlags{SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};

int main(int argc, char** argv)
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    int error = SDL_Init(SDL_INIT_EVERYTHING);
    if (error != 0)
    {
        std::cerr << "Failed to SDL_Init: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    SDL_SetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, "1");

    SDL_Window* window{SDL_CreateWindow(kWinTitle.data(), kWinPosX, kWinPosY, kWinWidth, kWinHeight, kWinFlags)};
    if (window == nullptr)
    {
        std::cerr << "Failed to SDL_Window: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Renderer* renderer{SDL_CreateRenderer(window, -1, kRendererFlags)};
    if (renderer == nullptr)
    {
        std::cerr << "Failed to SDL_CreateRenderer " << SDL_GetError() << "\n";
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event{};
    bool running{true};
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT: running = false; break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000U / 60U);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
