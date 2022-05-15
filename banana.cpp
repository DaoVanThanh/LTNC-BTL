#include "banana.h"

Banana::Banana()
{
    Posx=SCREEN_WIDTH;
    Posy=SCREEN_HEIGHT*0.5;
    x_val=0;
    y_val=0;
}


void Banana::HandleMove()
{
    Posx-=x_val;
    if(Posx < 0)
    {
        Posx=SCREEN_WIDTH;
        int rand_y=rand()%500;
        if(rand_y>SCREEN_HEIGHT-100)
        {
            rand_y=SCREEN_HEIGHT*0.3;
        }
        Posy=rand_y;
    }
}

SDL_Rect* Banana::getRect(int x, int y,int b_width, int b_height)
{
    rect={x+pos,y+pos,b_width/2,b_height/2};
    return &rect;
}


