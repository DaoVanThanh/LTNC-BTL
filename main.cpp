#include <iostream>
#include<SDL.h>
using namespace std;

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const string WINDOW_TITLE="Banana Kong";

void initSDL(SDL_Window* window,SDL_Surface* screenSurface);
void quitSDL(SDL_Window* window);

int main(int argc, char* args[])
{
    SDL_Window* window=NULL;
    SDL_Surface* screenSurface=NULL;
    initSDL(window,screenSurface);
    SDL_Delay(2000);
    quitSDL(window);
    return 0;
}
void initSDL(SDL_Window* window,SDL_Surface* screenSurface)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError();
    }
    else
    {
        window=SDL_CreateWindow(WINDOW_TITLE.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            cout<<"window could not be created! SDL_Error: "<<SDL_GetError();
        }
        else
        {
            screenSurface=SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface,NULL,SDL_MapRGB(screenSurface->format,0xFF,0xFF,0xFF));
            SDL_UpdateWindowSurface(window);
        }
    }
}
void quitSDL(SDL_Window* window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
