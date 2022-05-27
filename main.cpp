#include "loadTexture.h"
#include "Init_Quit.h"
#include "monkey.h"
#include "b.h"

bool loadMedia();
void freeTexture();
bool CollisionHandle(SDL_Rect A, SDL_Rect B);

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
TTF_Font* font=NULL;

SDL_Color yellow={255,255,51};
SDL_Color red={255,0,0};

B banana;
const int numOfBird=3;
vector<B>bird(numOfBird);
const double VEL=20;
const int bird_posy=450;
const int banana_posy=450;

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
            bool q=false,continuee=true;
            SDL_Event e;

            while(!q)
            {

                LTexture background;
                LTexture loadFont;
                if(!background.loadFromFile("game_image/background.png",renderer))
                {
                    cout<<"Failed to load background texture image!";
                    return 0;
                }

                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type==SDL_QUIT)
                    {
                        q=true;
                        continuee=false;
                    }
                }

                SDL_SetRenderDrawColor(renderer,255,255,0,255);
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

                background.free();
                loadFont.free();

            }

            if(continuee)
            {

                bool quit=false;
                srand(time(NULL));
                bool gameOver=false;
                while(!gameOver)
                {

                // PLAY GAME
                    Monkey monkey;
                    if(!monkey.loadFromFile("game_image/monkey.png",renderer))
                    {
                        return 0;
                    }

                    double scrollingOffset=0;
                    int score = 0;
                    SDL_Event ev;

                    //SET VELOCITY
                    banana.setX(VEL);
                    for(int i=0;i<numOfBird;i++)
                    {
                        bird[i].setX(VEL);
                    }

                    bool endd=false;

                    while(!quit)
                    {

                        LTexture jungle_background;
                        LTexture wire;
                        LTexture loadFont;
                        if(!jungle_background.loadFromFile("game_image/jungle_background.png",renderer))
                        {
                            cout<<"Failed to load jungle_background texture image!";
                            return 0;
                        }
                        if(!wire.loadFromFile("game_image/wire.png",renderer))
                        {
                            cout<<"Failed to load wire texture image!";
                            return 0;
                        }

                        while(SDL_PollEvent(&ev))
                        {
                            if(ev.type==SDL_QUIT)
                            {
                                quit=true;
                                endd=true;
                            }
                            monkey.handleEvent(ev);
                        }

                        scrollingOffset-=3;
                        if(scrollingOffset<-SCREEN_WIDTH)
                        {
                            scrollingOffset=0;

                        }

                        monkey.move();

                        SDL_RenderClear(renderer);

                        jungle_background.render(renderer,scrollingOffset,0,SCREEN_WIDTH,SCREEN_HEIGHT*2);
                        jungle_background.render(renderer,scrollingOffset+SCREEN_WIDTH,0,SCREEN_WIDTH,SCREEN_HEIGHT*2);
                        wire.render(renderer, WIRE_PosX, WIRE_PosY, wire.getWidth(), wire.getHeight()*1.3/2);
                        monkey.render(renderer, monkey.getPosX(), monkey.getPosY(), monkey.getWidth()*7/10, monkey.getHeight()*7/10);

                        banana.HandleMove(0,banana_posy);
                        for(int i=0;i<numOfBird;i++)
                        {
                            bird[i].HandleMove(bird_posy/numOfBird*i+2*val,bird_posy/numOfBird*(i+1)-2*val);
                        }

                        banana.render(renderer,banana.getPosX(),banana.getPosY(),banana.getWidth()/4,banana.getHeight()/4);
                        for(int i=0;i<numOfBird;i++)
                        {
                            bird[i].render(renderer,bird[i].getPosX(),bird[i].getPosY(),bird[i].getWidth(),bird[i].getHeight());
                        }


                        SDL_Rect mk_rect=monkey.getRect();
                        SDL_Rect banana_rect=banana.getRect(banana.getPosX(),banana.getPosY(),banana.getWidth()/3,banana.getHeight()/3);
                        vector<SDL_Rect> bird_rect(numOfBird);
                        for(int i=0;i<numOfBird;i++)
                        {
                            bird_rect[i]=bird[i].getRect(bird[i].getPosX(),bird[i].getPosY(),bird[i].getWidth(),bird[i].getHeight()+val);
                        }

                        if(CollisionHandle(mk_rect,banana_rect))
                        {
                            score++;
                            banana.reset(0,banana_posy);
                        }
                        loadFont.loadFromRenderedText("Score:","font2.ttf",yellow,renderer,font,SCORE_X,SCORE_Y,SCORE_W,SCORE_H);
                        string Score=to_string(score);
                        loadFont.loadFromRenderedText(Score,"font.ttf",yellow,renderer,font,score_X,score_Y,score_W,score_H);
                        for(int i=0;i<numOfBird;i++)
                        {
                            if( CollisionHandle(mk_rect,bird_rect[i]))
                            {
                                monkey_die.render(renderer,monkey.getPosX(),monkey.getPosY()-25, monkey_die.getWidth(), monkey_die.getHeight());
                                monkey.free();
                                SDL_RenderPresent(renderer);
                                SDL_Delay(1000);
                                quit=true;
                                break;
                            }
                        }

                        SDL_RenderPresent(renderer);
                        jungle_background.free();
                        wire.free();
                        loadFont.free();

                    }

                    if(endd==true)
                    {
                        return 0;
                    }

                //GAME OVER!

                    bool quit_game=false;
                    SDL_Event event;
                    while(!quit_game)
                    {

                        LTexture background;
                        LTexture loadFont;
                        if(!background.loadFromFile("game_image/background.png",renderer))
                        {
                            cout<<"Failed to load background texture image!";
                            return 0;
                        }

                        while(SDL_PollEvent(&event))
                        {
                            if(event.type==SDL_QUIT)
                            {
                                quit_game=true;
                                gameOver=true;
                                break;
                            }
                        }

                        SDL_SetRenderDrawColor(renderer,255,255,0,255);
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

                        //GET HIGHSCORE
                        int high_sc;
                        fstream h_sc("highScore.txt",ios::in | ios::out);
                        h_sc>>high_sc;
                        if(score>high_sc) h_sc<<score;
                        else h_sc<<high_sc;
                        h_sc.close();
                        string highScore=to_string(high_sc);
                        loadFont.loadFromRenderedText("High Score:","font2.ttf",yellow,renderer,font,HIGH_SCORE_X,HIGH_SCORE_Y,HIGH_SCORE_W,HIGH_SCORE_H);
                        loadFont.loadFromRenderedText(highScore,"font2.ttf",yellow,renderer,font,HIGH_score_X,HIGH_score_Y,HIGH_score,HIGH_score);

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
                            if(SDL_PointInRect(&mouse,&PlayAgainRect))
                            {
                                quit=false;
                                banana.reset(0,banana_posy);

                                for(int i=0;i<numOfBird;i++)
                                {
                                    bird[i].reset(bird_posy/numOfBird*i+2*val,bird_posy/numOfBird*(i+1)-2*val);
                                }
                                break;
                            }
                            else if(SDL_PointInRect(&mouse,&ExitRect))
                            {
                                gameOver=true;
                                break;
                            }
                            else continue;
                        }
                        background.free();
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

    if(!monkey_die.loadFromFile("game_image/monkeyDie.png",renderer))
    {
        cout<<"Failed to load monkeyDie texture image!";
        success=false;
    }

    if(!banana.loadFromFile("game_image/banana.png",renderer))
    {
        cout<<"Failed to load banana texture image!";
        success=false;
    }

    for(int i=0;i<numOfBird;i++)
    {
        if(!bird[i].loadFromFile("game_image/bird_texture.png",renderer))
        {
            cout<<"Failed to load bird texture image!";
            success=false;
        }
    }

    return success;
}

void freeTexture()
{
    banana.free();
    for(int i=0;i<numOfBird;i++)
    {
        bird[i].free();
    }
    monkey_die.free();
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
