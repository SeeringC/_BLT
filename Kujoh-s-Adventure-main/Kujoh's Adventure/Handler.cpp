#include "Handler.h"

Handler::Handler()
{
    isRunning = 1;
    pre_isRunning = isRunning;
    current_level = 1;
    current_character = 0;
    view = 0;
    level_end = 0;

    character_level = new int[numCharacter];

    for(int i=0; i<numCharacter; i++)
        character_level[i] = 0;

    char_growth = new int* [numCharacter];
    for(int i = 0; i < numCharacter; i++)
        char_growth[i] = new int [2];

    paused = false;

}

Handler::~Handler()
{

}

void Handler::start(SDL_Renderer* renderer)
{
    std::ifstream player_info("player_info.txt");
    player_info >> numCoin >> numGem;
    player_info >> lastLevel;

    for(int i=0; i<numCharacter; i++)
    {
        player_info >> character_level[i] >> char_growth[i][0] >> char_growth[i][1];
    }

    player_info.close();

    screen.loadTexture(renderer);

    /// loadCharacter

    for(int i=0; i<numCharacter; i++)
    {
        _character[i].loadCharacter(renderer, ("Character/" + int2str(i)).c_str(), i);
    }

    ///
}

void Handler::tick(SDL_Renderer* renderer)
{
    pre_isRunning = isRunning;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) /// X to quit the window
        {
            isRunning = 0;

            std::ofstream player_info("player_info.txt"); /// add st to save Player last Level

            player_info << numCoin << ' ' << numGem << '\n';
            player_info << lastLevel << '\n';

            for(int i=0; i<numCharacter; i++)
            {
                player_info << character_level[i] << ' ' << char_growth[i][0] << ' ' << char_growth[i][1] << '\n';;
            }

            player_info.close();
        }

        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {   /// if player click button
            int x,y;
            SDL_GetMouseState(&x, &y);

            screen.handleMouseInput(x, y, isRunning, current_level,
                                    current_character, character_level,
                                    numCoin, numGem, lastLevel, paused);

            bool click = true;

            if(pre_isRunning == 2 && isRunning == 3)
            {
                Map.Free();
                _character[current_character].setX(0);
                _character[current_character].setY(0);
                int newDmg = _character[current_character].getBaseDmg();
                if(character_level[current_character] > 0)
                {
                    newDmg += (character_level[current_character] - 1) * char_growth[current_character][0];
                }
                _character[current_character].setDmg(newDmg);

                int newHp = _character[current_character].getBaseHp();
                if(character_level[current_character] > 0)
                {
                    newHp += (character_level[current_character] - 1) * char_growth[current_character][1];
                }
                _character[current_character].setHp(newHp);
                _character[current_character].setHp(_character[current_character].getMaxHp());
                _character[current_character].setStatus(0);
                _character[current_character].setFrame(0);

                _character[current_character].setLevel(character_level[current_character]);

                startCorotine = 0;
                loadLevel(renderer, current_level);
            }
        }
        else if(event.type == SDL_KEYDOWN)
        {
            screen.handleKeyInput(event, paused, isRunning);
        }

        if(isRunning == 3)
        {
            _character[current_character].handleInput(event);
        }

    }

    SDL_RenderClear(renderer);

    if(isRunning == 1)
    {
        screen.startScreen(renderer);
    }
    else if(isRunning==2)
    {
        int baseHp = _character[current_character].getBaseHp();
        int baseDmg = _character[current_character].getBaseDmg();
        screen.levelSelection(renderer, current_level, current_character,
                           character_level, numCoin, numGem, lastLevel,
                           baseHp, baseDmg, char_growth);
    }
    else if(isRunning == 3)
    {
        if(paused)
            return;

        _character[current_character].update(Map);

        if(_character[current_character].getStatus() == 4 || _character[current_character].getStatus() == 5)
        {
            startCorotine++;
//            std::cout << startCorotine << '\n';
            if(startCorotine >= 100)
            {
                isRunning = 2;
                if(_character[current_character].getStatus() == 5 && lastLevel == current_level)
                {
                    numCoin += 100;
                    numGem += 40;
                    lastLevel++;
                }

                if(_character[current_character].getStatus() == 5)
                {
                    numCoin += 100;
                    numGem += 40;
                }
                _character[current_character].setStatus(0);
            }

        }
    }
}

void Handler::show(SDL_Renderer* renderer)
{
    if(isRunning == 3)
    {
        if(_character[current_character].getX() >= SCREEN_WIDTH / 2)
            view = _character[current_character].getX() - SCREEN_WIDTH / 2;
        else view = 0;

        /// Drawing map
        Map.render(renderer, view, 0, current_character == numLevel);


        ///Update Player Velocity
        _character[current_character].setVelX(MAX_RUN_SPEED);

        /// Show Character info

        level_end = 0;

        if(_character[current_character].getStatus() == 4) level_end = 1;
        else if(_character[current_character].getStatus() == 5) level_end = 2;

        screen.ingame(renderer, _character[current_character].getHp(),
                      _character[current_character].getDmg(),
                      numCoin, numGem, paused, level_end );

        /// Show Character
        _character[current_character].show(renderer, view);

    }
    SDL_RenderPresent(renderer);
}

void Handler::loadLevel(SDL_Renderer* renderer, int level)
{
    if(Map.loadMap("img", renderer, level) == false)
    {
        std::cout << "Cannot load Map!" << '\n';
        exit(1);
        return;
    }
}
