#ifndef LOADTEXTURE_INCLUDED
#define LOADTEXTURE_INCLUDED

#include "globalVariable.h"

const int RECT_WIDTH=200;
const int RECT_HEIGHT=50;
const int RECT_X=485;
const int RECT_Y=425;
const int pos=15;

class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(string path,SDL_Renderer* &rendererr);
    void loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer* &rendererr, TTF_Font* font );
    void free();
    void render(SDL_Renderer* &rendererr,int x, int y,int Width, int Height,SDL_Rect* clip=NULL);
    int getWidth();
    int getHeight();
private:
    int width;
    int height;
    SDL_Texture* texture;
};


#endif // LOADTEXTURE_INCLUDED

