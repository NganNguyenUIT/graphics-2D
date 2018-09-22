#include "FillColor.h"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

#define INT_SIZE sizeof(Uint32) * 8 /* Integer size in bits */

int findHighestBitSet(Uint32 num)
{
    int order = 0, i;

    /* Iterate over each bit of integer */
    for(i=0; i<INT_SIZE; i++)
    {
        /* If current bit is set */
        if((num>>i) & 1)
            order = i;
    }

    return order;
}

//Get color of a pixel
SDL_Color getPixelColor(Uint32 pixel_format, Uint32 pixel)
{
    SDL_PixelFormat* fmt = SDL_AllocFormat(pixel_format);

    Uint32 temp;
    Uint8 red, green, blue, alpha;

    //Check if pixel is a 32-bit integer
    if (findHighestBitSet(pixel) == 31)
    {
        /* Get Alpha component */
        temp = pixel & fmt->Amask;  /* Isolate alpha component */
        temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
        temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
        alpha = (Uint8)temp;
    } else {
        alpha = 255;
    }

    /* Get Red component */
    temp = pixel & fmt->Rmask;  /* Isolate red component */
    temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
    red = (Uint8)temp;

    /* Get Green component */
    temp = pixel & fmt->Gmask;  /* Isolate green component */
    temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
    green = (Uint8)temp;

    /* Get Blue component */
    temp = pixel & fmt->Bmask;  /* Isolate blue component */
    temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
    blue = (Uint8)temp;


    SDL_Color color = {red, green, blue, alpha};
    return color;

}

//Get all pixels on the window
SDL_Surface* getPixels(SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
    SDL_Surface* saveSurface = NULL;
    SDL_Surface* infoSurface = NULL;
    infoSurface = SDL_GetWindowSurface(SDLWindow);
    if (infoSurface == NULL) {
        std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
        return NULL;
    } else {
        unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
        if (pixels == 0) {
            std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
            return NULL;
        } else {
            if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
                std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
                return NULL;
            } else {
                saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                // Set the blend mode to specify how the alpha channel is used
                if (SDL_SetRenderDrawBlendMode(SDLRenderer, SDL_BLENDMODE_BLEND) != 0) {
                    std::cout << "\"saveSurface: Could not set render draw blend mode: " << SDL_GetError() << std::endl;
                }
            }
        }
    }
    return saveSurface;
}

//Compare two colors
bool compareTwoColors(SDL_Color color1, SDL_Color color2)
{
    if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b && color1.a == color2.a)
        return true;
    return false;
}


bool canFilled(SDL_Window *win, Vector2D newPoint,Uint32 pixel_format,
               SDL_Renderer *ren, SDL_Color fillColor, SDL_Color boundaryColor)
{
    SDL_Surface *surface = getPixels(win, ren);

    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int w = surface->w;

    int index = newPoint.y * w + newPoint.x;
    Uint32 pixel = pixels[index];
    SDL_Color color = getPixelColor(pixel_format, pixel);
    cout << (int)color.r << "," << (int)color.g << "," << (int)color.b << "," << (int)color.a << endl;

    if (!compareTwoColors(color, fillColor) && !compareTwoColors(color, boundaryColor))
    {
        delete surface;
        return true;
    }

    delete surface;
    return false;
}

