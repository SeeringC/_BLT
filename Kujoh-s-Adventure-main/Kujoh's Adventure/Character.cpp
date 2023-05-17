#include "Character.h"


Character::Character()
{
    for(int i=0; i<=1; i++)
    {
        idleAnim[i] = NULL;
        moveAnim[i] = NULL;
        jumpAnim[i] = NULL;
        attackAnim[i] = NULL;
        diedAnim[i] = NULL;
    }
    victoryAnim = NULL;
    portrait = NULL;

    _idle = std::make_pair(0,0);
    _move = std::make_pair(0,0);
    _jump = std::make_pair(0,0);
    _attack = std::make_pair(0,0);
    _die = std::make_pair(0,0);
    _victory = std::make_pair(0,0);

    leftPerformance = false;
    rightPerformance = false;
    finishAttack = true;
    isJumping = false;
    isFalling = true;

    frame = 0;
    status = nStatus = 0;
    facing = 0;

    framePerAttack = frameAttack = nextAttack = 0;
}

Character::~Character()
{
    for(int i=0; i<=1; i++)
    {
        SDL_DestroyTexture(idleAnim[i]);
        SDL_DestroyTexture(moveAnim[i]);
        SDL_DestroyTexture(jumpAnim[i]);
        SDL_DestroyTexture(attackAnim[i]);
        SDL_DestroyTexture(diedAnim[i]);
    }
    SDL_DestroyTexture(victoryAnim);
    SDL_DestroyTexture(portrait);

    _idle = std::make_pair(0,0);
    _move = std::make_pair(0,0);
    _jump = std::make_pair(0,0);
    _attack = std::make_pair(0,0);
    _die = std::make_pair(0,0);
    _victory = std::make_pair(0,0);
}

void Character::loadCharacter(SDL_Renderer* renderer, std::string path, int character_id)
{
    SDL_Surface* surface;

    for(int i=0; i<=1; i++) /// left and right Texture
    {
        surface = IMG_Load( (path + "/idle" + int2str(i) + ".png").c_str() );
        if(surface == NULL)
        {
            std::cout << 1 << '\n';
            exit(1);
        }
        idleAnim[i] = SDL_CreateTextureFromSurface(renderer, surface);

        surface = IMG_Load( (path + "/move" + int2str(i) + ".png").c_str() );
        if(surface == NULL)
        {
            std::cout << 2 << '\n';
            exit(1);
        }
        moveAnim[i] = SDL_CreateTextureFromSurface(renderer, surface);

        surface = IMG_Load( (path + "/attack" + int2str(i) + ".png").c_str() );
        if(surface == NULL)
        {
            std::cout << 3 << '\n';
            exit(1);
        }
        attackAnim[i] = SDL_CreateTextureFromSurface(renderer, surface);

        surface = IMG_Load( (path + "/jump" + int2str(i) + ".png").c_str() );
        if(surface == NULL)
        {
            std::cout << 4 << '\n';
            exit(1);
        }
        jumpAnim[i] = SDL_CreateTextureFromSurface(renderer, surface);

        surface = IMG_Load( (path + "/died" + int2str(i) + ".png").c_str() );
        if(surface == NULL)
        {
            std::cout << 5 << '\n';
            exit(1);
        }
        diedAnim[i] = SDL_CreateTextureFromSurface(renderer, surface);
    }

    surface = IMG_Load( (path + "/victory" + ".png").c_str() );
    if(surface == NULL)
    {
        std::cout << 5 << '\n';
        exit(1);
    }
    victoryAnim = SDL_CreateTextureFromSurface(renderer, surface);

    surface = IMG_Load( (path + "/portrait" + ".png").c_str() );
    if(surface == NULL)
    {
        std::cout << 6 << '\n';
        exit(1);
    }
    portrait = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    ///Check Character
//    SDL_Rect rect = {0,0, portraitSize, portraitSize};
//
//    SDL_RenderCopy(renderer, portrait, NULL, &rect);
//    SDL_RenderPresent(renderer);

    id = character_id;

    ///Reading frame of each animation

    std::ifstream file(path + "/char_info.txt");
    file >> rect.w >> rect.h; /// thua ke gameObject
    file >> type;
    file >> _idle.first >> _idle.second;
    file >> _move.first >> _move.second;
    file >> _attack.first >> _attack.second;
    file >> _die.first >> _die.second;
    file >> _victory.first >> _victory.second;
    file >> framePerAttack;
    file >> baseHp >> baseDmg;
    maxHp = baseHp;

    file.close();
}


