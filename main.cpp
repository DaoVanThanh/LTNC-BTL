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
SDL_Color red={255,0,0};

LTexture background;
LTexture jungle_background;
LTexture loadFont;
LTexture wire;


Banana banana;
Banana bird;
Banana box;

Monkey monkey_die;

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
                loadFont.loadFromRenderedText("Tap to start","font1.ttf",yellow,renderer,font,START_X,START_Y,START_W,START_H);

                SDL_Rect Start_Rect={START_X,START_Y,START_W,START_H};
                SDL_Point mouse;
                mouse.x=e.motion.x;
                mouse.y=e.motion.y;

                if(e.type==SDL_MOUSEMOTION)
                {
                    if(SDL_PointInRect(&mouse,&Start_Rect))
                    {
                        SDL_RenderDrawRect(renderer,&Start_Rect);
                    }
                }

                SDL_RenderPresent(renderer);

                if(e.type==SDL_MOUSEBUTTONDOWN)
                {
                    if(SDL_PointInRect(&mouse,&Start_Rect))
                        break;
                }
            }
            if(conti) {
                bool quit=false;
                srand((int)time(NULL));
                bool gameOver=false;
                while(!gameOver)
                {
                    Monkey monkey;
                    if(!monkey.loadFromFile("game_image/monkey.png",renderer))
                    {
                        return 0;
                    }

                    double scrollingOffset=0;
                    int score = 0;

                    SDL_Event ev;

                    const double x=2;
                    banana.setX(x);
                    bird.setX(x);
                    box.setX(x);

                    bool endd=false;
                    while(!quit)
                    {
                        while(SDL_PollEvent(&ev))
                        {
                            if(ev.type==SDL_QUIT)
                            {
                                quit=true;
                                endd=true;
                            }
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

                        banana.HandleMove();
                        bird.HandleMove();
                        box.HandleMove();
                        banana.render(renderer,banana.getPosX(),banana.getPosY(),banana.getWidth()/4,banana.getHeight()/4);
                        bird.render(renderer,bird.getPosX(),bird.getPosY(),bird.getWidth(),bird.getHeight());
                        box.render(renderer,box.getPosX(),box.getPosY(),box.getWidth(),box.getHeight());

                        SDL_Rect mk_rect=monkey.getRect();
                        SDL_Rect banana_rect=banana.getRect(banana.getPosX(),banana.getPosY(),banana.getWidth()/3,banana.getHeight()/3);
                        SDL_Rect bird_rect=bird.getRect(bird.getPosX(),bird.getPosY(),bird.getWidth(),bird.getHeight()+val);
                        SDL_Rect box_rect=box.getRect(box.getPosX()-val,box.getPosY()-val,box.getWidth()*2,box.getHeight()*2);

                        SDL_RenderDrawRect(renderer,&mk_rect);
                        SDL_RenderDrawRect(renderer,&banana_rect);
                        SDL_RenderDrawRect(renderer,&bird_rect);
                        SDL_RenderDrawRect(renderer,&box_rect);

                        if(CollisionHandle(mk_rect,banana_rect))
                        {
                            score++;
                            banana.reset();
                        }
                        loadFont.loadFromRenderedText("Score:","font2.ttf",yellow,renderer,font,SCORE_X,SCORE_Y,SCORE_W,SCORE_H);
                        string Score=to_string(score);
                        loadFont.loadFromRenderedText(Score,"font.ttf",yellow,renderer,font,score_X,score_Y,score_W,score_H);

                        if(CollisionHandle(mk_rect,bird_rect) || CollisionHandle(mk_rect,box_rect))
                        {

                            monkey_die.render(renderer,monkey.getPosX(),monkey.getPosY(), monkey.getWidth()*4/5, monkey.getHeight()*4/5);
                            monkey.free();
                            SDL_RenderPresent(renderer);
                            SDL_Delay(1000);
                            quit=true;
                        }

                        SDL_RenderPresent(renderer);

                    }

                    if(endd==true)
                    {
                        return 0;
                    }

                    bool quit_game=false;
                    SDL_Event event;
                    while(!quit_game)
                    {
                        while(SDL_PollEvent(&event))
                            {
                            if(event.type==SDL_QUIT) {
                                quit_game=true;
                                gameOver=true;
                            }
                        }

                        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                        SDL_RenderClear(renderer);
                        background.render(renderer,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
                        string s="Game Over !";
                        for(int i=0;i<s.length();i++)
                        {
                            loadFont.loadFromRenderedText(s.substr(i,1),"font.ttf",red,renderer,font,90+100*i,-5,80,80);
                        }

                        loadFont.loadFromRenderedText("Score:","font2.ttf",yellow,renderer,font,Score_X,Score_Y,Score_W,Score_H);
                        string Score=to_string(score);
                        loadFont.loadFromRenderedText(Score,"font2.ttf",yellow,renderer,font,GO_SCORE_X,GO_SCORE_Y,GO_SCORE,GO_SCORE);
                        loadFont.loadFromRenderedText("High Score:","font2.ttf",yellow,renderer,font,HIGH_SCORE_X,HIGH_SCORE_Y,HIGH_SCORE_W,HIGH_SCORE_H);
                        loadFont.loadFromRenderedText(Score,"font2.ttf",yellow,renderer,font,HIGH_score_X,HIGH_score_Y,HIGH_score,HIGH_score);

                        loadFont.loadFromRenderedText("Play Again","font1.ttf",yellow,renderer,font,PLAY_AGAIN_X,PLAY_AGAIN_Y,PLAY_AGAIN_W,PLAY_AGAIN_H);
                        loadFont.loadFromRenderedText("Exit","font1.ttf",yellow,renderer,font,EXIT_X,EXIT_Y,EXIT_W,EXIT_H);

                        SDL_Rect PlayAgainRect={PLAY_AGAIN_X,PLAY_AGAIN_Y,PLAY_AGAIN_W,PLAY_AGAIN_H};
                        SDL_Rect ExitRect={EXIT_X,EXIT_Y,EXIT_W,EXIT_H};
                        SDL_Point mouse;
                        mouse.x=event.motion.x;
                        mouse.y=event.motion.y;

                        if(event.type==SDL_MOUSEMOTION)
                        {
                            if(SDL_PointInRect(&mouse,&PlayAgainRect))
                            {
                                SDL_RenderDrawRect(renderer,&PlayAgainRect);
                            }
                            else if(SDL_PointInRect(&mouse,&ExitRect))
                            {
                                SDL_RenderDrawRect(renderer,&ExitRect);
                            }
                        }

                        SDL_RenderPresent(renderer);

                        if(event.type==SDL_MOUSEBUTTONDOWN)
                        {
                            if(SDL_PointInRect(&mouse,&PlayAgainRect)) {
                                quit=false;
                                banana.reset();
                                box.reset();
                                bird.reset();

                            }
                            else if(SDL_PointInRect(&mouse,&ExitRect))
                            {
                                gameOver=true;

                            }
                            break;
                        }
                        loadFont.free();
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
    if(!monkey_die.loadFromFile("game_image/monkeyDie.png",renderer))
    {
        cout<<"Failed to load monkeyDie texture image!";
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
