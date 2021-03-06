#ifndef LOADTEXTURE_INCLUDED
#define LOADTEXTURE_INCLUDED

#include "globalVariable.h"

const int START_X=485; const int START_Y=425; const int START_W=200; const int START_H=50;
const int SCORE_X=875; const int SCORE_Y=570; const int SCORE_W=200; const int SCORE_H=50;
const int score_X=1100; const int score_Y=550; const int score_W=100; const int score_H=75;
const int Score_X=235; const int Score_Y=405; const int Score_W=200; const int Score_H=50;
const int GO_SCORE_X=460; const int GO_SCORE_Y=390; const int GO_SCORE=75;;
const int HIGH_SCORE_X=635; const int HIGH_SCORE_Y=405; const int HIGH_SCORE_W=250; const int HIGH_SCORE_H=50;
const int HIGH_score_X=905; const int HIGH_score_Y=390; const int HIGH_score=75;
const int PLAY_AGAIN_X=485; const int PLAY_AGAIN_Y=475; const int PLAY_AGAIN_W=200; const int PLAY_AGAIN_H=50;
const int EXIT_X=535; const int EXIT_Y=525; const int EXIT_W=100; const int EXIT_H=50;

const int val=15;

class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(string path,SDL_Renderer* &rendererr);
    void loadFromRenderedText(string textureText,string Font, SDL_Color textColor, SDL_Renderer* &rendererr, TTF_Font* font,int posx, int posy,int width,int height);
    void free();
    void render(SDL_Renderer* &rendererr,int x, int y,int Width, int Height);
    int getWidth();
    int getHeight();
private:
    int width;
    int height;
    SDL_Texture* texture;
};


#endif // LOADTEXTURE_INCLUDED

