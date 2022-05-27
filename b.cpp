#include "b.h"

B::B()
{
    Posx=SCREEN_WIDTH;
    Posy=rand()%450;
    vel=0;
}


void B::HandleMove(int MIN,int MAX)
{
    Posx-=vel;
    if(Posx < 0)
    {
        Posx=SCREEN_WIDTH;
        double rand_y=rand()%(MAX-MIN+1) + MIN;
        Posy=rand_y;
    }
}

void B::reset(int MIN,int MAX)
{
    Posx=SCREEN_WIDTH+100;
    double rand_y=rand()%(MAX-MIN+1) + MIN;
    Posy=rand_y;
}

SDL_Rect B::getRect(int x, int y,int b_width, int b_height)
{
    rect={x+val,y+val,b_width/2,b_height/2};
    return rect;
}


