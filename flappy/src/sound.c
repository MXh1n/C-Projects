#include "sound.h"

Sfx assetSfx;

//Sfx
//-----------------------------------------------------------------------------------------------------
Sfx InitSfx(void){
    Sfx s;
    
    s.flySfx = LoadSound("sound/fly.wav");
    s.scoreSfx= LoadSound("sound/score.wav");
    s.deathSfx = LoadSound("sound/death.wav");  

    return s;
}

void UnloadSfx(Sfx s){
    UnloadSound(s.flySfx);
    UnloadSound(s.scoreSfx);
    UnloadSound(s.deathSfx);
}

void SetSfx(void){
    assetSfx = InitSfx();

}
//-----------------------------------------------------------------------------------------------------

//Music
//-----------------------------------------------------------------------------------------------------
BgMusic InitMusic(void){
    BgMusic m;

    m.menuMusic = LoadMusicStream("sound/menu_music.mp3");
    m.menuMusic.looping = true; 

    m.gameMusic = LoadMusicStream("sound/game_music2.mp3");
    m.gameMusic.looping = true; 

    


    return m;
}

void UnloadMusic(BgMusic m){
    UnloadMusicStream(m.menuMusic);
    UnloadMusicStream(m.gameMusic);
}

