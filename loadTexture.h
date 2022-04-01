#ifndef LOADTEXTURE_INCLUDED
#define LOADTEXTURE_INCLUDED

#include "globalVariable.h"

class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(string path,SDL_Renderer* &rendererr);
    void free();
    void render(SDL_Renderer* &rendererr,int x, int y, SDL_Rect* clip=NULL);
private:
    int width;
    int height;
    SDL_Texture* texture;
};

#endif // LOADTEXTURE_INCLUDED
