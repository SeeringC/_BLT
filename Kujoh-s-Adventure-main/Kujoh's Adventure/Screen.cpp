#include "Screen.h"

Screen::Screen()
{
    level_background = NULL;
    character_texture = NULL;
    gem = NULL;
    coin = NULL;
    for(int i=0; i<numCharacter; i++)
        portrait[i] = NULL;
    lock = NULL;
    star = NULL;
    nostar = NULL;
    statArrow = NULL;

    font = textFont = textFontBig = textFontSmall = NULL;

    curAlpha = 0;
    change_level = true;
    change_character = true;
    arrow_flag = true;
    selected_flag = true;
    flag = false;

    for(int i = 0; i < 3; i++)
        itemCount[i] = 0;

    frame = 0;
    ptSize = 150;
    cost = new long long[numCharacter];
    for(int i = 0; i < numCharacter; i++)
        cost[i] = 20;
    prev = 0;
}

Screen::~Screen()
{
    SDL_DestroyTexture(level_background);
    SDL_DestroyTexture(character_texture);
    SDL_DestroyTexture(gem);
    SDL_DestroyTexture(coin);
    for(int i = 0; i < numCharacter; i++)
        SDL_DestroyTexture(portrait[i]);
}

void Screen::loadTexture(SDL_Renderer* renderer)
{
    /// background, adding GameObject.render and SDL_RenderPresent to check
    background.loadImage("img/background.png", renderer);
    start_screen_title0.loadImage("img/Kujoh's.png", renderer);
    start_screen_title1.loadImage("img/adventure1.png", renderer);
    start_button[0].loadImage("img/start_0.png", renderer);
    start_button[1].loadImage("img/start_1.png", renderer);
    exit_button[0].loadImage("img/exit_0.png", renderer);
    exit_button[1].loadImage("img/exit_1.png", renderer);
    hpIcon.loadImage("img/hpIcon.png", renderer);
    dmgIcon.loadImage("img/dmgIcon.png", renderer);
    statsRect.loadImage("img/statsRect.png", renderer);
    option_box.loadImage("img/optionbox.png", renderer);
    bar.loadImage("img/bar.png", renderer);
    arrow[0].loadImage("img/arrow0.png", renderer);
    arrow[1].loadImage("img/arrow1.png", renderer);
    play_button.loadImage("img/play_button.png", renderer);
    itemBox.loadImage("img/itembox.png", renderer);
    charBox.loadImage("img/charBox.png", renderer);
    infoBox.loadImage("img/infoBox.png", renderer);
    costBox.loadImage("img/costBox.png", renderer);
    selected.loadImage("img/selected.png", renderer);
    paused_box.loadImage("img/paused.png", renderer);
    paused_return.loadImage("img/main_menu.png", renderer);
    paused_continue.loadImage("img/continue.png", renderer);
    win.loadImage("img/win.png", renderer);
    lose.loadImage("img/lose.png", renderer);

    hpIconStat = hpIcon;
    dmgIconStat = dmgIcon;

    start_screen_title0.setX(120);
    start_screen_title0.setY(-200);
    start_screen_title0.setVelY(13);

    start_screen_title1.setX(15);
    start_screen_title1.setY(720);
    start_screen_title1.setVelY(-200);

    start_button[0].setX(460);
    start_button[0].setY(380);
    start_button[1].setX(450);
    start_button[1].setY(370);

    exit_button[0].setX(460);
    exit_button[0].setY(550);
    exit_button[1].setX(450);
    exit_button[1].setY(542);

    hpIcon.setX(15 + portraitSize);
    hpIcon.setY(20);

    dmgIcon.setX(15 + portraitSize);
    dmgIcon.setY(70);

    option_box.setX((SCREEN_WIDTH - option_box.getW()) / 2);
    option_box.setY(30);

    bar.setX(option_box.getX() + 5);
    bar.setY(35);

    rectBar[0] = bar.getRect();
    rectBar[1] = bar.getRect();
    rectBar[1].x += bar.getW() + 5;

    arrow[0].setX(SCREEN_WIDTH / 4 - arrow[0].getW() - 40);
    arrow[0].setY((SCREEN_HEIGHT - arrow[0].getH()) / 2);

    arrow_range = {arrow[0].getX(), arrow[0].getX() + 40};

    arrow[1].setX(3 * SCREEN_WIDTH / 4 + 40);
    arrow[1].setY((SCREEN_HEIGHT - arrow[1].getH()) / 2);

    play_button.setX((SCREEN_WIDTH - play_button.getW()) / 2);
    play_button.setY(3 * SCREEN_HEIGHT / 4 + 75);

    itemBox.setX(10);
    itemBox.setY(10);

    charBox.setX(10);
    charBox.setY(itemBox.getY() + 20 + 2 * itemBox.getH());

    infoBox.setX(20 + charBox.getW() + charBox.getX());
    infoBox.setY(charBox.getY());

    costBox.setX(infoBox.getX() + (infoBox.getW() - costBox.getW()) / 2);
    costBox.setY(infoBox.getY() + infoBox.getH() - costBox.getH() - 20);

    selected.setH(150);
    selected.setW(150);

    selected_range = {150, 170};

    paused_box.setX((SCREEN_WIDTH - paused_box.getW()) / 2);
    paused_box.setY((SCREEN_HEIGHT - paused_box.getH()) / 2);

    paused_return.setX(paused_box.getX() + (paused_box.getW() - paused_return.getW()) / 2);
    paused_return.setY(paused_box.getY() + paused_box.getH() - paused_return.getH() - 10);

    paused_continue.setX(paused_return.getX());
    paused_continue.setY(paused_return.getY() - paused_continue.getH() - 10);

    win.setX((SCREEN_WIDTH - win.getW()) / 2);
    win.setY((SCREEN_HEIGHT / 4));

    lose.setX((SCREEN_WIDTH - lose.getW()) / 2);
    lose.setY((SCREEN_HEIGHT / 4));

    hpIconStat.setX(infoBox.getX() + 20);
    hpIconStat.setY(costBox.getY() - 20 - dmgIconStat.getH()-40);

    dmgIconStat.setX(infoBox.getX() + 20);
    dmgIconStat.setY(costBox.getY() - 20 - dmgIconStat.getH());



//////// Screen Debug Renderer
//    start_screen_title0.render(renderer,0);
//    start_screen_title1.render(renderer,0);
//    start_button[0].render(renderer,0);
//    start_button[1].render(renderer,0);
//    start_screen_title1.render(renderer,0);
//    exit_button[0].render(renderer,0);
//    exit_button[1].render(renderer,0);
//    hpIcon.render(renderer,0);
//    dmgIcon.render(renderer,0);
//    option_box.render(renderer,0);
//    bar.render(renderer,0);
//    arrow[0].render(renderer,0);
//    arrow[1].render(renderer,0);
//    play_button.render(renderer,0);
//    itemBox.render(renderer,0);
//    charBox.render(renderer,0);
//    infoBox.render(renderer,0);
//    costBox.render(renderer,0);
//    selected.render(renderer,0);
//    paused_box.render(renderer,0);
//    paused_return.render(renderer,0);
//    paused_continue.render(renderer,0);
//    win.render(renderer,0);
//    lose.render(renderer,0);
//    dmgIconStat.render(renderer,0);
//    hpIconStat.render(renderer,0);

//    SDL_RenderPresent(renderer);
////////

    SDL_Surface* surface;

    for(int i=0; i<numCharacter; i++)
    {
        surface = IMG_Load(("Character/" + int2str(i) + "/portrait.png").c_str());
        portrait[i] = SDL_CreateTextureFromSurface(renderer, surface);
    }

    surface = IMG_Load("img/item0.png");
    coin = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("img/item1.png");
    gem = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("img/lock.png");
    lock = SDL_CreateTextureFromSurface(renderer, surface);

    surface    = IMG_Load("img/star.png");
    star = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("img/nostar.png");
    nostar = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load("img/statArrow.png");
    statArrow = SDL_CreateTextureFromSurface(renderer, surface);

    font = TTF_OpenFont("REVUE.ttf", 45);

    textFont = TTF_OpenFont("calibrib.ttf", 25);

    textFontBig = TTF_OpenFont("calibrib.ttf", 35);

    textFontSmall = TTF_OpenFont("calibrib.ttf", 20);

    SDL_FreeSurface(surface);

///Screen Debug Creating Texture
//    SDL_Rect rect;
//    rect.x = 0;
//    rect.y = 0;
//    rect.w = 10000;
//    rect.h = 10000;
//    SDL_RenderCopy(renderer, portrait[0], &rect, NULL);
//    SDL_RenderPresent(renderer);
////////

}

