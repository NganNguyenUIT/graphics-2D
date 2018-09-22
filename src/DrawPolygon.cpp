#include "DrawPolygon.h"
#include <iostream>
using namespace std;

void DrawEquilateralTriangle(int xc, int yc, int R, SDL_Renderer *ren)
{
    int x[3];
    int y[3];
    float phi = M_PI_2;
    int i;

    for (i = 0; i < 3; i++)
    {
        x[i] = xc + int(R*cos(phi)+0.5);
        y[i] = yc - int(R*sin(phi)+0.5);
        phi += 2 * M_PI/3;
    }

    cout << x[0] << y[0] << endl;
    cout << x[1] << y[1] << endl;

    for (i = 0; i < 3; i++)
        Midpoint_Line(x[i],y[i],x[(i+1)%3],y[(i+1)%3], ren);
}

void DrawSquare(int xc, int yc, int R, SDL_Renderer *ren)
{
    int x[4];
    int y[4];
    float phi = M_PI_4;
    int i;

    for (i = 0; i < 4; i++)
    {
        x[i] = xc + int(R*cos(phi)+0.5);
        y[i] = yc - int(R*sin(phi)+0.5);
        phi += 2 * M_PI_4;
    }

    for (i = 0; i < 4; i++)
        Midpoint_Line(x[i],y[i],x[(i+1)%4],y[(i+1)%4], ren);
}
void DrawPentagon(int xc, int yc, int R, SDL_Renderer *ren)
{
    int x[5];
    int y[5];
    float phi = M_PI_2;
    int i;

    for (i = 0; i < 5; i++)
    {
        x[i] = xc + int(R*cos(phi)+0.5);
        y[i] = yc - int(R*sin(phi)+0.5);
        phi += 2 * M_PI/5;
    }

    for (i = 0; i < 5; i++)
        Midpoint_Line(x[i],y[i],x[(i+1)%5],y[(i+1)%5], ren);
}
void DrawHexagon(int xc, int yc, int R, SDL_Renderer *ren)
{
    int x[6];
    int y[6];
    float phi = 0;
    int i;

    for (i = 0; i < 6; i++)
    {
        x[i] = xc + int(R*cos(phi)+0.5);
        y[i] = yc - int(R*sin(phi)+0.5);
        phi += 2 * M_PI/6;
    }

    for (i = 0; i < 6; i++)
        Midpoint_Line(x[i],y[i],x[(i+1)%6],y[(i+1)%6], ren);
}

void DrawStar(int xc, int yc, int R, SDL_Renderer *ren)
{
    int x[5];
    int y[5];
    float phi = M_PI_2;
    int i;

    for (i = 0; i < 5; i++)
    {
        x[i] = xc + int(R*cos(phi)+0.5);
        y[i] = yc - int(R*sin(phi)+0.5);
        phi += 2 * M_PI/5;
    }

    for (i = 0; i < 5; i++)
        Midpoint_Line(x[i],y[i],x[(i+2)%5],y[(i+2)%5], ren);

}

void DrawEmptyStar(int xc, int yc, int R, SDL_Renderer *ren)
{
    int x[5], xp[5];
    int y[5], yp[5];
    float phi = M_PI_2;
    float rnho = R*sin(M_PI/10)/sin(7*M_PI/10);
    int i;

    for(i=0; i<5; i++)
    {
        x[i] = xc+int(R*cos(phi)+0.5);
        y[i] = yc-int(R*sin(phi)+0.5);
        xp[i] = xc+int(rnho*cos(phi+M_PI/5)+0.5);
        yp[i] = yc-int(rnho* sin(phi+M_PI/5)+0.5);
        phi += 2*M_PI/5;
    }

    for (i = 0; i < 5; i++)
    {
        x[i] = xc + int(R*cos(phi)+0.5);
        y[i] = yc - int(R*sin(phi)+0.5);
        phi += 2 * M_PI/5;
    }

    for (i = 0; i < 5; i++)
    {
        Midpoint_Line(x[i],y[i],xp[i],yp[i], ren);
        Midpoint_Line(xp[i],yp[i],x[(i+1)%5],y[(i+1)%5], ren);
    }

}

void DrawStarEight(int xc, int yc, int R, SDL_Renderer *ren)
{
    int x[8], xp[8];
    int y[8], yp[8];
    float phi = 0;
    float rnho = R*sin(M_PI/8)/sin(6*M_PI/8);
    int i;

    for(i=0; i<8; i++)
    {
        x[i] = xc+int(R*cos(phi)+0.5);
        y[i] = yc-int(R*sin(phi)+0.5);
        xp[i] = xc+int(rnho*cos(phi+M_PI/8)+0.5);
        yp[i] = yc-int(rnho* sin(phi+M_PI/8)+0.5);
        phi += 2*M_PI/8;
    }

    for(i=0; i<8; i++)
    {
        Midpoint_Line(x[i],y[i],xp[i],yp[i], ren);
        Midpoint_Line(xp[i],yp[i],x[(i+1)%8],y[(i+1)%8], ren);
    }

}

void DrawStarAngle(int xc, int yc, int R, float startAngle, SDL_Renderer *ren)
{
    int x[5], xp[5];
    int y[5], yp[5];
    float phi = startAngle;
    float rnho = R*sin(M_PI/10)/sin(7*M_PI/10);
    int i;

    for(i=0; i<5; i++)
    {
        x[i] = xc+int(R*cos(phi)+0.5);
        y[i] = yc-int(R*sin(phi)+0.5);
        xp[i] = xc+int(rnho*cos(phi+M_PI/5)+0.5);
        yp[i] = yc-int(rnho* sin(phi+M_PI/5)+0.5);
        phi += 2*M_PI/5;
    }

    for(i=0; i<5; i++)
    {
        Midpoint_Line(x[i],y[i],xp[i],yp[i], ren);
        Midpoint_Line(xp[i],yp[i],x[(i+1)%5],y[(i+1)%5], ren);
    }


}

void DrawConvergentStar(int xc, int yc, int r, SDL_Renderer *ren)
{
    float radius = r;
    float startAngle = M_PI_2;
    while(radius>1)
    {
        DrawStarAngle(xc,yc,int(radius+0.5),startAngle, ren);
        startAngle = startAngle + M_PI;
        radius = radius*sin(M_PI/10)/sin(7*M_PI/10);
    }


}