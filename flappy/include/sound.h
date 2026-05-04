#ifndef SOUND_H
#define SOUND_H

#include "raylib.h"

typedef struct{
    Sound flySfx;
    Sound scoreSfx;
    Sound deathSfx;

} Sfx;

typedef struct{
    
    Music menuMusic;
    Music gameMusic;

} BgMusic;


extern Sfx assetSfx;

//Functions
//------------------------------------------------------------------------------------------------------
Sfx InitSfx(void);
BgMusic InitMusic(void);

void UnloadSfx(Sfx s);
void UnloadMusic(BgMusic m);

void SetSfx(void);

#endif
