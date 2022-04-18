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
LTexture platform;

const int WALKING_ANIMATION_FRAMES = 8;
SDL_Rect SpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture SpriteSheetTexture;

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
                int frame=0;
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
                    jungle_background.render(renderer,scrollingOffset,0,SCREEN_WIDTH*4,SCREEN_HEIGHT*4);
                    jungle_background.render(renderer,scrollingOffset+jungle_background.getWidth(),0,SCREEN_WIDTH*4,SCREEN_HEIGHT*4);
                    platform.render(renderer,0,540-platform.getHeight(),platform.getWidth()*3,platform.getHeight()*2);
                    SDL_Rect* currentClip=&SpriteClips[frame/8];
                    SpriteSheetTexture.render(renderer,KONG_PosX,KONG_PosY,currentClip->w,currentClip->h,currentClip);
                    SDL_RenderPresent(renderer);
                    ++frame;

                    if( frame / 8 >= WALKING_ANIMATION_FRAMES )
                    {
                        frame = 0;
                    }
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
    if(!platform.loadFromFile("game_image/platformGrassed.png",renderer))
    {
        cout<<"Failed to load platform texture image!";
        success=false;
    }
    if(!SpriteSheetTexture.loadFromFile("game_image/move.png",renderer))
    {
        cout<<"Failed to load move texture image!";
        success=false;
    }
    else
    {
        double k=SpriteSheetTexture.getWidth()/8;
        for(int i=0;i<8;i++)
        {
            SpriteClips[i].x=k*i+5;
            SpriteClips[i].y=0;
            SpriteClips[i].w=k;
            SpriteClips[i].h=SpriteSheetTexture.getHeight();
        }
    }
    return success;
}

void freeTexture()
{
    background.free();
    jungle_background.free();
    loadFont.free();
    platform.free();
    SpriteSheetTexture.free();
}
