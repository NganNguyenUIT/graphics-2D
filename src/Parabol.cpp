#include "Parabol.h"
#include <iostream>
using namespace std;

void Draw2Points(int xc, int yc, int x, int y, SDL_Renderer *ren)
{
    int new_x;
    int new_y;

    new_x = xc + x;
    new_y = yc + y;
    SDL_RenderDrawPoint(ren, new_x, new_y);

    new_x = xc - x;
    new_y = yc + y;
    SDL_RenderDrawPoint(ren, new_x, new_y);
}
void BresenhamDrawParabolPositive(int xc, int yc, int A, SDL_Renderer *ren)
{
    int x = 0;
    int y = 0;
    int p = 1 - A;
    int xStop;
    int yStop;
    int res = SDL_GetRendererOutputSize(ren, &xStop, &yStop);

    if (res == 0)
    {
        //Area 1
        Draw2Points(xc,yc,x,y,ren);

        while(x<A)
        {
            if(p<=0)
                p += 2*x + 3 ;
            else
            {
                p += 2*x + 3 - 2*A;
                y++;
            }
            x++;
            Draw2Points(xc,yc,x,y,ren);
        }


        //Area 2
        p = 2*A - 1 ;
        while(x<xStop && y<yStop)
        {
            if(p<=0)
                p += 4*A ;
            else
            {
                p += 4*A - 4*x - 4;
                x++;
            }
            y++;
            Draw2Points(xc,yc,x,y,ren);
        }
    }

}

void BresenhamDrawParabolNegative(int xc, int yc, int A, SDL_Renderer *ren)
{
    int x = 0;
    int y = 0;
    int p = 1 - A;
    int xStop;

    int yStop;
    int res = SDL_GetRendererOutputSize(ren, &xStop, &yStop);

    if (res == 0)
    {
        //Area 1
        Draw2Points(xc,yc,x,y,ren);
        while (x < A) {
            if (p <= 0)
                p += 2*x + 3;
            else
            {
                p += 2*x + 3 - 2*A;
                y--;
            }
            x++;
            Draw2Points(xc,yc,x,y,ren);
        }

        //Area 2
        p = 2*A - 1;
        x = A;
        y = -A/2;

        while(x<xStop)
        {
            if(p<=0)
                p += 4*A;
            else
            {
                p += 4*A - 4*x - 4 ;
                x++;
            }
            y-- ;
            Draw2Points(xc,yc,x,y,ren);

        }

    }

}

void MidPointDrawParabolPositive(int xc, int yc, int A, SDL_Renderer *ren)
{
    int x = 0;
    int y = 0;
    int p = A - 1;
    int xStop;
    int yStop;
    int res = SDL_GetRendererOutputSize(ren, &xStop, &yStop);

    if (res == 0)
    {
        //Area 1
        Draw2Points(xc,yc,x,y,ren);

        while(x<A)
        {
            if(p<=0)
            {
                p += 2*A - 2*x - 3;
                y++;
            }

            else
            {
                p += -2*x - 3;
            }
            x++;
            Draw2Points(xc,yc,x,y,ren);
        }


//        //Area 2
//        p = 2*A - 1 ;
//        while(x<xStop && y<yStop)
//        {
//            if(p<=0)
//                p += 4*A ;
//            else
//            {
//                p += 4*A - 4*x - 4;
//                x++;
//            }
//            y++;
//            Draw2Points(xc,yc,x,y,ren);
//        }
    }

}