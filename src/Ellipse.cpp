#include "Ellipse.h"

void Draw4Points(int xc, int yc, int x, int y, SDL_Renderer *ren)
{
    int new_x;
    int new_y;

    new_x = xc + x;
    new_y = yc + y;
    SDL_RenderDrawPoint(ren, new_x, new_y);

    new_x = xc - x;
    new_y = yc + y;
    SDL_RenderDrawPoint(ren, new_x, new_y);

    new_x = xc + x;
    new_y = yc - y;
    SDL_RenderDrawPoint(ren, new_x, new_y);

    new_x = xc - x;
    new_y = yc - y;
    SDL_RenderDrawPoint(ren, new_x, new_y);
}

void BresenhamDrawEllipse(int xc, int yc, int a, int b, SDL_Renderer *ren)
{
    // Area 1
    int x = 0 ;
    int y = b ;
    int p = a*a - 2*a*a*b+2*b*b;
    Draw4Points(xc,yc,x,y,ren);
    while(x*x*(a*a+b*b)<=a*a*a*a)
    {
        if(p<=0)
            p += 4*b*b*x + 6*b*b;
        else
        {
            p+= 4*b*b*x - 4*a*a*y + 4*a*a + 6*b*b;
            y--;
        }
        x++;
        Draw4Points(xc,yc,x,y, ren);
    }

    // Area 2
    x = a ;
    y = 0 ;
    p = b*b - 2*b*b*a + 2*a*a;
    Draw4Points(xc,yc,x,y, ren);
    while(x*x*(a*a+b*b)>=a*a*a*a)
    {
        if(p<=0)
            p += 4*a*a*y + 6*a*a;
        else
        {
            p += 4*a*a*y - 4*b*b*x + 4*b*b + 6*a*a;
            x--;
        }
        y++;
        Draw4Points(xc,yc,x,y, ren);
    }
}

void MidPointDrawEllipse(int xc, int yc, int a, int b, SDL_Renderer *ren)
{
    // Vùng 1
    int x = 0 ;
    int y = b ;
    int p = b*b - a*a*b+a*a/4;
    Draw4Points(xc,yc,x,y, ren);
    while(x*x*(a*a+b*b)<=a*a*a*a)
    {
        if(p<=0)
            p += 2*b*b*x + 3*b*b;
        else
        {
            p+= 2*b*b*x - 2*a*a*y + 2*a*a + 3*b*b;
            y--;
        }
        x++;
        Draw4Points(xc,yc,x,y, ren);
    }

    // Vùng 2
    x = a ;
    y = 0 ;
    p = a*a - b*b*a + b*b/4;
    Draw4Points(xc,yc,x,y, ren);
    while(x*x*(a*a+b*b)>=a*a*a*a)
    {
        if(p<=0)
            p += 2*a*a*y + 3*a*a;
        else
        {
            p += 2*a*a*y - 2*b*b*x + 2*b*b + 3*a*a;
            x--;
        }
        y++;
        Draw4Points(xc,yc,x,y, ren);
    }

}