/// Drawing Animation
void Character::drawIdle(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = {0, 0, charSize, charSize};

    SDL_Rect tRect = {rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing,
                      rect.y - charSize / 3 - (charSize / 3 - rect.h),
                      charSize,
                      charSize};

    if(nStatus != status)
        frame = 0;

    status = STATUS::IDLE;

    nRect.x = (frame % _idle.first) * charSize;
    nRect.y = (frame / _idle.first) * charSize;

    SDL_RenderCopy(renderer, idleAnim[facing], &nRect, &tRect);
    frame++;

    if(frame == _idle.second)
        frame -= _idle.second;
}

void Character::drawMove(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = {0, 0, charSize, charSize};

    SDL_Rect tRect = {rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing,
                      rect.y - charSize / 3 - (charSize / 3 - rect.h),
                      charSize,
                      charSize};

    if(nStatus != status)
        frame = 0;

    status = STATUS::MOVE;

    nRect.x = (frame % _move.first) * charSize;
    nRect.y = (frame / _move.first) * charSize;

    SDL_RenderCopy(renderer, moveAnim[facing], &nRect, &tRect);
    frame++;

    if(frame == _move.second)
        frame -= _move.second;
}

void Character::drawDied(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = {0, 0, charSize, charSize};

    SDL_Rect tRect = {rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing,
                      rect.y - charSize / 3 - (charSize / 3 - rect.h),
                      charSize,
                      charSize};

    if(nStatus != status)
        frame = 0;

    status = STATUS::DIED;

    nRect.x = (frame % _die.first) * charSize;
    nRect.y = (frame / _die.first) * charSize;

    SDL_RenderCopy(renderer, diedAnim[facing], &nRect, &tRect);
    frame++;

    if(frame == _die.second)
        frame --;
}

void Character::drawVictory(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = {0, 0, charSize, charSize};

    SDL_Rect tRect = {rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing,
                      rect.y - charSize / 3 - (charSize / 3 - rect.h),
                      charSize,
                      charSize};

    if(nStatus != status)
        frame = 0;

    status = STATUS::VICTORY;

    nRect.x = (frame % _victory.first) * charSize;
    nRect.y = (frame / _victory.first) * charSize;

    SDL_RenderCopy(renderer, victoryAnim, &nRect, &tRect);
    frame++;

    if(frame == _victory.second)
        frame -= _victory.second;
}

void Character::drawAttack(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = {0, 0, charSize, charSize};

    SDL_Rect tRect = {rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing,
                      rect.y - charSize / 3 - (charSize / 3 - rect.h),
                      charSize,
                      charSize};

    if(nStatus != status && finishAttack)
        frame = 0;

    if(frame == _attack.second - 1)
        finishAttack = true;

    status = STATUS::ATTACK;

    nRect.x = (frame % _attack.first) * charSize;
    nRect.y = (frame / _attack.first) * charSize;

    SDL_RenderCopy(renderer, attackAnim[facing], &nRect, &tRect);
    frame++;

    if(frame == _attack.second)
        frame -= _attack.second;
}

void Character::drawJump(SDL_Renderer* renderer, int view)
{
    SDL_Rect nRect = {0, 0, charSize, charSize};

    SDL_Rect tRect = {rect.x - charSize / 3 - view - (charSize / 3 - rect.w) * facing,
                      rect.y - charSize / 3 - (charSize / 3 - rect.h),
                      charSize,
                      charSize};

    if(nStatus != status)
        frame = 0;

    status = STATUS::JUMP;

    SDL_RenderCopy(renderer, jumpAnim[facing], NULL, &tRect);
}

/// end of animation code

void Character::show(SDL_Renderer* renderer, int view)
{
    SDL_Rect pRect = {10, 10, portraitSize, portraitSize};

    SDL_RenderCopy(renderer, portrait, NULL, &pRect); /// player info and status

    if(nStatus != status) frame = 0;

    if(nStatus == STATUS::DIED)
    {
        drawDied(renderer, view);
        return;
    }

    if(nStatus == STATUS::VICTORY)
    {
        drawVictory(renderer, view);
        return;
    }

    nextAttack ++;
    if(nStatus == STATUS::ATTACK)
    {
        drawAttack(renderer, view);
        return;
    }

    if(isJumping || isFalling)
    {
        drawJump(renderer, view);
        return;
    }

    if(nStatus == STATUS::IDLE)
    {
        drawIdle(renderer, view);
        return;
    }

    if(nStatus == STATUS::MOVE)
    {
        drawMove(renderer, view);
        return;
    }
}

void Character::handleInput(SDL_Event event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_a:
            pressed['a'] = 1;
            pressed['d'] = 0;
            break;

        case SDLK_d:
            pressed['a'] = 0;
            pressed['d'] = 1;
            break;

        case SDLK_SPACE:
            if(isFalling == false)
                pressed[' '] = 1;
            break;

        case SDLK_k:
            if(nextAttack >= framePerAttack)
                pressed['k'] = 1;
            break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_a:
            pressed['a'] = 0;
            break;

        case SDLK_d:
            pressed['d'] = 0;
            break;

        case SDLK_SPACE:
            pressed[' '] = 0;
            break;

        case SDLK_k:
            pressed['k'] = 0;
            break;
        }
    }
}

