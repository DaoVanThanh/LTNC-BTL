#ifndef BANANA_H_INCLUDED
#define BANANA_H_INCLUDED

#include "loadTexture.h"

class Banana : public LTexture
{
public:
    Banana();
    void HandleMove();
    void setX(const double& X) {x_val=X;}
    double getPosX() {return Posx;}
    double getPosY() {return Posy;}
    void reset();
    SDL_Rect getRect(int x, int y,int b_width, int b_height);
private:
    double x_val;
    double Posx;
    double Posy;
    SDL_Rect rect;
};

#endif // BANANA_H_INCLUDED
