#include "init.h"

Bird InitSprite(void){
    Bird p;
    float frameWidth, frameHeight;

    p.spriteSheet = LoadTexture("asset/bird.png"); 
    
    frameWidth = p.spriteSheet.width/4;
    frameHeight = p.spriteSheet.height;
    
    p.spriteFrame = (Rectangle) {0, 0, frameWidth, frameHeight};
    
    
    float scaleWidth = frameWidth * 2, scaleHeight = frameWidth * 2;
    float offsetWidth = 5, offsetHeight = 8; 
    
    p.hitbox = (Rectangle) {
        50 + offsetWidth, GetScreenHeight()/2 - scaleHeight/2, 
        scaleWidth - offsetWidth * 2, scaleHeight - offsetHeight
    }; 

    p.destinationFrame = (Rectangle) {
        50 + scaleWidth/2, GetScreenHeight()/2 - scaleHeight/2, scaleWidth, scaleHeight
    };
    p.origin = (Vector2) {scaleWidth/2, scaleHeight/2};
    p.rotation = 0.0f;
    
    //initializing movement
    p.canJump = true; 
    p.jumpSpeed = 150.0f;
    p.acceleration = 650.0f; 

    p.velocity = (Vector2) {0, 0};


    //animation
    p.anim.frameCounter = 0;
    p.anim.currentFrame = 0;
    p.anim.totalFrame = 4;

    return p;
}

Background InitBackground(void){
    Background bg;
    
    bg.texture = LoadTexture("asset/bg.png");
    bg.pos = (Vector2) {0, -250};
    bg.rotation = 0.0f;
    bg.scale = 2.5f;
    
    //animation
    bg.scrollBack = 0.0f;
    bg.speed = 30.0f;

    return bg;
}

Tile InitGround(void){
    Tile g;

    g.texture = LoadTexture("asset/tile.png");
    g.tileWidth = g.texture.width / 8; 
    g.tileHeight = g.texture.height - 80; //80 is the height of the tubes with the tiles
    
    g.source = (Rectangle) {0, g.texture.height - g.tileHeight, g.tileWidth, g.tileHeight};
    g.pos = (Vector2) {0, GetScreenHeight() - g.tileHeight}; 

    return g;
}

Tube InitTube(void){
    Tube t = {0};
    

    t.texture = LoadTexture("asset/tube.png");
    
    t.tubeWidth = t.texture.width;
    t.tubeHeight = t.texture.height;
    
    t.source = (Rectangle) {0, 0, t.tubeWidth, t.tubeHeight};
    
    t.dest = (Rectangle) {
        200, 0,  t.tubeWidth * 2, t.tubeHeight * 2
    };
    
    t.origin = (Vector2) {0, 0};
    t.rotation = 0.0f; 
    
    //hitbox
    float tubeGapV = 40; //Vertical Gap between two tubes in pixels     
    float offsetWidth = 0; 

    t.topHitbox = (Rectangle) {
        t.dest.x, t.dest.y, t.tubeWidth*2 - offsetWidth, (t.tubeHeight)- tubeGapV  
    };
    
    t.bottomHitbox = (Rectangle) {
        t.dest.x, (t.tubeHeight * 2) - t.tubeHeight, t.tubeWidth*2 - offsetWidth, (t.tubeHeight) - tubeGapV
    };
    
    //speed
    t.speed = 100.0f;
    return t;
}

void InitTubeAll(Tube *tubes, int totalTube){
    int i;
    float offsetTube, tubeWidth, tubeGapH, tubeGapV;
    float offsetHitbox; 

    offsetTube= 300;
    tubeGapH = 250; //Horizontal spacing between the tubes
    tubeGapV = 40; //Vertical Gap between two tubes 
    
    offsetHitbox = 4; //Offsets the hitbox with the tube

    for (i = 0; i < totalTube; i++){
        tubes[i] = InitTube();

        tubeWidth = tubes[0].tubeWidth * 2;

        tubes[i].dest.x = (tubeWidth + tubeGapH * i) + offsetTube; 
        tubes[i].dest.y = GetRandomValue(-60, 0);
        
        //Hitbox
        tubes[i].topHitbox.x = tubes[i].dest.x + offsetHitbox;
        tubes[i].topHitbox.y = tubes[i].dest.y;
        
        tubes[i].bottomHitbox.x = tubes[i].dest.x + offsetHitbox;
        tubes[i].bottomHitbox.y = tubes[i].dest.y + (tubes[i].tubeHeight+ tubeGapV);


    }
    
}


MyFont InitFont(char *s, int size, Vector2 pos, Color color){
    MyFont f;

    f.text = s;
    f.size = size;
    
    f.pos = pos;
    f.color = color;

    return f;
}

