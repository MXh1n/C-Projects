#ifndef RENDER_H
#define RENDER_H
    
#include "init.h"

void DrawHitbox(Rectangle hitbox, Color color);
void DrawGround(Tile ground); 
void DrawTubeAll(Tube *tubes, int totalTube);
void UnloadTubeAll(Tube *a, int n);
void DrawFont(MyFont font);

#endif
