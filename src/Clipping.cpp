#include "Clipping.h"
#include <iostream>

RECT CreateWindow(int l, int r, int t, int b)
{
    RECT rect;
    rect.Left = l;
    rect.Right = r;
    rect.Top = t;
    rect.Bottom = b;

    return rect;
}

CODE Encode(RECT r, Vector2D P)
{
    CODE c = 0;
    if (P.x < r.Left)
        c = c|LEFT;
    if (P.x > r.Right)
        c = c|RIGHT;
    if (P.y < r.Top)
        c = c|TOP;
    if (P.y > r.Bottom)
        c = c|BOTTOM;
    return c;
}

int CheckCase(int c1, int c2)
{
    if (c1 == 0 && c2 == 0)
        return 1;
    if ((c1 != 0) && (c2 != 0) && ((c1&c2) != 0))
        return 2;
    return 3;
}

int CohenSutherland(RECT r, Vector2D P1, Vector2D P2, Vector2D &Q1, Vector2D &Q2)
{
    int c1 = Encode(r, P1);
    int c2 = Encode(r, P2);
    int checkCase = CheckCase(c1, c2);

    while (checkCase == 3)
    {
        ClippingCohenSutherland(r, P1, P2);
        c1 = Encode(r, P1);
        c2 = Encode(r, P2);
        checkCase = CheckCase(c1, c2);
    }

    if (checkCase == 2)
        return 0;

    Q1.set(P1);
    Q2.set(P2);
    return 1;

}

void ClippingCohenSutherland(RECT r, Vector2D &P1, Vector2D &P2)
{
    if (Encode(r, P1) == 0)
    {
        Vector2D temp(P1);
        P1.set(P2);
        P2.set(temp);
    }

    int c1 = Encode(r, P1);
    int c2 = Encode(r, P2);
    int dx = P2.x - P1.x;
    int dy = P2.y - P1.y;
    float m;

    if (dx != 0)
        m = (float)dy/dx;

    if ((c1 & LEFT) != 0)
    {
        P1.y += m * (r.Left - P1.x);
        P1.x = r.Left;
        return;
    }

    if ((c1 & RIGHT) != 0)
    {
        P1.y += m * (r.Right - P1.x);
        P1.x = r.Right;
        return;
    }

    if ((c1 & TOP) != 0)
    {
        if (dx != 0)
            P1.x += (r.Top - P1.y)/m;
        P1.y = r.Top;
        return;
    }

    if ((c1 & BOTTOM) != 0)
    {
        if (dx != 0)
            P1.x += (r.Bottom - P1.y)/m;
        P1.y = r.Bottom;
        return;
    }

}

int SolveNonLinearEquation(int p, int q, float &t1, float &t2)
{
    if (p == 0)
    {
        if (q < 0)
            return 0;
        return 1;
    }

    if (p > 0)
    {
        float t=(float)q/p;
        if(t2<t)
            return 1;
        if(t<t1)
            return 0;
        t2 = t;
        return 1;
    }

    float t=(float)q/p;
    if(t2<t)
        return 0;
    if(t<t1)
        return 1;
    t1 = t;
    return 1;
}

int LiangBarsky(RECT r, Vector2D P1, Vector2D P2, Vector2D &Q1, Vector2D &Q2)
{
    int Dx = P2.x-P1.x;
    int Dy = P2.y-P1.y;
    int xmin = r.Left;
    int xmax = r.Right;
    int ymin = r.Top;
    int ymax = r.Bottom;
    int p1 = -Dx;
    int p2 = Dx;
    int p3 = -Dy;
    int p4 = Dy;

    int q1 = P1.x-xmin;
    int q2 = xmax-P1.x;
    int q3 = P1.y-ymin;
    int q4 = ymax-P1.y;
    float t1 = 0;
    float t2 = 1;

    int a = SolveNonLinearEquation(p1,q1,t1,t2);
    int b = SolveNonLinearEquation(p2,q2,t1,t2);
    int c = SolveNonLinearEquation(p3,q3,t1,t2);
    int d = SolveNonLinearEquation(p4,q4,t1,t2);

    if(a*b*c*d==0)
        return 0;

    Q1.x = P1.x + int(t1*Dx+0.5);
    Q1.y = P1.y + int(t1*Dy+0.5);
    Q2.x = P1.x + int(t2*Dx+0.5);
    Q2.y = P1.y + int(t2*Dy+0.5);

    return 1;

}
