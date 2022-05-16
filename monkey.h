#ifndef MONKEY_H_INCLUDED
#define MONKEY_H_INCLUDED

#include "globalVariable.h"
#include "loadTexture.h"



class Monkey:public LTexture
{
public:
    const int MK_WIDTH = 118;
    const int MK_HEIGHT = 125;
    const double MK_VEL = 0.3;
    Monkey();
    void handleEvent(SDL_Event& e);
    void move();
    double getPosX();
    double getPosY();
    SDL_Rect getRect();
private:
    double PosX;
    double PosY;
    double Vel;
    SDL_Rect MK_RECT={KONG_PosX+val*3/2,KONG_PosY,MK_WIDTH/2,MK_HEIGHT*4/5};

};

#endif // MONKEY_H_INCLUDED
