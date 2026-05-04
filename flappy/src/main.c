#include "state.h"


//prototypes
//-------------------------------------------------------------------------------------------------
void Reset(Bird *bird, Tube *tubes, int totalTube);
int CountScore(Bird *bird, Tube *tubes, int score);

//---------------------------------------------------------------------------------------------

int main(void){
    //Congfig flags
    //-------------------------------------------------------------------------------------------
    
    //SetConfigFlags(FLAG_MSAA_4X_HINT); 
    SetConfigFlags(FLAG_VSYNC_HINT); 

    //------------------------------------------------------------------------------------------


    //Initialization
    //-----------------------------------------------------------------------------------------
    const int screenWidth = 640, screenHeight = 360;
    InitWindow(screenWidth, screenHeight, "flappy bird");
    InitAudioDevice(); 

    State currentState = MENU; //tracks State
    

    //Audio
    //----------------------------------------------------------------------------------------
    SetSfx();     
    BgMusic music = InitMusic();
    PlayMusicStream(music.menuMusic); 

    //---------------------------------------------------------------------------------------

    //Menu
    //--------------------------------------------------------------------------------------------
    Menu menu;
    menu.texture = LoadTexture("asset/menu.png");
    menu.pos = (Vector2) {0, 0};
   
    MyFont menuFont = InitFont("Press Space to play", 30, (Vector2) {160, screenHeight / 2 + 40}, WHITE);
     

    //--------------------------------------------------------------------------------------------

    //Game
    //-----------------------------------------------------------------------------------------------
    //bird
    Bird bird = InitSprite();
    
    //Background
    Background bg = InitBackground();
   
    //Tile
    Tile ground = InitGround();

    //Tube
    Tube tubes[NO_OF_TUBES];
    InitTubeAll(tubes, NO_OF_TUBES);
    

    //---------------------------------------------------------------------------------------------- 
    
    //OVer
    MyFont overFont = InitFont("GAME OVER!", 40, (Vector2) {140, 130}, DARKGRAY);
    MyFont resetFont = InitFont("Press Enter to play again!", 30, (Vector2) {140, 170}, DARKGRAY); 
    
    
    //Score
    int score = 0;    
    MyFont scoreFont = InitFont("Score: ", 20, (Vector2) {20, 20}, WHITE); 

    SetTargetFPS(60);
    //-----------------------------------------------------------------------------------------

    //Game loop
    while (!WindowShouldClose()){
        //Update
        //--------------------------------------------------------------------------------------
        float dt = GetFrameTime();
        
        switch (currentState){
            case MENU: {
                if (IsKeyPressed(KEY_SPACE)) {
                    currentState = GAME;
                    
                    StopMusicStream(music.menuMusic); //stops playing the menu music
                    PlayMusicStream(music.gameMusic); //Starts playing the game music
                } 
                
                UpdateMusicStream(music.menuMusic); //plays bg music

            } break;
            
            case GAME: {
                UpdateGame(&bird, &bg, tubes, dt);
                
                score = CountScore(&bird, tubes, score); //Tracks score
                scoreFont.text = TextFormat("Score: %d", score); 
                
                UpdateMusicStream(music.gameMusic); //plays bg music

                if (bird.hitbox.y > GetScreenHeight() + 50){
                    currentState = OVER;
                    score = 0;  //resets score
                }
            
            } break;
            
            case OVER: {
                if (IsKeyPressed(KEY_ENTER)) {
                    Reset(&bird, tubes, NO_OF_TUBES);  //Resets bird and tubes pos
                    currentState = GAME;
                } 
            } break;
                    

            default: break;
        }


        //-------------------------------------------------------------------------------------

        //Draw
        //-------------------------------------------------------------------------------------
        BeginDrawing();
            switch (currentState){
                case MENU: {
                    DrawMenu(&menu, &menuFont); 
                } break;
                
                case GAME: {
                    DrawGame(&bird, &bg, &ground, tubes); 
                
                    DrawFont(scoreFont);
                } break;
                
                case OVER: {
                    ClearBackground(RAYWHITE); 
                    DrawFont(overFont);
                    DrawFont(resetFont); 
                } break;


                default: break;
            }
        EndDrawing();
        //------------------------------------------------------------------------------------- 
    } 
    
    //De initialization
    //-----------------------------------------------------------------------------------------
    UnloadTexture(menu.texture); 
    UnloadTexture(bird.spriteSheet);
    UnloadTexture(bg.texture);
    UnloadTexture(ground.texture);
    UnloadTubeAll(&tubes, NO_OF_TUBES);    
    
    UnloadSfx(assetSfx);
    UnloadMusic(music); 

    CloseWindow();
    //-----------------------------------------------------------------------------------------
    return 0;
}


//Functions
//----------------------------------------------------------------------------------------------------
void Reset(Bird *bird, Tube *tubes, int totalTube){
    bird->hitbox.y = GetScreenHeight()/2 - bird->spriteSheet.height;
    bird->canJump = true;
    bird->velocity.y = 0; 

    InitTubeAll(tubes, totalTube);
}

int CountScore(Bird *bird, Tube *tubes, int score){
    int tubeNumber = score / 100; 

    if (bird->hitbox.x > tubes[tubeNumber].dest.x && bird->canJump){
        score += 100;
        
        PlaySound(assetSfx.scoreSfx);
    } 
    
    return score;
}


//------------------------------------------------------------------------------------------------------
