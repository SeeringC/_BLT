#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "BasicFunction.h"
#include "GameObject.h"
#include "GameMap.h"

class Character : public GameObject
{
public:

    Character();
    ~Character();

    void loadCharacter(SDL_Renderer* renderer, std::string path, int character_id);


    void drawIdle(SDL_Renderer* renderer, int view);
    void drawMove(SDL_Renderer* renderer, int view);
    void drawAttack(SDL_Renderer* renderer, int view);
    void drawDied(SDL_Renderer* renderer, int view);
    void drawVictory(SDL_Renderer* renderer, int view);
    void drawJump(SDL_Renderer* renderer, int view);

    void handleInput(SDL_Event event);
    void show(SDL_Renderer* renderer, int view);
    void update(GameMap& MAP);
    void collisionX(GameMap& MAP);
    void collisionY(GameMap& MAP); /// limit player move

    void setStatus(int _status) { nStatus = _status; }
    void setFrame(int _frame) { frame = _frame; }

    int getStatus() {return nStatus;}
protected:
    enum STATUS
    {
        IDLE = 0,
        MOVE,
        JUMP,
        ATTACK,
        DIED,
        VICTORY
    };

    SDL_Texture* idleAnim[2];
    SDL_Texture* moveAnim[2];
    SDL_Texture* jumpAnim[2];
    SDL_Texture* attackAnim[2];
    SDL_Texture* diedAnim[2];

    SDL_Texture* victoryAnim;
    SDL_Texture* portrait;

    //frame for each Animation
    std::pair<int,int> _idle;
    std::pair<int,int> _move;
    std::pair<int,int> _jump;
    std::pair<int,int> _attack;
    std::pair<int,int> _die;
    std::pair<int,int> _victory;

    bool leftPerformance;
    bool rightPerformance;
    bool finishAttack;
    bool isJumping;
    bool isFalling;

    bool pressed[300] = {false};

    int id; /// character_id
    int frame; /// animation for player
    int status;
    int nStatus;
    int facing; /// 0 - right, 1 left;
    int type; /// melee or range

    int framePerAttack, frameAttack, nextAttack;


};

#endif // CHARACTER_H_
