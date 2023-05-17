#ifndef HANDLER_H_
#define HANDLER_H_

#include <bits/stdc++.h>
#include "BasicFunction.h"
#include "GameObject.h"
#include "Screen.h"
#include "GameMap.h"
#include "Character.h"

class Handler
{
public:
    Handler();
    ~Handler();

    void start(SDL_Renderer* renderer); /// Prepare
    void tick(SDL_Renderer* renderer);
    void show(SDL_Renderer* renderer); /// Update Render to Screen
    void loadLevel(SDL_Renderer* renderer, int level);

    int get_is_running() {return isRunning;}

protected:

    Character _character[numCharacter];

    int isRunning;
    int lastLevel;
    int current_level;
    int current_character;
    int numGem, numCoin;
    int pre_isRunning;
    int view;
    int level_end; ///  1 - lose; 2 - win
    int startCorotine = 0; /// WaitForSecond

    int* character_level;

    int **char_growth;

    bool paused;

    GameMap Map;

    SDL_Event event;
    Screen screen;
};

Uint32 getpixel(SDL_Surface *surface, int x, int y);

#endif
