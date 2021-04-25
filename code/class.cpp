#include"class.h"
bool LTexture::loadFromFile( std::string path,SDL_Renderer* gRenderer ) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL ) {
        cout<< "Unable to load image %s! SDL_image Error: %s\n"<< path.c_str()<< IMG_GetError();
    } else {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 255, 255, 255 ) );
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) {
            cout<< "Unable to create texture from %s! SDL Error: %s\n"<< path.c_str()<< SDL_GetError();
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText,SDL_Renderer* gRenderer,TTF_Font* gFont,SDL_Color textColor ) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(),textColor );

    if( textSurface == NULL ) {
        cout<< "Unable to render text surface! SDL_ttf Error: %s\n"<< TTF_GetError();
    } else {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL ) {
            cout<< "Unable to create texture from rendered text! SDL Error: %s\n"<< SDL_GetError();
        } else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    return mTexture != NULL;
}

void LTexture::free() {
    if( mTexture != NULL ) {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void LTexture::render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip ) {
    pos_x=x;
    pos_y=y;
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void LTexture::renderlogo( int x, int y,SDL_Renderer* gRenderer) {
    SDL_RenderCopy( gRenderer, mTexture, NULL, NULL );
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

int LTexture::getpos_X() {
    return pos_x;
}

int LTexture::getpos_Y() {
    return pos_y;
}