void Screen::startScreen(SDL_Renderer* renderer)
{
    background.render(renderer, 0);

    /// Moving Title
    if(start_screen_title0.getY() < 5)
    {
        start_screen_title0.setY(std::min(5, start_screen_title0.getY() +
                                     start_screen_title0.getVelY()));
    }

    if(start_screen_title1.getY() > 180 && start_screen_title0.getY() == 5)
    {
        start_screen_title1.setY(std::max(180, start_screen_title1.getY() +
                                     start_screen_title1.getVelY()));
    }

    start_screen_title0.render(renderer, 0);
    start_screen_title1.render(renderer, 0);
    /// end of Moving Title

    int x,y;

    SDL_GetMouseState(&x, &y);

    if(curAlpha == 255)
    {
        if(inRect(x, y, start_button[0].getRect()))
        {
            start_button[1].render(renderer, 0);
        }
        else
        {
            start_button[0].render(renderer, 0);
        }
    }

    if(curAlpha == 255)
    {
        if(inRect(x, y, exit_button[0].getRect()))
        {
            exit_button[1].render(renderer, 0);
        }
        else
        {
            exit_button[0].render(renderer, 0);
        }
    }

    if(curAlpha < 255 && start_screen_title1.getY() == 180)
        curAlpha += 17;

    SDL_RenderPresent(renderer);
}

