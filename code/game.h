#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include"class.h"
using namespace std;
class LTexture;
class TPiece;
class game{
public:
    int tmp_x,tmp_y;
    int TrangThaiManHinh=0;
    int tmp_Width=0,tmp_Height=0,tmp2_Width=0,tmp2_Height=0;
    int dem=0,diem_over=0;
    int radom=0;
    int diem=-10;
    int timedelay=600;
    int hightscore;
    bool newhighscore=false;
    bool Roi = false,DiChuyen = false;
    bool quit=false;
    bool Pause=false,down=false,_down=false;
    bool SoundOff=false;
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    Mix_Music* nhacnen=NULL;
    Mix_Music* victory=NULL;
    Mix_Music* lose=NULL;
    Mix_Chunk *sucess = NULL;
    TTF_Font *gFont = NULL;
    LTexture gTextTexture[kmenunum],color[total];
    LTexture borda,gameover,logo,tetris_logo,background,highscore,pause,play,volume,tatvolume;
    SDL_Color textColor[kmenunum];
    TPiece PieceMatrix[MATRIX_PIECES_X][MATRIX_PIECES_Y];
    TPiece TmpMatrix[4][4],TmpMatrix2[4][4];
    bool init();

    bool loadMedia();

    void close();

    void Score();

    void RenderLogo();

    void MosueDown(SDL_Event& e);

    void MosueDownToPause(SDL_Event& e);

    void MosueDownToPlay(SDL_Event& e);

    void HandEvent(SDL_Event& e);

    void Volume(SDL_Event& e);

    void ClearTmpMatrix();

    void ClearPieceMatrix();

    void SetTmpColor(int color);

    void SetTmpColor2(int color);

    void Reset();

    void GetTmpSize();

    void GenerateTmpMatrix();

    void SetTmp();

    void RotateTmpMatrix();

    void DrawGame();

    void DrawTmpMatrix();

    void DrawTmpMatrixWhenPause();

    void CollisionCheck (int key);

    void ClearRow(int h);

    void CheckRow();

    void GameOver();

    void RenderGameOver();

    void GamePlay();
};
#endif // GAME_H_INCLUDED