void BoundaryFill4(SDL_Window *win, Vector2D startPoint,Uint32 pixel_format,
                   SDL_Renderer *ren, SDL_Color fillColor, SDL_Color boundaryColor)
{
    int xStop, yStop;
    SDL_GetWindowSize(win, &xStop, &yStop);

    SDL_Surface *surface = getPixels(win, ren);

    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int w = surface->w;

    stack<Vector2D> stackP;

    Vector2D newPoint;
    Vector2D currentPoint = startPoint;
    bool canPass = false;

    int index = currentPoint.y * w + currentPoint.x;
    Uint32 pixel = pixels[index];
    SDL_Color color = getPixelColor(pixel_format, pixel);


    if (compareTwoColors(color, fillColor) || compareTwoColors(color, boundaryColor))
        return;

    if (!compareTwoColors(color, fillColor) && !compareTwoColors(color, boundaryColor))
    {
        stackP.push(currentPoint);
    }

    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);

    cout << "END START POINT" << endl;

    while (!stackP.empty() && currentPoint.x >= 0 && currentPoint.y >= 0 && currentPoint.x < xStop && currentPoint.y < yStop)
    {
        currentPoint = stackP.top();

        SDL_RenderDrawPoint(ren, currentPoint.x, currentPoint.y);

        newPoint.set(currentPoint.x - 1, currentPoint.y);

        if (canFilled(win, newPoint, pixel_format, ren, fillColor, boundaryColor))
        {
            stackP.push(newPoint);
            cout << newPoint;
            continue;
        }

        newPoint.set(currentPoint.x + 1, currentPoint.y);
        if (canFilled(win, newPoint, pixel_format, ren, fillColor, boundaryColor))
        {
            stackP.push(newPoint);
            cout << newPoint;
            continue;
        }

        newPoint.set(currentPoint.x, currentPoint.y - 1);
        if (canFilled(win, newPoint, pixel_format, ren, fillColor, boundaryColor))
        {
            stackP.push(newPoint);
            cout << newPoint;
            continue;
        }

        newPoint.set(currentPoint.x, currentPoint.y + 1);
        if (canFilled(win, newPoint, pixel_format, ren, fillColor, boundaryColor))
        {
            stackP.push(newPoint);
            cout << newPoint;
            continue;
        }

        stackP.pop();
    }
}

//======================================================================================================================
//=============================================FILLING TRIANGLE=========================================================

int maxIn3(int a, int b, int c)
{
    int lc = a;
    if (b > lc)
        c = b;
    if (c > lc)
        lc = c;
    return lc;
}

int minIn3(int a, int b, int c)
{
    int lc = a;
    if (b < lc)
        c = b;
    if (c < lc)
        lc = c;
    return lc;
}

void swap(Vector2D &a, Vector2D &b)
{
    Vector2D temp(a);
    a.set(b);
    b.set(temp);
}

void ascendingSort(Vector2D &v1, Vector2D &v2, Vector2D &v3)
{
    if (v1.y > v2.y) {
        swap(v1, v2);
    }

    if(v1.y > v3.y)
    {
        swap(v1, v3);
    }

    if(v2.y > v3.y)
    {
        swap(v2, v3);
    }
}

void TriangleFill1(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
    int xmin = minIn3(v1.x, v2.x, v3.x);
    cout << xmin << endl;
    int xmax = maxIn3(v1.x, v2.x, v3.x);
    cout << xmax << endl;
    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    Midpoint_Line(xmin, v1.y, xmax, v1.y, ren);
}

void TriangleFill2(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
    float const1 = (float)(v3.x - v1.x)/(v3.y - v1.y);
    float const2 = (float)(v3.x - v2.x)/(v3.y - v2.y);

    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    float xLeft = v1.x;
    float xRight = v2.x;

    for (int y = v1.y; y <= v3.y; y++)
    {
        xLeft += const1;
        xRight += const2;
        Midpoint_Line(int(xLeft + 0.5), y, int(xRight + 0.5), y, ren);
    }
}

void TriangleFill3(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
    float const1 = (float)(v2.x - v1.x)/(v2.y - v1.y);
    float const2 = (float)(v3.x - v1.x)/(v3.y - v1.y);

    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    float xLeft = v1.x;
    float xRight = v1.x;

    for (int y = v1.y; y <= v3.y; y++)
    {
        xLeft += const1;
        xRight += const2;
        Midpoint_Line(int(xLeft + 0.5), y, int(xRight + 0.5), y, ren);
    }
}

