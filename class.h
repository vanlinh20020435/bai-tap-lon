#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
#include"thongso.h"
class TPiece
{
public:
    int Color = 0; // Represents the blue color
    bool Used = false;
};

class LTexture
{
	public:
		bool loadFromFile( std::string path,SDL_Renderer* gRenderer );
		bool loadFromRenderedText( std::string textureText,SDL_Renderer* gRenderer,TTF_Font* gFont, SDL_Color textColor );
		void free();
		void render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip = NULL );
		void renderlogo(int x, int y,SDL_Renderer* gRenderer);
		int getWidth();
		int getHeight();
        int getpos_X();
        int getpos_Y();
	private:
		SDL_Texture* mTexture=NULL;
		int pos_x;
		int pos_y;
		int mWidth=0;
		int mHeight=0;
};
//////MATRIX

#endif // CLASS_H_INCLUDED
