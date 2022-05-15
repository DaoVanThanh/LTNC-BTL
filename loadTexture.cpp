#include "loadTexture.h"

LTexture::LTexture()
{
    width=0;
    height=0;
    texture=NULL;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(string path,SDL_Renderer* &rendererr)
{
    free();
    SDL_Texture* newTexture=NULL;
    SDL_Surface* loadedSurface=IMG_Load(path.c_str());
    if(loadedSurface==NULL)
    {
        cout<<"Unable to load image"<<IMG_GetError();
    }
    else
    {
        //SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
        newTexture=SDL_CreateTextureFromSurface(rendererr,loadedSurface);
        if(newTexture==NULL)
        {
            cout<<"Unable to create image"<<SDL_GetError();
        }
        else
        {
            width=loadedSurface->w;
            height=loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    texture=newTexture;
    return texture!=NULL;
}

void LTexture::loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer* &rendererr, TTF_Font* font)
{
	free();
	font=TTF_OpenFont("font.ttf", 56);
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		cout<<"Unable to render text surface!" << TTF_GetError();
	}
	else
	{

		//Create texture from surface pixels
        SDL_Texture* text = SDL_CreateTextureFromSurface( rendererr, textSurface );
		if( text == NULL )
		{
			cout<<"Unable to create texture from rendered text!"<< SDL_GetError() ;
		}
		else
		{
		    SDL_Rect textRect={RECT_X,RECT_Y,RECT_WIDTH,RECT_HEIGHT};
			SDL_RenderCopy(rendererr,text,NULL,&textRect);
		}

		SDL_FreeSurface( textSurface );
		SDL_DestroyTexture(text);
	}
}

void LTexture::render(SDL_Renderer* &rendererr,int x, int y,int Width, int Height,SDL_Rect* clip)
{
    SDL_Rect renderQuad={x,y,Width,Height};
    if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( rendererr, texture, clip, &renderQuad);
}

void LTexture::free()
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture=NULL;
        width=0;
        height=0;
    }
}

int LTexture::getWidth()
{
    return width;
}

int LTexture::getHeight()
{
    return height;
}
