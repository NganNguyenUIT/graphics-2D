#include <iostream>
#include <SDL.h>
#include "Line.h"
#include "Clipping.h"
#include "DrawPolygon.h"
#include "FillColor.h"

using namespace std;

const int WIDTH  = 800;
const int HEIGHT = 600;


int main(int, char**){
    //First we need to start up SDL, and make sure it went ok
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    //Make sure creating our window went ok
    if (win == NULL){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //Create a renderer that will draw to the window, -1 specifies that we want to load whichever
    //DON'T FORGET CHANGE THIS LINE IN YOUR SOURCE ----->>>>> SDL_RENDERER_SOFTWARE

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Set the blend mode to specify how the alpha channel is used
    if (SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND) != 0) {
        std::cout << "\"Could not set render draw blend mode: " << SDL_GetError() << std::endl;
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    //YOU CAN INSERT CODE FOR TESTING HERE

    //Get pixel format of the window
    Uint32 pixel_format = SDL_GetWindowPixelFormat(win);

    //Set alpha channel = 255
    SDL_Color fillColor = {36, 113, 163, 255};
    SDL_Color boundaryColor = {255, 255, 0, 255};

    //Draw a rectangle then fill it from startPoint by calling BoundaryFill4
    SDL_Rect *rect1 = new SDL_Rect();
    rect1->x = 0;
    rect1->y = 0;
    rect1->w = 100;
    rect1->h = 10;
    //Filling edges by boundary color
    SDL_SetRenderDrawColor(ren, boundaryColor.r, boundaryColor.g, boundaryColor.b, boundaryColor.a);
    SDL_RenderDrawRect(ren, rect1);

    Vector2D startPoint(2, 2);
    BoundaryFill4(win, startPoint, pixel_format, ren, fillColor, boundaryColor);

    //Three vertices for triangle
    Vector2D v1(200, 100);
    Vector2D v2(150, 400);
    Vector2D v3(400, 300);

    //Filling triangle by calling TriangleFill
    //TriangleFill(v1, v2, v3, ren, fillColor);

    int xc = 200;
    int yc = 200;
    int R = 100;


    FillIntersectionRectangleCircle(v1, v2, xc, yc, R, ren, fillColor);

    SDL_Delay(5000);
    SDL_RenderPresent(ren);

    //Take a quick break after all that hard work
    //Quit if happen QUIT event
    bool running = true;

    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT: running = false; break;
            }

        }

    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
