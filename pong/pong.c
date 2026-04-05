#include "raylib.h"
#include <math.h>

#define MY_BLUE (Color) {27, 106, 201, 255}
#define BG_BLUE (Color) {136, 183, 239, 255}
#define MY_RED (Color) {164, 20, 26, 255}
#define BG_RED (Color) {235, 91, 97, 255}
#define TEXT_WHITE (Color) {250, 250, 250, 130}

typedef struct{
    Rectangle body;
    float directionY;
    int speed;
    Color color;
} Player; //Members required for the two players

typedef struct{
    //shape 
    Rectangle body; 
    int centerX;
    int centerY;
    float radius;
    
    //movement related
    Vector2 direction;
    float speed;
    float acceleration; 

    Color color;
} Ball;


//AUDIO VARIABLES-------------------------------------------------------------------------
Sound playerReflectSound;
Sound wallReflectSound;
Sound scoreSound;
//----------------------------------------------------------------------------------------



//Function Prototypes----------------------------------------------------------------
Player InitPlayer(float posX, float posY, Color playerColor); //It initializes the player
void DrawBackground(void); //It draws the background of the game
void InputKey(float *directionY, KeyboardKey downKey, KeyboardKey upKey); //Takes user input
void ClampPlayer(int minX, int minY, int maxX, int maxY, Rectangle *body);//It keeps the player in a boundary
void UpdateBall(Rectangle player1, Rectangle player2, Ball *ball, float dt); //Update ball movement and check for collision
void NormalizeDirection(Vector2 *direction); //It keeps the diagonal speed constant
float CapLimit(float initial, float max); //Sets a max limit
void Reset(Rectangle *ball, float *speed, float *acceleration);
bool CalculateScore(int *s1, int *s2, Rectangle *body, bool calculated); //Calculates score
Vector2 AngularMovement(Vector2 direction, Rectangle ball, Rectangle player); //It calculates distance of ball Center from player and changes y direction according to it



//-----------------------------------------------------------------------------------
//
//

