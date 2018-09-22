#include "Bezier.h"
#include <iostream>
using namespace std;

void DrawCurve(std::vector<Vector2D> points, double t, SDL_Renderer *ren)
{
    double x, y;
    if (points.size() == 1)
        SDL_RenderDrawPoint(ren,points.at(0).x, points.at(0).y);
    else
    {
        std::vector<Vector2D> newPoints(points.size() - 1);
        for (int i = 0; i < newPoints.size(); i++)
        {
            x = (1 - t) * points.at(i).x + t * points.at(i + 1).x;
            y = (1 - t) * points.at(i).y + t * points.at(i + 1).y;

            newPoints.at(i) = Vector2D(x, y);
        }
        DrawCurve(newPoints, t, ren);
    }
}

void DrawCurve2(SDL_Renderer *ren, Vector2D p1, Vector2D p2, Vector2D p3)
{
    std::vector<Vector2D> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    double t;

    for (t = 0;t <= 1; t+= 0.0001)
        DrawCurve(points, t, ren);

}
void DrawCurve3(SDL_Renderer *ren, Vector2D p1, Vector2D p2, Vector2D p3, Vector2D p4)
{
    std::vector<Vector2D> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    double t;

    for (t = 0;t <= 1; t+= 0.0001)
        DrawCurve(points, t, ren);
}


