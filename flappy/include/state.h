#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "init.h"
#include "movement.h"
#include "render.h"


typedef enum{
    MENU = 0, GAME, PAUSE, OVER
} State;



void UpdateGame(Bird *bird, Background *bg, Tube *tubes, float dt);
void DrawGame(Bird *bird, Background *bg, Tile *ground, Tube tubes[]);
void DrawMenu(Menu *menu, MyFont *font);

#endif
