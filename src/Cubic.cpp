#include "Cubic.h"

void Draw2PointsCubic(int xc, int yc, int x, int y, SDL_Renderer *ren)
{
    int new_x;
    int new_y;

    new_x = xc + x;
    new_y = yc + y;
    SDL_RenderDrawPoint(ren, new_x, new_y);

    new_x = xc - x;
    new_y = yc - y;
    SDL_RenderDrawPoint(ren, new_x, new_y);
}
void BresenhamDrawCubic(int xc, int yc, int A, SDL_Renderer *ren)
{
    int x = 0;
    int y = 0;
    int p = 2 - 3*A*A ;
    int xStop;
    int yStop;
    int res = SDL_GetRendererOutputSize(ren, &xStop, &yStop);

    if (res == 0)
    {
        //Area 1
        Draw2PointsCubic(xc,yc,x,y,ren);

        while(x<A)
        {
            if(p<=0)
                p += 6*x*x + 18*x + 14;
            else
            {
                p += 6*x*x + 18*x + 14 - 6*A*A;
                y++;
            }
            x++;
            Draw2PointsCubic(xc,yc,x,y,ren);
        }

        //Area 2
        p = 2*A - 1 ;
        while(x<xStop && y<yStop)
        {
            if(p<=0)
                p += 6*A*A;
            else
            {
                p += 6*A*A - 4*x - 4;
                x++;
            }
            y++;
            Draw2PointsCubic(xc,yc,x,y,ren);
        }

    }
}