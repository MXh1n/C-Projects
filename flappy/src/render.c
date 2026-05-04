#include "render.h"

void DrawHitbox(Rectangle hitbox, Color color){
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, color);
}

void DrawGround(Tile ground){

    for (int i = 0; i < NO_OF_TILES; i++){
        ground.pos.x = i * ground.tileWidth; 
        
        DrawTextureRec(ground.texture, ground.source, ground.pos, WHITE);
    }

} 


void DrawTubeAll(Tube *tubes, int totalTube){
    int i;

    for (i = 0; i < totalTube; i++){
        DrawTexturePro(
            tubes[i].texture, tubes[i].source, tubes[i].dest, tubes[i].origin, tubes[i].rotation,
            WHITE
        );
        
        //DrawHitbox(tubes[i].topHitbox, RED);
        //DrawHitbox(tubes[i].bottomHitbox, RED);
         
    }
}


void UnloadTubeAll(Tube *a, int n){
    int i;
    
    for (i = 0; i < n; i++){
        UnloadTexture(a[i].texture);
    }
}

void DrawFont(MyFont font){
    DrawText(font.text, font.pos.x, font.pos.y, font.size, font.color);  
}

