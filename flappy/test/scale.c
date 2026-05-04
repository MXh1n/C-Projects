#include "raylib.h"

int main(void){
    const int screenWidth = 640, screenHeight = 360;
    InitWindow(screenWidth, screenHeight, "Scaling bg");
    
    Texture2D bg = LoadTexture("Background_3.png");
    Vector2 pos = {0, -150};
    float scrollBack = 0; 
    
    //player
    Texture2D player = LoadTexture("Bird.png");
    float frameWidth = player.width / 4;
    float frameHeight = player.height;
    
    int frameCount = 0, currentFrame = 0;

    Rectangle src = {0, 0, frameWidth, frameHeight};
    Rectangle dest = {screenWidth/2, screenHeight/2, frameWidth *2, frameHeight*2};
    Vector2 origin = {frameWidth, frameHeight};
    
    
    //Environment
    Texture2D grass = LoadTexture("grass.png");
    
    //TUbe
    Texture2D tube = LoadTexture("Tube.png");
    Rectangle srcTube = {0, 0, tube.width/4, tube.height/2}; 
    Rectangle destTube = {100, 0, srcTube.width * 2, srcTube.height * 2};
    Vector2 originTube = {0, 0}; 

    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        scrollBack -= 0.5f; 
       
        if (scrollBack <= -bg.width) scrollBack = 0;

        pos.x = scrollBack;
        
        //Animating 
        frameCount++;

        if (frameCount >= (60/10)){
            frameCount = 0;
            currentFrame++;

            if (currentFrame >= 4) currentFrame = 0;
            
            src.x = currentFrame * frameWidth;
        }

        BeginDrawing();
            DrawTextureEx(bg, pos, 0, 2, WHITE); 
            DrawTextureEx(bg, (Vector2) {bg.width*2 + scrollBack, -150}, 0, 2, WHITE); 
            
            //Drawing plyer
            DrawTexturePro(player, src, dest, origin, 0, WHITE);
            
            for (int i = 0; i < 20; i++){
                DrawTextureEx(grass, (Vector2) {0+32*i, 328}, 0, 2, WHITE); 
            }
        
            DrawTexturePro(tube, srcTube, destTube, originTube, 0, WHITE);
    
        EndDrawing();
    }
    
    UnloadTexture(bg);
    CloseWindow();
    return 0;
}