void Character::update(GameMap& Map)
{
    if(isJumping || isFalling)
    {
        velY += gravity;

        if(velY>MAX_FALL_SPEED)
            velY = MAX_FALL_SPEED;
    }

    rect.y += velY;

    if(rect.y < 0) rect.y = 0;

    if(rect.y + rect.h >= Map.getMapHeight() * TILE_SIZE - 2)
        rect.y = Map.getMapHeight() * TILE_SIZE - rect.h - 2;

    collisionY(Map);

    if(rect.y + rect.h >= Map.getMapHeight() * TILE_SIZE - 2 || hp == 0) /// checking out of map
    {
        nStatus = STATUS::DIED;
        return;
    }

    if(rect.x >= Map.getVictory() || nStatus == STATUS::VICTORY)
    {
        nStatus = STATUS::VICTORY;
        return;
    }

    if(!isFalling && !pressed['a'] && !pressed['d'] &&
       !pressed['k'])
    {
        nStatus = STATUS::IDLE;
    }

    if(isFalling == false && pressed[' '])
    {
        isJumping = isFalling = true;
        nStatus = STATUS::JUMP;
        velY -= 40;
    }
    else if(isFalling == true)
    {
        nStatus = STATUS::JUMP;
    }


    if(pressed['a'])
    {
        facing = 1;
        nStatus = STATUS::MOVE;
        rect.x -= velX;
    }
    else if(pressed['d'])
    {
        facing = 0;
        nStatus = STATUS::MOVE;
        rect.x += velX;
    }
    pressed[' '] = false;

    if(rect.x < 0)
        rect.x = 0;
    if(rect.x + rect.w > Map.getMapWidth() * TILE_SIZE)
        rect.x = Map.getMapWidth() * TILE_SIZE - rect.w;
    collisionX(Map);

    if(pressed['k'] && nextAttack >= framePerAttack)
    {
        nStatus = STATUS::ATTACK;
        finishAttack = false;
        nextAttack = 0; /// resetAttacktime
    }
    else if(!finishAttack)
    {
        nStatus = STATUS::ATTACK;
    }

}

void Character::collisionX(GameMap& Map)
{
    int pos_x1 = (rect.x - 1) / TILE_SIZE;
    int pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    int pos_y1 = rect.y / TILE_SIZE;
    int pos_y2 = (rect.y + rect.h) / TILE_SIZE;

    /// make sure player not jump through platform from the right

    for(int i = pos_y1; i <= pos_y2; i++)
    {
        if(Map.getInfo()[i][pos_x1])
        {
            rect.x = (pos_x1 + 1) * TILE_SIZE;
            break;
        }
    }

    pos_x1 = rect.x / TILE_SIZE;
    pos_x2 = (rect.x + rect.w + 1) / TILE_SIZE;
    pos_y1 = rect.y / TILE_SIZE;
    pos_y2 = (rect.y + rect.h) / TILE_SIZE;

    /// make sure player not jump through platform from the left

    for(int i = pos_y1; i <= pos_y2; i++)
    {
        if(Map.getInfo()[i][pos_x2])
        {
            rect.x = pos_x2 * TILE_SIZE - rect.w - 1;
            break;
        }
    }
}

void Character::collisionY(GameMap& Map)
{
    int pos_x1 = rect.x / TILE_SIZE;
    int pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    int pos_y1 = (rect.y - 1) / TILE_SIZE;
    int pos_y2 = (rect.y + rect.h) / TILE_SIZE;

    /// make sure player not jump through platform from below

    for(int i = pos_x1; i <= pos_x2; i++)
    {
        if(Map.getInfo()[pos_y1][i])
        {
            velY = 0;
            rect.y = (pos_y1 + 1) * TILE_SIZE;
            isJumping = false;
            isFalling = true;
            nStatus = STATUS::JUMP;
            break;
        }
    }

    pos_x1 = rect.x / TILE_SIZE;
    pos_x2 = (rect.x + rect.w) / TILE_SIZE;
    pos_y1 = rect.y / TILE_SIZE;
    pos_y2 = (rect.y + rect.h + 1) / TILE_SIZE;

    for(int i = pos_x1; i <= pos_x2; i++)
    {
        if(Map.getInfo()[pos_y2][i])
        {
            velY = 0;
            isJumping = isFalling = false;
            rect.y = pos_y2 * TILE_SIZE - rect.h - 1;
            return;
        }
    }
    isFalling = true; ///in case player not on ground
}
