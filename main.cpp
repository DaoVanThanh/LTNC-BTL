#include "loadTexture.h"
#include "Init_Quit.h"

bool loadMedia();
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
LTexture text;

int main( int argc, char* args[] )
{
    if(!init(window,renderer))
    {
        cout<<"Failed to initialize";
    }
    else
    {
        if(!loadMedia())
        {
            cout<<"Failed to load image";
        }
        else
        {
            bool q=false;
            SDL_Event e;
            while(!q)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type==SDL_QUIT) q=true;
                }
                SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                SDL_RenderClear(renderer);
                text.render(renderer,0,0);
                SDL_RenderPresent(renderer);
            }
        }
    }
    text.free();
    quit(window,renderer);
	return 0;
}

bool loadMedia()
{
    bool success=true;
    if(!text.loadFromFile("game_image/jungle_background.png",renderer))
    {
        cout<<"Failed to load texture image!";
        success=false;
    }
    return success;
}