void Screen::handleMouseInput(int x, int y, int &isRunning,
                              int &cur_level, int &cur_character,
                              int *character_level, int &numCoin,
                              int &numGem, int lastLevel, bool &paused)
{
    if(isRunning == 1)
    {
        if(curAlpha == 255)
        {
            if(inRect(x, y, exit_button[0].getRect()))
            {
                isRunning = 0;
            }
            if(inRect(x, y, start_button[0].getRect()))
            {
                isRunning = 2;
            }
        }
    }
    else if(isRunning == 2)
    {
        /// Making a bar changing
        if(flag && inRect(x, y, rectBar[0]))
            flag = 0;
        else if(!flag && inRect(x, y, rectBar[1]))
            flag = 1;

        if(flag == 0)
        {
            if(character_level[cur_character] == 0)
            {
                cur_character = prev;
                change_character = true;
            }

            if(inRect(x, y, arrow[0].getRect()) && cur_level > 1)
            {
                cur_level--;
                change_level = true;
            }
            else if(inRect(x, y, arrow[1].getRect()) && cur_level < numLevel)
            {
                cur_level++;
                change_level = true;
            }

            if(inRect(x, y, play_button.getRect()))
            {///Player hit the play button
                if(cur_level <= lastLevel)
                    isRunning = 3; /// -> StartPlaying
            }
        }
        else
        {///Character Selection
            int col = 5;
            int row = (numCharacter - 1) / 5;
            int dis = 20;
            ptSize = 150; /// portraitSize

            for(int i = 0; i <= row; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    int id = i * 5 + j;
                    if(id >= numCharacter) break;
                    SDL_Rect nRect = {0, 0, ptSize, ptSize};
                    nRect.x = charBox.getX() + dis + j * (dis + ptSize);
                    nRect.y = charBox.getY() + dis + i * (dis + ptSize);
                    if(inRect(x, y, nRect))
                    {
                        if(character_level[id]  > 0)
                            prev = id;
                        if(id != cur_character){
                            change_character = true;
                        }
                        cur_character = id;
                    }
                }
            }

            if(inRect(x, y, costBox.getRect()))
            {
                if(character_level[cur_character] == 0 && numGem >= cost[cur_character])
                {
                    numGem -= cost[cur_character];
                    character_level[cur_character]++;
                }
                else if(character_level[cur_character] > 0 && numCoin >= cost[cur_character])
                {
                    numCoin -= cost[cur_character];
                    character_level[cur_character]++;
                }
            }
        }
    }
    else if(isRunning == 3)
    {
        if(paused)
        {
            if(inRect(x,y, paused_continue.getRect()))
            {
                paused = false;
            }
            if(inRect(x,y, paused_return.getRect()))
            {
                paused = false;
                isRunning = 2;
            }
        }
    }
}

