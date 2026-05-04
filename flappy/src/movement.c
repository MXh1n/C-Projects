#include "movement.h"

#define OFFSET_Y 12

//sound
//----------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------


float ClampObject(float value, float min, float max){
    if (value >= max) return max;
    if (value <= min) return min;

    return value;
}

float UpdatePlayerRotation(Vector2 velocity, float angleSpeed){
    float rotation; 
    
    rotation = velocity.y / angleSpeed;
    rotation = ClampObject(rotation, -45.0f, 45.0f);
    
    return rotation;
}


void UpdatePlayerMovement(Bird *bird, float dt){
    
    bird->velocity.y += bird->acceleration * dt;

    if (IsKeyPressed(KEY_SPACE) && bird->canJump) {
        bird->velocity.y = -bird->jumpSpeed;
        
        PlaySound(assetSfx.flySfx); //Fly sound
        SetSoundVolume(assetSfx.flySfx, 0.8); //adjusts the sound volume 
    }
    
    //y movement
    bird->hitbox.y += bird->velocity.y * dt;
    bird->hitbox.y = ClampObject(bird->hitbox.y, 0, GetScreenHeight() + 200);     

    bird->destinationFrame.y = bird->hitbox.y + OFFSET_Y;

    //rotation
    bird->rotation = UpdatePlayerRotation(bird->velocity, 10.0f);
}


void UpdateBackground(Background *bg, float speed, float dt){
    bg->scrollBack -= speed * dt;
    
    if (bg->scrollBack <= -bg->texture.width * bg->scale) bg->scrollBack = 0.0f; //This makes sure scrollBack resets when after it exceeds bg width 
    
    bg->pos.x = bg->scrollBack;
}


void AnimatePlayer(Rectangle *source, Animation *anim, int animSpeed){
    anim->frameCounter++;
    
    float timer = GetFPS() / (anim->totalFrame + animSpeed); 

    if (anim->frameCounter >= timer){
        anim->frameCounter = 0;
        
        anim->currentFrame++;
    }
    
    if (anim->currentFrame >= anim->totalFrame) anim->currentFrame = 0;
    
    source->x = anim->currentFrame * source->width;

}

void UpdateTube(Tube *t, int n, float dt){
    int i;

    for (i = 0; i < n; i++){
        t[i].topHitbox.x -= t[i].speed * dt;
        t[i].bottomHitbox.x -= t[i].speed * dt;
    
        t[i].dest.x = t[i].topHitbox.x; 
    }
}

void DetectCollision(Bird *bird, Tube *tube, int n){
    int i = 0;

    for (i = 0; i < n; i++){
        if (CheckCollisionRecs(bird->hitbox, tube[i].topHitbox)){
            bird->canJump = false;
            
            PlaySound(assetSfx.deathSfx); //Plays sfx
        } 
        if (CheckCollisionRecs(bird->hitbox, tube[i].bottomHitbox)){
            bird->canJump = false;
            
            PlaySound(assetSfx.deathSfx); // plays sfx
        
        } 
    }
}

