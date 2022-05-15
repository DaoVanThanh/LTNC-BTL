#include "monkey.h"

Monkey::Monkey()
{
    PosX=KONG_PosX;
    PosY=KONG_PosY;
    Vel=0;
}

void Monkey::handleEvent(SDL_Event& e)
{
    if(e.type==SDL_KEYDOWN && e.key.repeat==0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            Vel -= MK_VEL;
            break;
        case SDLK_DOWN:
            Vel += MK_VEL;
            break;
        }
    }
    else if(e.type==SDL_KEYUP && e.key.repeat==0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            Vel += MK_VEL;
            break;
        case SDLK_DOWN:
            Vel -= MK_VEL;
            break;
        }
    }
}

void Monkey::move()
{
    PosY += Vel;
    MK_RECT.y = PosY;
    if(PosY < 0 || (PosY+MK_HEIGHT) > SCREEN_HEIGHT)
    {
        PosY -= Vel;
        MK_RECT.y = PosY;
    }
}

double Monkey::getPosX()
{
    return PosX;
}

double Monkey::getPosY()
{
    return PosY;
}

SDL_Rect* Monkey::getRect()
{
    return &MK_RECT;
}

