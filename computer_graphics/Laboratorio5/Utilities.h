#pragma once
#include "strutture.h"
#include "lib.h"
vec2 randomPosition(int width, int height);
void usaShaderConUniforms(unsigned int shader_programId, glm::mat4& projection, mat4& model, float currentTime, vec2 resolution);
void findBB(Figura* fig);
void updateBB(Figura* fig);
bool checkCollision(Figura obj1, Figura obj2);
void aggiornaProiettili(float deltaTime);