void Screen::handleKeyInput(SDL_Event event, bool &paused, int &isRunning)
{
    if(event.key.keysym.sym == SDLK_p)
    {
        paused = !paused;
        /// false -> true
        /// true -> false;
    }
    if(event.key.keysym.sym == SDLK_ESCAPE)
    {
        if(isRunning == 1)
            isRunning = 0;
        else if(isRunning == 2)
            isRunning = 1;
        else
            paused = !paused;
    }
}

void Screen::levelSelection(SDL_Renderer* renderer, int cur_level,
                        int cur_character, int* character_level,
                        int numCoin, int numGem, int lastLevel,
                        int baseHp, int baseDmg, int **char_growth)
{
    ///Dynamic Arrow
    if(arrow_flag == 0)
    {
        arrow[0].setX(arrow[0].getX() - 5);
        arrow[1].setX(arrow[1].getX() + 5);
    }
    else
    {
        arrow[0].setX(arrow[0].getX() + 5);
        arrow[1].setX(arrow[1].getX() - 5);
    }

    if(arrow[0].getX() == arrow_range.first)
        arrow_flag = 1;
    else if(arrow[0].getX() == arrow_range.second)
        arrow_flag = 0;

    /// left Bar of the Selector
    if(flag == 1 && bar.getX() < rectBar[1].x)
        bar.setX(std::min(bar.getX() + 75, rectBar[1].x));
    else if(flag == 0 && bar.getX() > rectBar[0].x)
        bar.setX(std::max(bar.getX() - 75, rectBar[0].x));

    background.render(renderer, 0);
    option_box.render(renderer, 0);
    bar.render(renderer, 0);


    ///Level Selection Bar
    std::string s = "Level Selection";
    SDL_Surface* sf_font = NULL;

    if(flag == 0)
    {
        sf_font = TTF_RenderText_Solid(textFont, s.c_str(), black);
    }
    else
    {
        sf_font = TTF_RenderText_Solid(textFont, s.c_str(), white);
    }

    int w = sf_font->w;
    int h = sf_font->h;
    SDL_Texture* nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);

    SDL_Rect nRect = {0, 0, w, h};
    nRect.x = rectBar[0].x + (rectBar[0].w - w) / 2;
    nRect.y = rectBar[0].y + (rectBar[0].h - h) / 2;
    SDL_RenderCopy(renderer, nTexture, NULL, &nRect);


    ///Characters Bar
    s = "Characters";

    if(flag == 1)
    {
        sf_font = TTF_RenderText_Solid(textFont, s.c_str(), black);
    }
    else
    {
        sf_font = TTF_RenderText_Solid(textFont, s.c_str(), white);
    }

    w = sf_font->w;
    h = sf_font->h;
    nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);

    nRect = {0, 0, w, h};
    nRect.x = rectBar[1].x + (rectBar[1].w - w) / 2;
    nRect.y = rectBar[1].y + (rectBar[1].h - h) / 2;
    SDL_RenderCopy(renderer, nTexture, NULL, &nRect);

    ///Gem and Coin box
    itemBox.render(renderer, 0);

    nRect = itemBox.getRect();
    nRect.y += itemBox.getH() + 5;
    SDL_RenderCopy(renderer, itemBox.getObject(), NULL, &nRect);

    nRect.x += 5;
    nRect.y += 5;
    nRect.w = nRect.h = 30;
    SDL_RenderCopy(renderer, gem, NULL, &nRect);

    nRect.y = itemBox.getY() + 5;
    SDL_RenderCopy(renderer, coin, NULL, &nRect);

    ///Coin text
    sf_font = TTF_RenderText_Solid(textFont, int2str(numCoin).c_str(), white);
    w = sf_font->w;
    h = sf_font->h;
    nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
    nRect.x = itemBox.getX() + itemBox.getW() - 10 - w;
    nRect.y = itemBox.getY() + 10;
    nRect.w = w, nRect.h = h;
    SDL_RenderCopy(renderer, nTexture, NULL, &nRect);

    ///Gem text
    sf_font = TTF_RenderText_Solid(textFont, int2str(numGem).c_str(), white);
    w = sf_font->w;
    h = sf_font->h;
    nTexture = SDL_CreateTextureFromSurface(renderer, sf_font);
    nRect.x = itemBox.getX() + itemBox.getW() - 10 - w;
    nRect.y = itemBox.getY() + 10 + itemBox.getH() + 5;
    nRect.w = w;
    nRect.h = h;
    SDL_RenderCopy(renderer, nTexture, NULL, &nRect);

    ///load Character
    if(change_character)
    { /// load Character in Character Selection
        description.clear();
        frame = 0;
        std::string path = "Character/" + int2str(cur_character);
        SDL_Surface* sf = IMG_Load((path + "/idle0.png").c_str());
        character_texture = SDL_CreateTextureFromSurface(renderer, sf);
        change_character = false;
        std::ifstream file((path + "/char_info.txt").c_str());
        file >> cw >> ch;
        file >> fr.first;
        file >> fr.first >> fr.second;
        file.close();

        std::ifstream file_description((path + "/description.txt").c_str());
        std::string s;
        while(std::getline(file_description, s))
            description.push_back(s);

        file_description.close();

        SDL_FreeSurface(sf);
    }

    SDL_Rect fRect = {0, 0, charSize, charSize};
    fRect.x = (frame % fr.first) * charSize;
    fRect.y = (frame / fr.first) * charSize;

    if(flag == 0)
    {
        if(change_level)
        {
            std::string path = "img/Level_" + int2str(cur_level) + "/background.png";
            SDL_Surface* sf = IMG_Load(path.c_str());
            level_background = SDL_CreateTextureFromSurface(renderer, sf);

            path = "img/Level_" + int2str(cur_level) + "/name.png";
            level_name.loadImage(path, renderer);
            level_name.setX(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2 - level_name.getW()) / 2);
            level_name.setY(SCREEN_HEIGHT / 4 + 10);

            SDL_FreeSurface(sf);
            change_level = false;
        }

        SDL_Rect nRect, tRect;

        nRect.x = SCREEN_WIDTH / 4;
        nRect.y = SCREEN_HEIGHT / 4;
        nRect.w = SCREEN_WIDTH / 2;
        nRect.h = SCREEN_HEIGHT / 2;

        tRect = nRect;
        tRect.x -= 4;
        tRect.y -= 4;
        tRect.w += 8;
        tRect.h += 8;

        SDL_SetRenderDrawColor(renderer, 120, 120, 0, 255);
        SDL_RenderFillRect(renderer, &tRect);

        SDL_RenderCopy(renderer, level_background, NULL, &nRect);

        nRect.x = nRect.x + nRect.w - 40;
        nRect.y = nRect.y + 10;
        nRect.w = nRect.h = 30;

        if(cur_level < lastLevel)
            SDL_RenderCopy(renderer, star, NULL, &nRect);
        else if(cur_level > lastLevel)
            SDL_RenderCopy(renderer, lock, NULL, &nRect);
        else SDL_RenderCopy(renderer, nostar, NULL, &nRect);

        if(cur_level > 1)
            arrow[0].render(renderer, 0);
        if(cur_level < numLevel)
            arrow[1].render(renderer, 0);

        if(cur_level <= lastLevel)
            play_button.render(renderer, 0);

        SDL_Rect cRect = {0, 0, charSize, charSize};
        cRect.x = (SCREEN_WIDTH - charSize) / 2 + (charSize / 3 - cw) / 2;
        cRect.y = (SCREEN_HEIGHT - charSize) / 2;
        SDL_RenderCopy(renderer, character_texture, &fRect, &cRect);
        frame++;
        while(frame >= fr.second)
            frame -= fr.second;
    }
    else
    {
        ///Selection animation
        if(selected_flag == 0)
        {
            selected.setW(selected.getW() - 4);
            selected.setH(selected.getH() - 4);
        }
        else
        {
            selected.setW(selected.getW() + 4);
            selected.setH(selected.getH() + 4);
        }
        if(selected.getW() == selected_range.first)
            selected_flag = 1;
        else if(selected.getW() == selected_range.second)
            selected_flag = 0;
        ///

        charBox.render(renderer, 0);
        infoBox.render(renderer, 0);
        costBox.render(renderer, 0);

        int col = 5;
        int row = (numCharacter - 1)/5;
        int dis = 20;

        ///Draw Character Selection Box

        for(int i=0; i<=row; i++)
        {
            for(int j=0; j<col; j++)
            {
                int id = i*5 + j;

                if(id>=numCharacter)
                    break;

                SDL_Rect nRect = {0, 0, ptSize, ptSize};
                nRect.x = charBox.getX() + dis + j*(dis + ptSize);
                nRect.y = charBox.getY() + dis + i*(dis + ptSize);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                if(id == cur_character)
                {
                    SDL_RenderFillRect(renderer, &nRect);
                }

                SDL_RenderDrawRect(renderer, &nRect);
                SDL_RenderCopy(renderer, portrait[id], NULL, &nRect);

                SDL_Rect nnRect = nRect;
                nnRect.x = nnRect.x + nnRect.w - 40;
                nnRect.y = nnRect.y + 10;
                nnRect.w = nnRect.h = 30;

                if(character_level[id] == 0)
                    SDL_RenderCopy(renderer, lock, NULL, &nnRect);

                if(id == cur_character)
                {
                    selected.setX(nRect.x - (selected.getW() - nRect.w) / 2);
                    selected.setY(nRect.y - (selected.getH() - nRect.h) / 2);
                }
            }
        }

        ///Draw Info of Character
        SDL_Rect cRect = {0, 0, charSize, charSize};
        cRect.x = infoBox.getX() + (infoBox.getW() - charSize) / 2 + (charSize / 3 - cw) / 2;
        cRect.y = infoBox.getY() - 80;
        SDL_RenderCopy(renderer, character_texture, &fRect, &cRect);


        SDL_Surface* surface;
        SDL_Texture* texture;

        ///Draw Stat

        hpIconStat.render(renderer, 0);
        dmgIconStat.render(renderer, 0);

        int newHp = baseHp, newDmg = baseDmg;

        if(character_level[cur_character] > 0)
        {
            newHp += (character_level[cur_character] - 1) * char_growth[cur_character][1];
            newDmg += (character_level[cur_character] - 1) * char_growth[cur_character][0];
        }

        SDL_Rect hpRect, dmgRect;
//
        surface = TTF_RenderText_Solid(textFont, int2str(newDmg).c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        dmgRect = {0, 0, surface->w, surface->h};
        dmgRect.x = dmgIconStat.getX() + dmgIconStat.getW() + 10;
        dmgRect.y = dmgIconStat.getY() + (dmgIconStat.getH() - surface->h)/2;
        SDL_RenderCopy(renderer, texture, NULL, &dmgRect);

        if(character_level[cur_character] > 0)
        {
            surface = TTF_RenderText_Solid(textFontBig, int2str(newDmg + char_growth[cur_character][0]).c_str(), green);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            dmgRect.w = surface->w;
            dmgRect.h = surface->h;
            dmgRect.x = 40 + infoBox.getX() + infoBox.getW() / 2;
            dmgRect.y -= 5;
            SDL_RenderCopy(renderer, texture, NULL, &dmgRect);
        }

        ///Hp
        /// Got BUG because newHp is NULL, remember to fix -> Fixed
        surface = TTF_RenderText_Solid(textFont, int2str(newHp).c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        hpRect = {0, 0, surface->w ,surface->h};
        hpRect.x = hpIconStat.getX() + hpIconStat.getW() + 10;
        hpRect.y = hpIconStat.getY() + (hpIconStat.getH() - surface->h) / 2;
        SDL_RenderCopy(renderer, texture, NULL, &hpRect);

        if(character_level[cur_character] > 0)
        {
            surface = TTF_RenderText_Solid(textFontBig, int2str(newHp + char_growth[cur_character][1]).c_str(), green);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            hpRect.w = surface->w;
            hpRect.h = surface->h;
            hpRect.x = 40 + infoBox.getX() + infoBox.getW() / 2;
            hpRect.y -= 5;
            SDL_RenderCopy(renderer, texture, NULL, &hpRect);
        }

        ///Draw Level
        surface = TTF_RenderText_Solid(textFont, ("Lv. " + int2str(character_level[cur_character])).c_str(), textColor);
        texture =  SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect lvRect = {0, 0, surface->w, surface->h};
        lvRect.x = hpIconStat.getX() + hpIconStat.getW() + 10;
        lvRect.y = hpIconStat.getY() - lvRect.h - 10;
        SDL_RenderCopy(renderer, texture, NULL, &lvRect);

        if(character_level[cur_character] > 0)
        {
            surface = TTF_RenderText_Solid(textFontBig, ("Lv. " + int2str(character_level[cur_character] + 1)).c_str(), green);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            lvRect.w = surface->w;
            lvRect.h = surface->h;
            lvRect.x = 40 + infoBox.getX() + infoBox.getW() / 2;
            lvRect.y -= 5;
            SDL_RenderCopy(renderer, texture, NULL, &lvRect);
        }

        if(character_level[cur_character] > 0)
        {
            SDL_Rect aRect = {0, 0, 25, 23};

            aRect.x = dmgIconStat.getX() + 130;
            aRect.y = dmgIconStat.getY() + (hpIconStat.getH() - aRect.h) / 2;
            SDL_RenderCopy(renderer, statArrow, NULL, &aRect);

            aRect.x = hpIconStat.getX() + 130;
            aRect.y = hpIconStat.getY() + (hpIconStat.getH() - aRect.h) / 2;
            SDL_RenderCopy(renderer, statArrow, NULL, &aRect);

            aRect.y -= 20 + aRect.h;
            SDL_RenderCopy(renderer, statArrow, NULL, &aRect);
        }

        ///Draw Description

        SDL_Rect dRect;
        dRect.x = infoBox.getX() + 10;
        dRect.y = infoBox.getY() + charSize - 130;

        for(int i = 0; i < description.size(); i++)
        {
            surface = TTF_RenderText_Solid(textFontSmall, description[i].c_str(), textColor);
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            dRect.w = surface->w;
            dRect.h = surface->h;

            SDL_RenderCopy(renderer, texture, NULL, &dRect);

            dRect.y += 25;
        }


        ///Draw Cost
        if(character_level[cur_character] > 0)
            cost[cur_character] = getCost(character_level[cur_character]);

        std::string temp = "Unlock";
        if(character_level[cur_character] > 0) temp = "Upgrade";

        surface = TTF_RenderText_Solid(textFont, temp.c_str(), black);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        lvRect = {0, 0, surface->w, surface->h};
        lvRect.x = costBox.getX() + 40;
        lvRect.y = costBox.getY() + (costBox.getH() - surface->h) / 2;
        SDL_RenderCopy(renderer, texture, NULL, &lvRect);

        lvRect.x += 30 + surface->w;
        lvRect.y = costBox.getY() + (costBox.getH() - 30) / 2;
        lvRect.w = lvRect.h = 30;
        if(character_level[cur_character] > 0)
            SDL_RenderCopy(renderer, coin, NULL, &lvRect);
        else
            SDL_RenderCopy(renderer, gem, NULL, &lvRect);


        /// Draw the money need to pay to the Character
        if(character_level[cur_character] > 0 && numCoin >= cost[cur_character])
        {///cannot use Coin to get Character :>
            surface = TTF_RenderText_Solid(textFont, int2str(cost[cur_character]).c_str(), black);
        }
        else if(character_level[cur_character] == 0 && numGem >= cost[cur_character])
        {
            surface = TTF_RenderText_Solid(textFont, int2str(cost[cur_character]).c_str(), black);
        }
        else
        {
            surface = TTF_RenderText_Solid(textFont, int2str(cost[cur_character]).c_str(), red);
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);

        lvRect.w = surface->w;
        lvRect.h = surface->h;
        lvRect.x += 40;
        lvRect.y = costBox.getY() + (costBox.getH() - surface->h) / 2;
        SDL_RenderCopy(renderer, texture, NULL, &lvRect);

        /// animation for selection
        frame++;
        while(frame >= fr.second) frame -= fr.second;
        selected.render(renderer, 0);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void Screen::ingame(SDL_Renderer* renderer, int char_hp,
                int char_dmg, int numCoin, int numGem,
                bool paused, int level_end)
{
    statsRect.render(renderer, 0);
    hpIcon.render(renderer, 0);
    dmgIcon.render(renderer, 0);

    /// Character HP
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, int2str(char_hp).c_str(), white);
    SDL_Texture* nTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect rect = {160, 15, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, nTexture, NULL, &rect);

    /// Character DMG
    textSurface = TTF_RenderText_Solid(font, int2str(char_dmg).c_str(), white);
    nTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    rect = {160, 65, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, nTexture, NULL, &rect);

    SDL_FreeSurface(textSurface);

    /// Gem and Coin of Char
    rect = itemBox.getRect();
    rect.x = SCREEN_WIDTH / 2;
    rect.y = 5;
    SDL_RenderCopy(renderer, itemBox.getObject(), NULL, &rect);

    rect.x += itemBox.getW() + 10;
    SDL_RenderCopy(renderer, itemBox.getObject(), NULL, &rect);

    rect.x += 5;
    rect.y += 5;
    rect.w = rect.h = 30;
    SDL_RenderCopy(renderer, gem, NULL, &rect);

    rect.x = SCREEN_WIDTH / 2 + 5;
    SDL_RenderCopy(renderer, coin, NULL, &rect);

    /// Text of Gem and Coin

    textSurface = TTF_RenderText_Solid(textFont, int2str(numGem).c_str(), white);
    int w = textSurface->w;
    int h = textSurface->h;
    nTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    rect.x = SCREEN_WIDTH / 2 + itemBox.getW() - 10 - w;
    rect.y = 15;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, nTexture, NULL, &rect);

    textSurface = TTF_RenderText_Solid(textFont, int2str(numCoin).c_str(), white);
    w = textSurface->w;
    h = textSurface->h;
    nTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    rect.x = SCREEN_WIDTH / 2 + 2 * itemBox.getW() - w;
    rect.y = 15;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(renderer, nTexture, NULL, &rect);

    if(paused)
    {
        paused_box.render(renderer, 0);
        paused_return.render(renderer, 0);
        paused_continue.render(renderer, 0);
    }

    if(level_end == 2)
        win.render(renderer, 0);
    else if(level_end == 1)
        lose.render(renderer, 0);
}
