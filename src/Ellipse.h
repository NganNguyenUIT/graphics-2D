#ifndef GRAPHICS2D_ELLIPSE_H
#define GRAPHICS2D_ELLIPSE_H
#include <SDL.h>
void BresenhamDrawEllipse(int xc, int yc, int a, int b, SDL_Renderer *ren);
void MidPointDrawEllipse(int xc, int yc, int a, int b, SDL_Renderer *ren);
#endif //GRAPHICS2D_ELLIPSE_H
