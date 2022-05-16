#include "loadTexture.h"
#include "Init_Quit.h"
#include "monkey.h"
#include "banana.h"

bool loadMedia();
void freeTexture();
bool CollisionHandle(SDL_Rect A, SDL_Rect B);

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
TTF_Font* font=NULL;

SDL_Color yellow={255,255,51};

LTexture background;
LTexture jungle_background;
LTexture loadFont;
LTexture wire;

Banana banana;
Banana bird;
Banana box;

Monkey monkey;

int main( int argc, char* args[] )
{
    srand((int)time(NULL));
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

                SDL_Rect RectTangle={TEXT_X,TEXT_Y,TEXT_WIDTH,TEXT_HEIGHT};
                SDL_Point mouse;
                mouse.x=e.motion.x;
                mouse.y=e.motion.y;

                if(e.type==SDL_MOUSEMOTION)
                {
                    if(SDL_PointInRect(&mouse,&RectTangle))
                    {
                        SDL_RenderDrawRect(renderer,&RectTangle);
                    }
                }

                SDL_RenderPresent(renderer);

                if(e.type==SDL_MOUSEBUTTONDOWN)
                {
                    if(SDL_PointInRect(&mouse,&RectTangle))
                        break;
                }
            }
            if(conti) {
                double scrollingOffset=0;
                bool quit=false;
                SDL_Event ev;

                const double x=1;
                banana.setX(x);
                bird.setX(x);
                box.setX(x);

                while(!quit)
                {
                    while(SDL_PollEvent(&ev))
                    {
                        if(ev.type==SDL_QUIT) quit=true;
                        monkey.handleEvent(ev);
                    }
                    scrollingOffset-=0.1;
                    if(scrollingOffset<-SCREEN_WIDTH)
                    {
                        scrollingOffset=0;

                    }
                    monkey.move();
                    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                    SDL_RenderClear(renderer);

                    jungle_background.render(renderer,scrollingOffset,0,SCREEN_WIDTH,SCREEN_HEIGHT*2);
                    jungle_background.render(renderer,scrollingOffset+SCREEN_WIDTH,0,SCREEN_WIDTH,SCREEN_HEIGHT*2);
                    wire.render(renderer, WIRE_PosX, WIRE_PosY, wire.getWidth(), wire.getHeight()*1.3/2);
                    monkey.render(renderer, monkey.getPosX(), monkey.getPosY(), monkey.getWidth()*4/5, monkey.getHeight()*4/5);

                    banana.render(renderer,banana.getPosX(),banana.getPosY(),banana.getWidth()/4,banana.getHeight()/4);
                    bird.render(renderer,bird.getPosX(),bird.getPosY(),bird.getWidth(),bird.getHeight());
                    box.render(renderer,box.getPosX(),box.getPosY(),box.getWidth(),box.getHeight());

                    banana.HandleMove();
                    bird.HandleMove();
                    box.HandleMove();

                    SDL_Rect mk_rect=monkey.getRect();
                    SDL_Rect rect=banana.getRect(banana.getPosX(),banana.getPosY(),banana.getWidth()/3,banana.getHeight()/3);
                    SDL_Rect bird_rect=bird.getRect(bird.getPosX(),bird.getPosY(),bird.getWidth(),bird.getHeight()+val);
                    SDL_Rect box_rect=box.getRect(box.getPosX()-val,box.getPosY()-val,box.getWidth()*2,box.getHeight()*2);

//                    SDL_RenderDrawRect(renderer,&mk_rect);
//                    SDL_RenderDrawRect(renderer,&rect);
//                    SDL_RenderDrawRect(renderer,&bird_rect);
//                    SDL_RenderDrawRect(renderer,&box_rect);

                    if(CollisionHandle(mk_rect,bird_rect) || CollisionHandle(mk_rect,box_rect))
                    {
                        SDL_Delay(1000);
                        quit=true;
                    }

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
    if(!banana.loadFromFile("game_image/banana.png",renderer))
    {
        cout<<"Failed to load banana texture image!";
        success=false;
    }
    if(!bird.loadFromFile("game_image/bird_texture.png",renderer))
    {
        cout<<"Failed to load bird texture image!";
        success=false;
    }
    if(!box.loadFromFile("game_image/block_wood.png",renderer))
    {
        cout<<"Failed to load box texture image!";
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
    wire.free();
    banana.free();
    bird.free();
    box.free();
}

bool CollisionHandle(SDL_Rect A, SDL_Rect B)
{
    int leftA=A.x, rightA=A.x+A.w, topA=A.y, bottomA=A.y+A.h;
    int leftB=B.x, rightB=B.x+B.w, topB=B.y, bottomB=B.y+B.h;
    if(bottomA <= topB)
        return false;
    if(bottomB <= topA)
        return false;
    if(leftA >= rightB)
        return false;
    if(leftB >= rightA)
        return false;
    return true;
}
