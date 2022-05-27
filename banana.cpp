#include "banana.h"

Banana::Banana()
{
    Posx=SCREEN_WIDTH;
    Posy=rand()%450;
    x_val=0;
}


void Banana::HandleMove(int MIN,int MAX)
{
    Posx-=x_val;
    if(Posx < 0)
    {
        Posx=SCREEN_WIDTH;
        double rand_y=rand()%(MAX-MIN+1) + MIN;
        Posy=rand_y;
    }
}

void Banana::reset()
{
    Posx=SCREEN_WIDTH+100;
    double rand_y=rand()%450;
    Posy=rand_y;
}

SDL_Rect Banana::getRect(int x, int y,int b_width, int b_height)
{
    rect={x+val,y+val,b_width/2,b_height/2};
    return rect;
}


