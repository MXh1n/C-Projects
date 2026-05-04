#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "init.h"

float ClampObject(float value, float min, float max); //Limits the value in a range

void UpdatePlayerMovement(Bird *bird, float dt); //Makes player fall and handles rotation
void AnimatePlayer(Rectangle *source, Animation *anim, int animSpeed); //Animates player

void UpdateBackground(Background *bg, float speed, float dt); //Make bg go back giving an animation

void UpdateTube(Tube *t, int n, float dt);

void DetectCollision(Bird *bird, Tube *tube, int n);

#endif