int main(void){
    
    //Initialization----------------------------------------------------------------------
    const int screenWidth = 850, screenHeight = 500;
    
    //Player
    Player player1 = InitPlayer(15, screenHeight/2, MY_BLUE);
    Player player2 = InitPlayer(screenWidth - 15, screenHeight/2, MY_RED);
    
    //Ball
    Ball ball;
    ball.body = (Rectangle) {screenWidth/2 - 5, screenHeight/2 - 5, 20, 20};
    ball.direction = (Vector2) {1.0f, 1.0f}; 
    ball.speed = 300.0f; 
    ball.acceleration = 1.0f; 
    ball.color = GOLD; 
    
    //score
    int score1 = 0, score2 = 0;
    int winner = 0;    
    

    //Initializing Window
    InitWindow(screenWidth, screenHeight, "Pong-Game");
    SetTargetFPS(60);
        
    //Initializing audio
    InitAudioDevice();
    
    Music backgroundMusic = LoadMusicStream("audio/retro_music.mp3");
    backgroundMusic.looping  = true; 
    PlayMusicStream(backgroundMusic);  
    
    playerReflectSound = LoadSound("audio/reflect2.mp3");
    wallReflectSound = LoadSound("audio/reflect1.mp3"); 
    Sound gameoverSound = LoadSound("audio/gameover.mp3"); 
    scoreSound = LoadSound("audio/score.mp3"); 

    //-----------------------------------------------------------------------------------
    //Main Game loop--------------------------------------------------------------------
    bool calculated = false; 
    while (!WindowShouldClose()){
        UpdateMusicStream(backgroundMusic); 

        //User Input
        InputKey(&player1.directionY, KEY_S, KEY_W);
        InputKey(&player2.directionY, KEY_DOWN, KEY_UP);
        
        float dt = GetFrameTime();

        player1.body.y += player1.directionY * player1.speed * dt;
        player2.body.y += player2.directionY * player2.speed * dt;
        
        ClampPlayer(0, 0, screenWidth, screenHeight, &player1.body);
        ClampPlayer(0, 0, screenWidth, screenHeight, &player2.body);
        
        //Ball Movement
        UpdateBall(player1.body, player2.body, &ball, dt);
        
        ball.centerX = ball.body.x + ball.body.width / 2;
        ball.centerY = ball.body.y + ball.body.height / 2;
        ball.radius = ball.body.width / 2;
        
        ClampPlayer(-100, -50, screenWidth + 100, screenHeight + 50, &ball.body);
    
        //Computing Score
        bool scored = CalculateScore(&score1, &score2, &ball.body, calculated); 
        if (score1 == 5 || score2 == 5){
            PlaySound(gameoverSound); 

            if (score1 == 5) winner = 1;
            else if (score2 == 5) winner = 2;
            break; 
        }       
        const char *displayScore1 = TextFormat("%d", score1);
        const char *displayScore2 = TextFormat("%d", score2);
        
                
        //Drawing
        BeginDrawing();
            DrawBackground(); 
            DrawRectangleRec(player1.body, player1.color); 
            DrawRectangleRec(player2.body, player2.color); 
            
            //Displaying Score
            DrawText(displayScore1, 100, 100, 300, TEXT_WHITE); 
            DrawText(displayScore2, 600, 100, 300, TEXT_WHITE); 
            
            //Drawing ball
            DrawCircle(ball.centerX, ball.centerY, ball.radius, ball.color);
            

        EndDrawing();
        //-------------------------------------------------------------------------------- 
        

        //Triggering Reset---------------------------------------------------------------
        while (scored){
            
            calculated = true;
            char *restart = "PRESS SPACE TO START";  
             
            int textWidth = MeasureText(restart, 35);

            BeginDrawing();
                DrawText(restart, screenWidth/2 - textWidth/2, 200, 35, DARKGRAY); 
            EndDrawing();
            
            if (IsKeyDown(KEY_SPACE)){
                Reset(&ball.body, &ball.speed, &ball.acceleration);
                calculated = false; 
                break;
            
            }
        
        }
        //-------------------------------------------------------------------------------- 
    }
    
    //Drawing End Screen ------------------------------------------------------------
    while (winner != 0){

        char *winner_str = "WINNER IS BLUE"; 
        float strLen = MeasureText(winner_str, 50);
        
        if (winner == 2) 
            winner_str = "WINNER IS RED";
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(winner_str, screenWidth / 2 - strLen / 2, 230, 50, GRAY);
        EndDrawing();
        
        if (WindowShouldClose()) break;
    }
    //-------------------------------------------------------------------------------
    
    UnloadMusicStream(backgroundMusic);
    UnloadSound(playerReflectSound);
    UnloadSound(wallReflectSound);
    UnloadSound(gameoverSound);
    UnloadSound(scoreSound);


    CloseAudioDevice(); 
    CloseWindow();
    return 0;
}
//------------------------------------------------------------------------------------------
//
//

//Functions--------------------------------------------------------------------------------
Player InitPlayer(float posX, float posY, Color playerColor){ 
    Player player;

    player.body = (Rectangle) {posX - 7.5, posY - 40, 15, 80};
    player.directionY = 0.0f;
    player.speed = 500;
    player.color = playerColor; 
    
    return player;
}

void DrawBackground(void){
    Rectangle background1 = {0, 0, 425, 550}; 
    Rectangle background2 = {425, 0, 425, 550}; 
    Rectangle line = {415, 0, 10, 550};

    DrawRectangleRec(background1, BG_BLUE);
    DrawRectangleRec(background2, BG_RED);
    DrawRectangleRec(line, RAYWHITE);
    
}

