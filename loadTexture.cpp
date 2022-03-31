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
    SDL_Texture* newTexture=NULL;
    SDL_Surface* loadedSurface=IMG_Load(path.c_str());
    if(loadedSurface==NULL)
    {
        cout<<"Unable to load image"<<IMG_GetError();
    }
    else
    {
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

void LTexture::render(SDL_Renderer* &rendererr,int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad={x,y,SCREEN_WIDTH,SCREEN_HEIGHT};
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


