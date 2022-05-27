#ifndef BANANA_H_INCLUDED
#define BANANA_H_INCLUDED

#include "loadTexture.h"

class B : public LTexture
{
public:
    B();
    void HandleMove(int MIN,int MAX);
    void setX(const double& _vel) {vel=_vel;}
    double getPosX() {return Posx;}
    double getPosY() {return Posy;}
    void reset(int MIN,int MAX);
    SDL_Rect getRect(int x, int y,int b_width, int b_height);
private:
    double vel;
    double Posx;
    double Posy;
    SDL_Rect rect;
};

#endif // BANANA_H_INCLUDED
