#include "GameMap.h"

GameMap::GameMap()
{
    Num_Block = 0;
}

GameMap::~GameMap()
{
//    NumBlock = 0;
}

void GameMap::Free()
{
    SDL_FreeSurface(mapSheet);

    Block.clear();
    Decor.clear();
}

/// https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}

bool GameMap::loadMap(std::string path, SDL_Renderer* renderer, int level)
{
    std::ifstream file_map( (path + "/level_" + int2str(level) + "/map_info.txt").c_str() );

    file_map >> Map_Width >> Map_Height;
    file_map >> Num_Block >> Num_Decor;

    decor_width = new int [Num_Decor];
    decor_height = new int [Num_Decor];

    for(int i=0; i<Num_Decor; i++)
    {
        file_map >> decor_width[i] >> decor_height[i];
    }
    file_map.close();

    info = new int* [Map_Height];

    for(int i=0; i<Map_Height; i++)
    {
        info[i] = new int [Map_Width];
    }

    mapSheet = IMG_Load( (path + "/level_" + int2str(level) + "/level.png").c_str() );

    SDL_Texture* newTexture;

    SDL_Surface* loadedSurface = IMG_Load( (path + "/level_" + int2str(level) + "/background.png").c_str() );

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    background = newTexture;


    loadedSurface = IMG_Load( (path + "/castle.png").c_str() );

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    castle = newTexture;


    loadedSurface = IMG_Load( (path + "/flag.png").c_str() );

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    flag = newTexture;

    SDL_FreeSurface(loadedSurface);

    for(int i=0; i<Num_Block; i++)
    {
        SDL_Surface* loadedSurface = IMG_Load( (path + "/level_" + int2str(level) + "/block_" + int2str(i) + ".png" ).c_str() );

        Block.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));

        SDL_FreeSurface(loadedSurface);
    }

    for(int i=0; i<Num_Decor; i++)
    {
        SDL_Surface* loadedSurface = IMG_Load( (path + "/level_" + int2str(level) + "/decor_" + int2str(i) + ".png" ).c_str() );

        Decor.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));

        SDL_FreeSurface(loadedSurface);
    }

    SDL_Color rgb;
    Uint32 data;

    int lp_x;

    for(int i=0; i<Map_Height; i++)
    {
        for(int j=0; j<Map_Width; j++)
        {
            data = getpixel(mapSheet, j, i);

            SDL_GetRGB(data, mapSheet->format, &rgb.r, &rgb.g, &rgb.b);

            if(rgb == white || rgb == green)
            {
                info[i][j] = 1;
            }
            else
            {
                info[i][j] = 0;

                if(level < numLevel)
                {
                    if(rgb == yellow)
                    {
                        lp_x = j * TILE_SIZE + 11 * TILE_SIZE;
                    }
                    if(rgb == pink)
                    {
                        victory_w = j * TILE_SIZE;
                        victory_h = (i+4) * TILE_SIZE;
                    }
                }
            }
        }
    }

    std::ifstream file( (path + "/level_" + int2str(level) + "/lp_pos.txt").c_str() );
    int num_lp;
    file >> num_lp;

    for(int i=0; i<num_lp; i++)
    {
        int temp_pos;
        file >> temp_pos;
        lp_pos.push_back(temp_pos);
    }
    file.close();

    std::sort(lp_pos.begin(), lp_pos.end(), std::greater<int>() );

    if(level < numLevel)
    {
        lp_pos.push_back(lp_x);
    }

    return mapSheet != NULL &&  background != NULL;
}

void GameMap::render(SDL_Renderer* renderer, int view, bool map_cleared, bool isBossLevel)
{
    SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_RenderCopy(renderer, background, NULL, &rect);

    SDL_Color rgb;
    Uint32 data;

    rect = {0, 0, TILE_SIZE, TILE_SIZE};

    int numGrass = 0;

    for(int i=0; i<Map_Height; i++)
    {
        for(int j=0; j<Map_Width; j++)
        {
            data = getpixel(mapSheet, j, i);

            SDL_GetRGB(data, mapSheet->format, &rgb.r, &rgb.g, &rgb.b);

            rect.x = j * TILE_SIZE - view;
            rect.y = i * TILE_SIZE;
            if(rgb == white)
            {
                rect.w = TILE_SIZE;
                rect.h = TILE_SIZE;
                SDL_RenderCopy(renderer, Block[Num_Block-1], NULL, &rect);
            }
            else if(rgb == green)
            {
                rect.w = TILE_SIZE;
                rect.h = TILE_SIZE;
                numGrass++;
                SDL_RenderCopy(renderer, Block[numGrass%(Num_Block-1)], NULL, &rect);
            }
            else if(rgb == blue)
            {
                rect.w = decor_width[0] * TILE_SIZE;
                rect.h = decor_height[0] * TILE_SIZE;
                SDL_RenderCopy(renderer, Decor[0], NULL, &rect);
            }
            else if(rgb == red)
            {
                rect.w = decor_width[1] * TILE_SIZE;
                rect.h = decor_height[1] * TILE_SIZE;
                SDL_RenderCopy(renderer, Decor[1], NULL, &rect);
            }
            else if(rgb == cyan)
            {
                rect.w = decor_width[2] * TILE_SIZE;
                rect.h = decor_height[2] * TILE_SIZE;
                SDL_RenderCopy(renderer, Decor[2], NULL, &rect);
            }
            else if(rgb == yellow)
            {
                rect.w = 23 * TILE_SIZE;
                rect.h = 18 * TILE_SIZE;
                SDL_RenderCopy(renderer, castle, NULL, &rect);
            }
            else if(rgb == pink)
            {
                rect.w = 2 * TILE_SIZE;
                rect.h = 5 * TILE_SIZE;
                SDL_RenderCopy(renderer, flag, NULL, &rect);
            }

        }
    }

}
