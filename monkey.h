#ifndef MONKEY_H_INCLUDED
#define MONKEY_H_INCLUDED

#include "globalVariable.h"
#include "loadTexture.h"

class Monkey:public LTexture
{
public:
    const int MK_WIDTH=2;
    const int MK_HEIGHT=2;
    const int MK_VEL=1;
    Monkey();
    void handleEvent(SDL_Event& e);
    void move();
    int getPosX();
    int getPosY();
private:
    int PosX;
    int PosY;
    int Vel;
};

#endif // MONKEY_H_INCLUDED
