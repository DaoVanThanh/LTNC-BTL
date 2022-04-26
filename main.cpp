#include "loadTexture.h"
#include "Init_Quit.h"

bool loadMedia();
void freeTexture();

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
TTF_Font* font=NULL;

SDL_Color yellow={255,255,51};

LTexture background;
LTexture jungle_background;
LTexture loadFont;
LTexture monkey;
LTexture monkey2;
LTexture wire;

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
            bool q=false,conti=true;
            SDL_Event e;
            while(!q)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type==SDL_QUIT)
                    {
                        q=true;
                        conti=false;
                    }
                }
                SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                SDL_RenderClear(renderer);
                background.render(renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
                loadFont.loadFromRenderedText("Tap to start",yellow,renderer,font);
                SDL_Rect RectTangle={RECT_X,RECT_Y,RECT_WIDTH,RECT_HEIGHT};
                SDL_Point mouse;
                mouse.x=e.motion.x;
                mouse.y=e.motion.y;

                if(e.type==SDL_MOUSEMOTION)
                {
                    if(SDL_PointInRect(&mouse,&RectTangle))
                    {
                        SDL_RenderDrawRect(renderer,&RectTangle);
                    }
                    SDL_RenderPresent(renderer);
                }
                else if(e.type==SDL_MOUSEBUTTONDOWN)
                {
                    if(SDL_PointInRect(&mouse,&RectTangle))
                        break;
                }
            }
            if(conti) {
                double scrollingOffset=0;
                bool quit=false;
                SDL_Event ev;

                while(!quit)
                {
                    while(SDL_PollEvent(&ev))
                    {
                        if(ev.type==SDL_QUIT) quit=true;
                    }
                    scrollingOffset-=0.1;
                    if(scrollingOffset<-jungle_background.getWidth())
                    {
                        scrollingOffset=0;

                    }
                    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                    SDL_RenderClear(renderer);
                    jungle_background.render(renderer,scrollingOffset,0,SCREEN_WIDTH,SCREEN_HEIGHT*3);
                    jungle_background.render(renderer,scrollingOffset+jungle_background.getWidth(),0,SCREEN_WIDTH,SCREEN_HEIGHT*3);
                    wire.render(renderer, KONG_PosX+80,0,wire.getWidth(),wire.getHeight()*1.3/2);
                    monkey.render(renderer,KONG_PosX,KONG_PosY,monkey.getWidth(),monkey.getHeight());
                    monkey2.render(renderer,KONG_PosX+10,KONG_PosY-200,monkey2.getWidth(),monkey2.getHeight());
                    SDL_RenderPresent(renderer);

                }
            }
        }
    }

    freeTexture();
    quit(window,renderer);
	return 0;
}

bool loadMedia()
{
    bool success=true;
    if(!background.loadFromFile("game_image/background.png",renderer))
    {
        cout<<"Failed to load background texture image!";
        success=false;
    }
    if(!jungle_background.loadFromFile("game_image/jungle_background.png",renderer))
    {
        cout<<"Failed to load jungle_background texture image!";
        success=false;
    }
    if(!monkey.loadFromFile("game_image/monkey.png",renderer))
    {
        cout<<"Failed to load monkey texture image!";
        success=false;
    }
    if(!wire.loadFromFile("game_image/wire.png",renderer))
    {
        cout<<"Failed to load wire texture image!";
        success=false;
    }
    if(!monkey2.loadFromFile("game_image/monkey2.png",renderer))
    {
        cout<<"Failed to load move texture image!";
        success=false;
    }
    return success;
}

void freeTexture()
{
    background.free();
    jungle_background.free();
    loadFont.free();
    monkey.free();
    monkey2.free();
    wire.free();
}
