#include "state.h"

void UpdateGame(Bird *bird, Background *bg, Tube *tubes, float dt){
    
    UpdatePlayerMovement(bird, dt); //makes player fall and handles rotation
    AnimatePlayer(&bird->spriteFrame, &bird->anim, 3); 
    DetectCollision(bird, tubes, NO_OF_TUBES); 

    UpdateBackground(bg, bg->speed, dt); //animates background
    UpdateTube(tubes, NO_OF_TUBES, dt); //Moves the tube horizontally   
}
    
void DrawGame(Bird *bird, Background *bg, Tile *ground, Tube tubes[]){
    //Background
    //-------------------------------------------------------------------------------------------
    DrawTextureEx(bg->texture, bg->pos, bg->rotation, bg->scale, WHITE); //Drawing bg
    
    DrawTextureEx(bg->texture, 
                 (Vector2) {bg->texture.width * bg->scale + bg->pos.x, bg->pos.y}, 
                 bg->rotation, bg->scale, WHITE); //Drawing second after first bg
    //------------------------------------------------------------------------------------------- 

    DrawTubeAll(tubes, NO_OF_TUBES); //Drawing all tubes

    DrawGround(*ground); //drawing multiple ground tiles
 

    DrawTexturePro(bird->spriteSheet, bird->spriteFrame, bird->destinationFrame, bird->origin, bird->rotation, WHITE); //Drawing player  
   
    //Hitbox
    //-------------------------------------------------------------------------------------------
    //DrawHitbox(bird->hitbox, GREEN);
    
    //-------------------------------------------------------------------------------------------
}


void DrawMenu(Menu *menu, MyFont *font){
    DrawTextureV(menu->texture, menu->pos, WHITE);

    DrawFont(*font);
}

