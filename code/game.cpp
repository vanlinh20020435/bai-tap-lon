#include"game.h"
using namespace std;
bool game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Tetris By Nguyen Van Linh", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool game::loadMedia()
{

	//Loading success flag
	bool success = true;
    if(!(color[blue].loadFromFile("image//blue.png",gRenderer)&&
    borda.loadFromFile("image//borda.png",gRenderer)&&
    color[violet].loadFromFile("image//violet.png",gRenderer)&&
    color[cyan].loadFromFile("image//cyan.png",gRenderer)&&
    color[green].loadFromFile("image//green.png",gRenderer)&&
    color[orange].loadFromFile("image//orange.png",gRenderer)&&
    color[red].loadFromFile("image//red.png",gRenderer)&&
    color[yellow].loadFromFile("image//yellow.png",gRenderer)&&
    logo.loadFromFile("image//logo(2).png",gRenderer)&&
    gameover.loadFromFile("image//gameover.png",gRenderer)&&
    tetris_logo.loadFromFile("image//Tetris_Logo.jpg",gRenderer)&&
    background.loadFromFile("image//background.png",gRenderer)&&
    highscore.loadFromFile("image//hightscore.png",gRenderer)))
    {
        printf( "Failed to load arrow texture!\n" );
		success = false;
    }
    nhacnen = Mix_LoadMUS( "music//Tetris.mp3" );
	if( nhacnen == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	victory = Mix_LoadMUS( "music//highscore.mp3" );
	if( victory == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	lose = Mix_LoadMUS( "music//lose.wav" );
	if( lose == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	sucess = Mix_LoadWAV( "music//success.wav" );
	if( sucess == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	//Open the font
	gFont = TTF_OpenFont( "ARCADE.ttf", 50 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	return success;
}

void game::close()
{
	//Free loaded images
	gTextTexture[0].free();
    gTextTexture[1].free();
	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void game::Score(){
    string s1=to_string(diem);
    string s2=to_string(hightscore);
    gFont = TTF_OpenFont( "ARCADE.ttf", 30 );
    textColor[3]={255,255,255};
    textColor[2]={255,255,255};
    textColor[1]={255,255,255};
    textColor[0]={255,255,255};
    gTextTexture[3].loadFromRenderedText( s1,gRenderer,gFont, textColor[3] );
    gTextTexture[2].loadFromRenderedText( "SCORE: ",gRenderer,gFont, textColor[2] );
    gTextTexture[1].loadFromRenderedText( s2,gRenderer,gFont, textColor[3]);
    gTextTexture[0].loadFromRenderedText( "HIGH SCORE: ",gRenderer,gFont, textColor[2] );
    gTextTexture[2].render(480,360,gRenderer);
    gTextTexture[3].render(580,360,gRenderer);
    gTextTexture[0].render(480,460,gRenderer);
    gTextTexture[1].render(660,460,gRenderer);
}
void game::RenderLogo(){
    int x,y;
    SDL_GetMouseState( &x, &y );
    //bool insile =false;
                for (int i = 0; i < kmenunum; ++i)
                {
                    if (x >= gTextTexture[i].getpos_X() && x <= gTextTexture[i].getpos_X() + gTextTexture[i].getWidth() &&
                        y >= gTextTexture[i].getpos_Y() && y <= gTextTexture[i].getpos_Y() + gTextTexture[i].getHeight())
                    {
                        textColor[i]={255,0,0};
                    }
                    else
                    {
                        textColor[i]={255,255,255};
                    }
                }
        gFont = TTF_OpenFont( "ARCADE.ttf", 50 );
        gTextTexture[1].loadFromRenderedText( "EXIT",gRenderer,gFont, textColor[1] );
        gTextTexture[0].loadFromRenderedText( "PLAY",gRenderer,gFont, textColor[0] );
        tetris_logo.renderlogo(0,0,gRenderer);
        gTextTexture[0].render(323,360,gRenderer);
        gTextTexture[1].render(323,420,gRenderer);
}
void game::MosueDown(SDL_Event& e){
    int x,y;
    if(e.type == SDL_MOUSEBUTTONUP){
        SDL_GetMouseState( &x, &y );
        if (x >= gTextTexture[0].getpos_X() && x <= gTextTexture[0].getpos_X() + gTextTexture[0].getWidth() &&
            y >= gTextTexture[0].getpos_Y() && y <= gTextTexture[0].getpos_Y() + gTextTexture[0].getHeight()){
                newhighscore=false;
                diem_over=0;
                TrangThaiManHinh=1;
                Mix_PlayMusic(nhacnen,-1);
            }
        else if (x >= gTextTexture[1].getpos_X() && x <= gTextTexture[1].getpos_X() + gTextTexture[1].getWidth() &&
                y >= gTextTexture[1].getpos_Y() && y <= gTextTexture[1].getpos_Y() + gTextTexture[1].getHeight()){
                TrangThaiManHinh=-1;
            }
    }
}
void game::HandEvent(SDL_Event& e){
    while( SDL_PollEvent(&e) != 0 ){

					if( e.type == SDL_QUIT )
					{

						quit = true;
					}
					if(e.type == SDL_KEYDOWN){
                            DiChuyen=true;

                        switch (e.key.keysym.sym){
                            case SDLK_ESCAPE:{
                                quit=true;
                                break;
                            }
                            case SDLK_UP:{
                                RotateTmpMatrix();
                                DiChuyen=true;
                                break;
                            }
                            case SDLK_RIGHT:{
                                if(tmp_x+tmp_Width*20<=380)tmp_x+=20;
                                CollisionCheck(2);
                                DiChuyen=true;
                                break;
                            }
                            case SDLK_LEFT:{
                                if(tmp_x>=80)tmp_x-=20;
                                CollisionCheck(3);
                                DiChuyen=true;
                                break;
                            }
                            case SDLK_DOWN:{
                                if(tmp_y+tmp_Height*20<540)tmp_y+=20;
                                dem+=20;
                                CollisionCheck(4);
                                DiChuyen=true;
                                break;
                            }                    }
					}
				}
};
void game::ClearTmpMatrix()
{
    for (int xp = 0; xp < 4; xp++)
    {
        for (int yp = 0; yp < 4; yp++)
        {
            TmpMatrix[xp][yp].Used = false;
            TmpMatrix2[xp][yp].Used = false;
        }
    }
}
void game::ClearPieceMatrix()
{
    for (int xp = 0; xp < MATRIX_PIECES_X; xp++)
    {
        for (int yp = 0; yp < MATRIX_PIECES_Y; yp++)
        {
            PieceMatrix[xp][yp].Used = false;
        }
    }
}
void game::SetTmpColor(int color)
{
    for (int xp = 0; xp < 4; xp++)
    {
        for (int yp = 0; yp < 4; yp++)
        {
            TmpMatrix[xp][yp].Color = color;
        }
    }
}
void game::SetTmpColor2(int color)
{
    for (int xp = 0; xp < 4; xp++)
    {
        for (int yp = 0; yp < 4; yp++)
        {
            TmpMatrix2[xp][yp].Color = color;
        }
    }
}
void game::Reset(){
    tmp_x=star_x;
    tmp_y=star_y;
}
void game::GetTmpSize()
{
    int width = 0,width2 = 0;
    int height = 0,height2 = 0;
    //
    for (int xp = 0; xp < 4; xp++)
    {
        for (int yp = 0; yp < 4; yp++)
        {
            if (TmpMatrix[xp][yp].Used == true)
            {
                if (xp > width)
                {
                    width = xp;
                }
                if (yp > height)
                {
                    height = yp;
                }
            }
            if (TmpMatrix2[xp][yp].Used == true)
            {
                if (xp > width2)
                {
                    width2 = xp;
                }
                if (yp > height2)
                {
                    height2 = yp;
                }
            }
        }
    }
    //
    tmp_Width = width;
    tmp_Height = height;
    tmp2_Width = width2;
    tmp2_Height = height2;
}
void game::GenerateTmpMatrix()
{
    // 0 = I, 1 = J, 2 = L, 3 = O, 4 = Z, 5 = T, 6 = S
    // Clear the old Matrix
    diem=diem+10;
    ClearTmpMatrix();
    Reset();
    //
    if (radom == 0)
    {
        // I
        SetTmpColor(cyan);
        TmpMatrix[0][0].Used = true;
        TmpMatrix[0][1].Used = true;
        TmpMatrix[0][2].Used = true;
        TmpMatrix[0][3].Used = true;
    }
    else if (radom == 1)
    {
        // J
        SetTmpColor(blue);
        TmpMatrix[1][0].Used = true;
        TmpMatrix[1][1].Used = true;
        TmpMatrix[1][2].Used = true;
        TmpMatrix[0][2].Used = true;
    }
    else if (radom == 2)
    {
        // L
        SetTmpColor(orange);
        TmpMatrix[0][0].Used = true;
        TmpMatrix[0][1].Used = true;
        TmpMatrix[0][2].Used = true;
        TmpMatrix[1][2].Used = true;
    }
    else if (radom == 3)
    {
        // O
        SetTmpColor(yellow);
        TmpMatrix[0][0].Used = true;
        TmpMatrix[0][1].Used = true;
        TmpMatrix[1][1].Used = true;
        TmpMatrix[1][0].Used = true;
    }
    else if (radom == 4)
    {
        // Z
        SetTmpColor(red);
        TmpMatrix[0][0].Used = true;
        TmpMatrix[1][0].Used = true;
        TmpMatrix[1][1].Used = true;
        TmpMatrix[2][1].Used = true;
    }
    else if (radom == 5)
    {
        // T
        SetTmpColor(violet);
        TmpMatrix[1][0].Used = true;
        TmpMatrix[0][1].Used = true;
        TmpMatrix[1][1].Used = true;
        TmpMatrix[2][1].Used = true;
    }
    else if (radom == 6)
    {
        // S
        SetTmpColor(green);
        TmpMatrix[0][1].Used = true;
        TmpMatrix[1][1].Used = true;
        TmpMatrix[1][0].Used = true;
        TmpMatrix[2][0].Used = true;
    }
    radom=rand()%7;
    if (radom == 0)
    {
        // I
        SetTmpColor2(cyan);
        TmpMatrix2[0][0].Used = true;
        TmpMatrix2[0][1].Used = true;
        TmpMatrix2[0][2].Used = true;
        TmpMatrix2[0][3].Used = true;
    }
    else if (radom == 1)
    {
        // J
        SetTmpColor2(blue);
        TmpMatrix2[1][0].Used = true;
        TmpMatrix2[1][1].Used = true;
        TmpMatrix2[1][2].Used = true;
        TmpMatrix2[0][2].Used = true;
    }
    else if (radom == 2)
    {
        // L
        SetTmpColor2(orange);
        TmpMatrix2[0][0].Used = true;
        TmpMatrix2[0][1].Used = true;
        TmpMatrix2[0][2].Used = true;
        TmpMatrix2[1][2].Used = true;
    }
    else if (radom == 3)
    {
        // O
        SetTmpColor2(yellow);
        TmpMatrix2[0][0].Used = true;
        TmpMatrix2[0][1].Used = true;
        TmpMatrix2[1][1].Used = true;
        TmpMatrix2[1][0].Used = true;
    }
    else if (radom == 4)
    {
        // Z
        SetTmpColor2(red);
        TmpMatrix2[0][0].Used = true;
        TmpMatrix2[1][0].Used = true;
        TmpMatrix2[1][1].Used = true;
        TmpMatrix2[2][1].Used = true;
    }
    else if (radom == 5)
    {
        // T
        SetTmpColor2(violet);
        TmpMatrix2[1][0].Used = true;
        TmpMatrix2[0][1].Used = true;
        TmpMatrix2[1][1].Used = true;
        TmpMatrix2[2][1].Used = true;
    }
    else if (radom == 6)
    {
        // S
        SetTmpColor2(green);
        TmpMatrix2[0][1].Used = true;
        TmpMatrix2[1][1].Used = true;
        TmpMatrix2[1][0].Used = true;
        TmpMatrix2[2][0].Used = true;
    }
    GetTmpSize();
}
void game::SetTmp()
{
    TPiece MatrixBackup[5][5];
    // Left Side
    while (true)
    {
        for (int xp = 0; xp < 4; xp++)
        {
            for (int yp = 0; yp < 4; yp++)
            {
                MatrixBackup[xp][yp] = TmpMatrix[xp][yp];
            }
        }
        //
        bool h = false;
        for (int yTmp = 0; yTmp < 4; yTmp++)
        {
            if (TmpMatrix[0][yTmp].Used == true)
            {
                h = true;
            }
        }
        if (h == true)
        {
            break;
        }
        else
        {
            for (int xp = 0; xp < 4; xp++)
            {
                for (int yp = 0; yp < 4; yp++)
                {
                    TmpMatrix[xp][yp] = MatrixBackup[xp + 1][yp];
                }
            }
        }
    }
    // Up Side
    while (true)
    {
        for (int xp = 0; xp < 4; xp++)
        {
            for (int yp = 0; yp < 4; yp++)
            {
                MatrixBackup[xp][yp] = TmpMatrix[xp][yp];
            }
        }
        //
        bool h = false;
        for (int xTmp = 0; xTmp < 4; xTmp++)
        {
            if (TmpMatrix[xTmp][0].Used == true)
            {
                h = true;
            }
        }
        if (h == true)
        {
            break;
        }
        else
        {
            for (int xp = 0; xp < 4; xp++)
            {
                for (int yp = 0; yp < 4; yp++)
                {
                    TmpMatrix[xp][yp] = MatrixBackup[xp][yp + 1];
                }
            }
        }
    }

}
void game::RotateTmpMatrix()
{
    bool vacham=false;
    TPiece MatrixBackup[4][4];
    for (int xp = 0; xp < 4; xp++)
    {
        for (int yp = 0; yp < 4; yp++)
        {
            MatrixBackup[xp][yp] = TmpMatrix[xp][yp];
        }
    }
    //
    TmpMatrix[0][3] = MatrixBackup[3][3];
    TmpMatrix[0][2] = MatrixBackup[2][3];
    TmpMatrix[0][1] = MatrixBackup[1][3];
    TmpMatrix[0][0] = MatrixBackup[0][3];
    //
    TmpMatrix[3][3] = MatrixBackup[3][0];
    TmpMatrix[2][3] = MatrixBackup[3][1];
    TmpMatrix[1][3] = MatrixBackup[3][2];
    TmpMatrix[0][3] = MatrixBackup[3][3];
    //
    TmpMatrix[3][3] = MatrixBackup[3][0];
    TmpMatrix[3][2] = MatrixBackup[2][0];
    TmpMatrix[3][1] = MatrixBackup[1][0];
    TmpMatrix[3][0] = MatrixBackup[0][0];
    //
    TmpMatrix[0][0] = MatrixBackup[0][3];
    TmpMatrix[1][0] = MatrixBackup[0][2];
    TmpMatrix[2][0] = MatrixBackup[0][1];
    TmpMatrix[3][0] = MatrixBackup[0][0];
    //
    TmpMatrix[1][1] = MatrixBackup[1][2];
    TmpMatrix[1][2] = MatrixBackup[2][2];
    TmpMatrix[2][2] = MatrixBackup[2][1];
    TmpMatrix[2][1] = MatrixBackup[1][1];
    //
    SetTmp();
    GetTmpSize();
    if(tmp_x+tmp_Width*20>400||tmp_x<60||tmp_y+tmp_Height*20>27*20) vacham=true;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(TmpMatrix[i][j].Used==true&&PieceMatrix[(tmp_x/20)+i-3][(tmp_y/20)+j].Used==true){
                vacham=true;
            }
        }
    }
    if(vacham==true){
        for (int xp = 0; xp < 4; xp++)
        {
            for (int yp = 0; yp < 4; yp++)
            {
                TmpMatrix[xp][yp]=MatrixBackup[xp][yp];
            }
        }
        SetTmp();
        GetTmpSize();
    }
}
void game::DrawTetrisMatrix(){
    logo.render(455,80,gRenderer);
    background.render(60,0,gRenderer);
     Score();
    int px_start = MATRIX_DRAW_POS_X + 20;
    int py_start = MATRIX_DRAW_POS_Y;
    //
    int rightBorderPosX = px_start + (MATRIX_PIECES_X * 20);
    int leftBorderPosX = MATRIX_DRAW_POS_X;
    int YLimit = (MATRIX_PIECES_Y * 20) + 20 + py_start;
    for (int yp = 0; yp < YLimit; yp+=20)
    {
        borda.render(MATRIX_DRAW_POS_X, yp,gRenderer);
        borda.render(rightBorderPosX, yp,gRenderer);
    }
    for (int xp = MATRIX_DRAW_POS_X; xp < rightBorderPosX; xp += 20)
    {
        borda.render(xp, YLimit - 20,gRenderer);
    }
    for(int i=0;i<MATRIX_PIECES_X;i++){
        for(int j=0;j<MATRIX_PIECES_Y;j++){
            if(PieceMatrix[i][j].Used==true) color[PieceMatrix[i][j].Color].render(MATRIX_DRAW_POS_X+20+i*20,j*20,gRenderer);
        }
    }

}
void game::DrawTmpMatrix(){
    if(Roi== false&&timedelay>300){
        GenerateTmpMatrix();
        timedelay=0;
    }
    Roi=true;
    if(tmp_y+tmp_Height*20==27*20) Roi=false;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            if(TmpMatrix[i][j].Used==true){
                if(PieceMatrix[(tmp_x/20)+i-3][(tmp_y/20)+j+1].Used==true) Roi=false;
                color[TmpMatrix[i][j].Color].render(tmp_x+i*20,tmp_y+j*20,gRenderer);
            }
            if(TmpMatrix2[i][j].Used==true){
                color[TmpMatrix2[i][j].Color].render(110-tmp2_Width*10+i*20+440,200+j*20,gRenderer);
            }
        }
    }
    if(Roi==false) timedelay=timedelay+20;
    if(Roi== false&&timedelay>300){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(TmpMatrix[i][j].Used==true){
                    PieceMatrix[(tmp_x/20)+i-3][(tmp_y/20)+j]=TmpMatrix[i][j];
                }
            }
        }
    }
    if(dem>=dem_max&&DiChuyen==false){
        if(timedelay==0)tmp_y=tmp_y+20;
        dem=0;
    }
}
void game::CollisionCheck (int key){
    bool vacham=false;
    if(key==2){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(TmpMatrix[i][j].Used==true&&PieceMatrix[(tmp_x/20)+i-3][(tmp_y/20)+j].Used==true){
                    vacham=true;
                }
            }
        }
        if(vacham==true) tmp_x=tmp_x-20;
    }
    if(key==3){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(TmpMatrix[i][j].Used==true&&PieceMatrix[(tmp_x/20)+i-3][(tmp_y/20)+j].Used==true){
                    vacham=true;
                }
            }
        }
        if(vacham==true) tmp_x=tmp_x+20;
    }
    if(key==4){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(TmpMatrix[i][j].Used==true&&PieceMatrix[(tmp_x/20)+i-3][(tmp_y/20)+j].Used==true){
                    vacham=true;
                }
            }
        }
        if(vacham==true) tmp_y=tmp_y-20;
    }
}
void game::ClearRow(int h){
    Mix_PlayChannel( -1, sucess, 0 );
    for(int j=0;j<MATRIX_PIECES_X;j++) PieceMatrix[j][h].Used==false;
    for(int i=h;i>=0;i--){
        for(int j=0;j<MATRIX_PIECES_X;j++){
            if(i==0) PieceMatrix[j][i].Used=false;
            else PieceMatrix[j][i]=PieceMatrix[j][i-1];
        }

    }
}
void game::CheckRow()
{
    bool xoahang=true;
    int demsohang=0;
    for(int i=MATRIX_PIECES_Y-1;i>=0;i--){
        for(int j=0;j<MATRIX_PIECES_X;j++){
            if(PieceMatrix[j][i].Used==false) xoahang=false;
        }
        if(xoahang==true){
            ClearRow(i);
            demsohang++;
        }
        xoahang=true;
    }
    if(demsohang==1) diem=diem+100;
    else diem=diem+100*demsohang*demsohang;
}
void game::GameOver(){
    for(int i=0;i<MATRIX_PIECES_X;i++){
        if(PieceMatrix[i][0].Used==true){
            TrangThaiManHinh=2;
            ClearPieceMatrix();
            diem_over=diem;
            diem=-10;
            break;
    }
    }
}
void game::RenderGameOver(){
    int x,y;
    string s=to_string(diem_over);
    SDL_GetMouseState( &x, &y );
    //bool insile =false;
                for (int i = 0; i < 2; ++i)
                {
                    if (x >= gTextTexture[i].getpos_X() && x <= gTextTexture[i].getpos_X() + gTextTexture[i].getWidth() &&
                        y >= gTextTexture[i].getpos_Y() && y <= gTextTexture[i].getpos_Y() + gTextTexture[i].getHeight())
                    {
                        textColor[i]={255,0,0};
                    }
                    else
                    {
                        textColor[i]={255,255,255};
                    }
                }
                textColor[2]={255,255,255};textColor[3]={255,255,255};
        gFont = TTF_OpenFont( "ARCADE.ttf", 50 );
        gTextTexture[1].loadFromRenderedText( "EXIT",gRenderer,gFont, textColor[1]);
        gTextTexture[0].loadFromRenderedText( "PLAY AGAIN",gRenderer,gFont, textColor[0]);
        gFont = TTF_OpenFont( "ARCADE.ttf", 80 );
        gTextTexture[3].loadFromRenderedText( s,gRenderer,gFont, textColor[3]);
        gTextTexture[2].loadFromRenderedText( "SCORE: ",gRenderer,gFont, textColor[2]);
        gameover.render(0,100,gRenderer);
        if(newhighscore==true)highscore.render(430+gTextTexture[3].getWidth(),260-50,gRenderer);
        gTextTexture[0].render(245,360,gRenderer);
        gTextTexture[1].render(330,420,gRenderer);
        gTextTexture[2].render(205,260,gRenderer);
        gTextTexture[3].render(455,260,gRenderer);
}
void game::GamePlay(){
    int nhacvictory=0;
    fstream file,fileout;
    file.open("hightscore.txt");
    file>>hightscore;
    file.close();
    fileout.open("hightscore.txt",ios::out);
    textColor[0]={255,255,255};textColor[1]={255,255,255};
    srand((int)time(0));
    radom = rand()%7;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    SDL_Event e;
			Mix_PlayMusic(nhacnen,-1);
			while( !quit )
			{
			    dem+=20;
			    DiChuyen=false;
				HandEvent(e);
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
				SDL_RenderClear( gRenderer );
				if(TrangThaiManHinh==0){
                        RenderLogo();
                        MosueDown(e);
				}
				else if(TrangThaiManHinh==-1) quit=true;
				else if(TrangThaiManHinh==1){
                    nhacvictory=0;
                    DrawTetrisMatrix();
                    DrawTmpMatrix();
                    CheckRow();
                    GameOver();
				}
				else if(TrangThaiManHinh==2){
                        if(diem_over<=hightscore){
                               if(nhacvictory==0) Mix_PlayMusic(lose,1);
                                nhacvictory++;
                        }
                        if(diem_over>hightscore){
                            if(nhacvictory==0)Mix_PlayMusic(victory,1);
                            hightscore=diem_over;
                            nhacvictory++;
                            newhighscore=true;
                        }
                        RenderGameOver();
                        MosueDown(e);

				}
				SDL_RenderPresent( gRenderer );
			}
		}
	}
    fileout<<hightscore;
    fileout.close();
	close();
}
