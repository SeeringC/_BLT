#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "BasicFunction.h"
#include "GameObject.h"

class GameMap
{
public:
    GameMap();
    ~GameMap();

    void Free();

    int getNumBLock() { return Num_Block; }
    void setNumBlock(int _NumBlock) { Num_Block = _NumBlock; }

    int getNumDecor() { return Num_Decor; }
    void setNumDecor(int _NumDecor) { Num_Decor = _NumDecor; }

    int getMapWidth() { return Map_Width; }
    int getMapHeight() { return Map_Height; }

    int getNumCoin() { return numCoin; }
    void setNumCoin(int _NumCoin) { numCoin = _NumCoin; }

    int getNumGem() { return numGem; }
    void setNumGem(int _NumGem) { numGem = _NumGem; }

    int **getInfo() { return info; }
    int getVictory() { return victory_w; }

    std::vector<int> get_lppos() { return lp_pos; }
    void pop_lppos() { lp_pos.pop_back(); }

    bool loadMap(std::string path, SDL_Renderer* renderer, int level);
    void render(SDL_Renderer* renderer, int view, bool map_cleared, bool isBossLevel);

protected:
    std::vector <SDL_Texture*> Block;
    std::vector <SDL_Texture*> Decor;

    SDL_Surface* mapSheet;

    SDL_Texture* background;
    SDL_Texture* castle;
    SDL_Texture* flag;

    int Num_Block;
    int Num_Decor;
    int Map_Width;
    int Map_Height;
    int numCoin,numGem;
    int victory_w,victory_h;

    std::vector<int> lp_pos; /// little princes postition

    int** info;

    int* decor_width;
    int* decor_height;
};


#endif // GAMEMAP_H_
