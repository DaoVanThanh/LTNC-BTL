#include "banana.h"

Banana::Banana()
{
    Posx=SCREEN_WIDTH;
    Posy=rand()%430;
    x_val=0;
}


void Banana::HandleMove()
{
    Posx-=x_val;
    if(Posx < 0)
    {
        Posx=SCREEN_WIDTH;
        double rand_y=rand()%430;
        Posy=rand_y;
    }
}

void Banana::reset()
{
    Posx=SCREEN_WIDTH+100;
    double rand_y=rand()%430;
    Posy=rand_y;
}

SDL_Rect Banana::getRect(int x, int y,int b_width, int b_height)
{
    rect={x+val,y+val,b_width/2,b_height/2};
    return rect;
}


