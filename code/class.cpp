#include"class.h"
bool LTexture::loadFromFile( std::string path,SDL_Renderer* gRenderer )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		cout<< "Unable to load image %s! SDL_image Error: %s\n"<< path.c_str()<< IMG_GetError();
	}
	else
	{
	    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 255, 255, 255 ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			cout<< "Unable to create texture from %s! SDL Error: %s\n"<< path.c_str()<< SDL_GetError();
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText,SDL_Renderer* gRenderer,TTF_Font* gFont,SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(),textColor );
	if( textSurface == NULL )
	{
		cout<< "Unable to render text surface! SDL_ttf Error: %s\n"<< TTF_GetError();
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			cout<< "Unable to create texture from rendered text! SDL Error: %s\n"<< SDL_GetError();
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip )
{
    pos_x=x;
    pos_y=y;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	//SDL_RenderCopy( gRenderer, mTexture, NULL, NULL );
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}
void LTexture::renderlogo( int x, int y,SDL_Renderer* gRenderer)
{
	SDL_RenderCopy( gRenderer, mTexture, NULL, NULL );
}
int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
int LTexture::getpos_X(){
    return pos_x;
}
int LTexture::getpos_Y(){
    return pos_y;
}