void InputKey(float *directionY, KeyboardKey downKey, KeyboardKey upKey){
    *directionY = 0.0f; 

    if (IsKeyDown(downKey)) *directionY = 1.0f;
    if (IsKeyDown(upKey)) *directionY = -1.0f; 
}

void ClampPlayer(int minX, int minY, int maxX, int maxY, Rectangle *body){
    if (body->x + body->width > maxX) body->x = maxX - body->width;
    else if (body->x < minX) body->x = minX; 

    if (body->y + body->height > maxY) body->y = maxY - body->height;
    else if (body->y < minY) body->y = minY;
}

void NormalizeDirection(Vector2 *direction){
    float len = sqrt((direction->x * direction->x) + (direction->y * direction->y));

    if (len > 0){
        direction->x /= len;
        direction->y /= len;
    }
}

void UpdateBall(Rectangle player1, Rectangle player2, Ball *ball, float dt){

    //checking collision with ceiling and floor-------------------------------------------
    if (ball->body.y <= 0){ //Ball hits ceiling
        PlaySound(wallReflectSound); 
        ball->direction.y = 1.0f; //Ball goes down
    }
    
    else if (ball->body.y + ball->body.height >= 500){ //Ball hits floor
        PlaySound(wallReflectSound); 
        ball->direction.y = -1.0f; //Ball goes up
    } 
    
    //----------------------------------------------------------------------------------
    NormalizeDirection(&ball->direction); 

    //Checking collision-------------------------------------------------------------------
    ball->speed = CapLimit(ball->speed, 700); 
    ball->body.x += ball->direction.x * ball->speed * dt; 
    
    //Checking collision in x - axis-----------------------------------------------------
    
    //Checking collision with right player
    if (CheckCollisionRecs(ball->body, player2)){
        if (ball->body.x + ball->body.width > player2.x) //Ball hitting left side
            ball->direction.x = -1.0f;
        
        //Audio
        PlaySound(playerReflectSound);


        ball->direction= AngularMovement(ball->direction, ball->body, player2); //Adds a variety to y direction;
        ball->body.x = player2.x - ball->body.width; 
        ball->acceleration += 0.05; 
        ball->speed *= ball->acceleration; //Increasing speed after each collision with paddle
    } 
    
    //Checking collision with left player
    if (CheckCollisionRecs(ball->body, player1)){
        if (ball->body.x < player1.x + player1.width) //Ball hitting right side
            ball->direction.x = 1.0f;
        
        //Audio
        PlaySound(playerReflectSound);
        
        ball->direction = AngularMovement(ball->direction, ball->body, player1);
        ball->body.x = player1.x + player1.width;
        ball->acceleration += 0.05; 
        ball->speed *= ball->acceleration; 
        
    } 
    
    //------------------------------------------------------------------------------------
    
    ball->body.y += ball->direction.y * ball->speed * dt; 
    

    //-------------------------------------------------------------------------------------
}

float CapLimit(float initial, float max){
    if (initial >= max) return max;
    
    return initial;
}

bool CalculateScore(int *s1, int *s2, Rectangle *body, bool calculated){ 
    
    if (body->x < -40 && !calculated){
        PlaySound(scoreSound); 
        (*s2)++;
        return true; 
    } 
    else if (body->x + body->width > 890 && !calculated){
        PlaySound(scoreSound); 

        (*s1)++;
        return true;
    }
    
    return false;
}

void Reset(Rectangle *ball, float *speed, float *acceleration){
    ball->x = 850/2 - ball->width/2;
    ball->y = 500/2 - ball->height/2;
    *speed = 200.0f;
    *acceleration = 1.0f;
}

Vector2 AngularMovement(Vector2 direction, Rectangle ball, Rectangle player){
    float playerCenterY = player.y + player.height/2.0f;
    float ballCenterY = ball.y + ball.height/2.0f;

    direction.y = (ballCenterY - playerCenterY) / (player.height/2.0f);
    NormalizeDirection(&direction); 

    return direction;
}

