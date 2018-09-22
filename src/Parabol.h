#ifndef GRAPHICS2D_PARAPOL_H
#define GRAPHICS2D_PARAPOL_H
#include <SDL.h>
void BresenhamDrawParabolPositive(int xc, int yc, int A, SDL_Renderer *ren);
void BresenhamDrawParabolNegative(int xc, int ycb, int A, SDL_Renderer *ren);
void MidPointDrawParaolPositive(int xc, int yc, int A, SDL_Renderer *ren);
#endif //GRAPHICS2D_PARAPOL_H
