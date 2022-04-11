#include "Init_Quit.h"

bool init(SDL_Window* &window, SDL_Renderer* &renderer)
{
    bool success=true;
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        cout<<"SDL could not initialize"<<SDL_GetError();
        success=false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            cout<<"Warning: Linear texture filtering not enabled!";
        }
        window=SDL_CreateWindow(WINDOW_TITLE.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            cout<<"window could not be created!"<<SDL_GetError();
            success=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                cout<<"renderer could not be created!"<<SDL_GetError();
                success=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    cout<< "SDL_image could not initialize!"<<IMG_GetError();
                    success=false;
                }
                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
            }
        }
    }
    return success;
}

void quit(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_DestroyRenderer(renderer);
    renderer=NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