void TriangleFill4(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
    float const1 = (float)(v2.x - v1.x)/(v2.y - v1.y);
    float const2 = (float)(v3.x - v1.x)/(v3.y - v1.y);
    int y;

    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    float xLeft = v1.x;
    float xRight = v1.x;

    for (y = v1.y; y <= v2.y; y++)
    {
        xLeft += const1;
        xRight += const2;
        Midpoint_Line(int(xLeft + 0.5), y, int(xRight + 0.5), y, ren);
    }

    const1 = (float)(v3.x - v2.x)/(v3.y - v2.y);
    for (;y <= v3.y; y++)
    {
        xLeft += const1;
        xRight += const2;
        Midpoint_Line(int(xLeft + 0.5), y, int(xRight + 0.5), y, ren);
    }
}

void TriangleFill(Vector2D v1, Vector2D v2, Vector2D v3, SDL_Renderer *ren, SDL_Color fillColor)
{
    ascendingSort(v1, v2, v3);

    if (v1.y == v2.y && v2.y == v3.y)
    {
        TriangleFill1(v1, v2, v3, ren, fillColor);
        return;
    }

    if (v1.y == v2.y && v2.y < v3.y)
    {
        TriangleFill2(v1, v2, v3, ren, fillColor);
        return;
    }

    if (v1.y < v2.y && v2.y == v3.y)
    {
        TriangleFill3(v1, v2, v3, ren, fillColor);
        return;
    }

    TriangleFill4(v1, v2, v3, ren, fillColor);
    return;
}
//======================================================================================================================
//===================================CIRCLE - RECTANGLE - ELLIPSE=======================================================
bool isInsideCircle(int xc, int yc, int R, int x, int y)
{
    if((x-xc)*(x-xc) + (y-yc)*(y-yc) <= R*R)
        return true;
    return false;
}

void FillIntersection(int x1,int y1,int x2,int y2, int xc, int yc, int R,
                      SDL_Renderer *ren, SDL_Color fillColor)
{
    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    int xmin = min(x1, x2);
    int xmax = max(x1, x2);

    for(int x = xmin;x <= xmax; x++)
        if(isInsideCircle(xc,yc,R,x,y1)==1)
            SDL_RenderDrawPoint(ren, x, y1);

}

void FillIntersectionRectangleCircle(Vector2D vTopLeft, Vector2D vBottomRight, int xc, int yc, int R,
                                     SDL_Renderer *ren, SDL_Color fillColor)
{

    for(int y = vTopLeft.y;y <= vBottomRight.y; y++)
        FillIntersection(vTopLeft.x, y, vBottomRight.x, y, xc, yc, R, ren, fillColor);

}

void RectangleFill(Vector2D vTopLeft, Vector2D vBottomRight, SDL_Renderer *ren, SDL_Color fillColor)
{
    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    for (int y = vTopLeft.y; y <= vBottomRight.y; y++)
        Midpoint_Line(vTopLeft.x, y, vBottomRight.x, y, ren);
}

void put4line(int xc, int yc, int x, int y, SDL_Renderer *ren, SDL_Color fillColor)
{
    SDL_SetRenderDrawColor(ren, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    Midpoint_Line(xc + x, yc + y, xc - x, yc + y, ren);
    Midpoint_Line(xc + y, yc + x, xc - y, yc + x, ren);
    Midpoint_Line(xc + y, yc - x, xc - y, yc - x, ren);
    Midpoint_Line(xc + x, yc - y, xc - x, yc - y, ren);
}

void CircleFill(int xc, int yc, int R, SDL_Renderer *ren, SDL_Color fillColor)
{
    int x = 0;
    int y = R;
    int p = 1 - R;
    put4line(xc, yc, x, y, ren, fillColor);
    while(x < y)
    {
        if (p < 0)
            p += 2*x + 3;
        else
        {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
        put4line(xc, yc, x, y, ren, fillColor);
    }
}

void FillIntersectionEllipseCircle(int xcE, int ycE, int a, int b, int xc, int yc, int R, SDL_Renderer *ren, SDL_Color fillColor)
{
}

void FillIntersectionTwoCircles(int xc1, int yc1, int R1, int xc2, int yc2, int R2, SDL_Renderer *ren, SDL_Color fillColor)
{
}
