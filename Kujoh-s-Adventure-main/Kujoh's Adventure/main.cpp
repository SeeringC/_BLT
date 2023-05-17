#include <bits/stdc++.h>

#include "Handler.h"

using namespace std;

const string WINDOW_TITLE = "Kujoh's Adventure";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void close();


int main(int argv, char* args[])
{
    initSDL(gWindow,gRenderer);
    TTF_Init();

    /// do st here

    Handler handler;

    handler.start(gRenderer);

    int currentTime, lastTime = 0;

    while(handler.get_is_running())
    {
        currentTime = SDL_GetTicks();

        if(currentTime - lastTime >= 33)
        {
            handler.tick(gRenderer);
            handler.show(gRenderer);
            lastTime = currentTime;
        }

    }
    /// end st here

    close(); /// Game Finish Display
    return 0;
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if(window == NULL)
        logSDLError(std::cout, "SDL_CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL)
        logSDLError(std::cout, "SDL_CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << "Error: " << SDL_GetError() << std::endl;

    if(fatal)
    {
        SDL_Quit();
        exit(1); ///exit(1) reveals that the task of the program is not completed
    }
}

void close()
{

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}
