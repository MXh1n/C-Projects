#ifndef INIT_H
#define INIT_H

#include "raylib.h"
#include "sound.h"

#define NO_OF_TILES 50
#define NO_OF_TUBES 100

//structs
//--------------------------------------------------------------------------------------------
//Menu struct
//----------------------------------------------------------------------
typedef struct{
    Texture2D texture;
    Vector2 pos;
} Menu;

typedef struct{
    char *text;
    Vector2 pos;
    int size;
    Color color;
    
    
} MyFont;

//---------------------------------------------------------------------

//Game structs
//------------------------------------------------------------------------
typedef struct{
    int frameCounter;
    int currentFrame;
    int totalFrame;
 
} Animation; //variables needed to animate

typedef struct{
    
    //For Drawing
    Texture2D spriteSheet;
    Rectangle spriteFrame;
    Rectangle destinationFrame;
    Vector2 origin;
    float rotation; 

    //Movement
    Rectangle hitbox; 
    Vector2 velocity;
    float jumpSpeed;
    float acceleration;
    bool startFlying; //doesnt make bird immediately
    bool canJump; //Allows to jump 

    //animation
    Animation anim;

} Bird; //properties of main bird or player

typedef struct{
    Texture2D texture;
    Vector2 pos;
    float rotation;
    float scale;
    
    //animation
    float scrollBack;
    float speed;

} Background; //background propreties

typedef struct{
    Texture2D texture;
    
    float tileWidth, tileHeight;
    
    Rectangle source;
    Vector2 pos;

} Tile;

typedef struct{
    Texture2D texture;
    
    float tubeWidth, tubeHeight;

    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation; 
    
    Rectangle topHitbox, bottomHitbox;
    float speed;

} Tube;

//---------------------------------------------------------------------------------------------

//Functions
//--------------------------------------------------------------------------------------------
Bird InitSprite(void);
Background InitBackground(void);
Tile InitGround(void);
Tube InitTube(void);
void InitTubeAll(Tube *tubes, int totalTube);

MyFont InitFont(char *s, int size, Vector2 pos, Color color);
//----------------------------------------------------------------------------------------------

#endif
