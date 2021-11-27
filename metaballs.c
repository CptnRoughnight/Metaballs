#include "raylib.h"
#include <stdlib.h>

unsigned int screenWidth = 320;
unsigned int screenHeight = 240;

#define ligma 10     // balls

Camera2D camera;

struct BALL{
        float x;
        float y;
        float dx;
        float dy;
        float radius;
        float r;
        float g;
        float b;
};
struct BALL balls[ligma];

float calcDistance(int x,int y,int i)
{
    return sqrt(pow(balls[i].x-x,2) + 
                pow(balls[i].y-y,2)*1.0f);
}
    
void initBalls()
{
    for (unsigned int i=0;i<ligma;i++)
    {
        struct BALL b;
        b.x = rand()%screenWidth;
        b.y = rand()%screenHeight;
        b.dx = ((float)rand()/(float)(RAND_MAX)) * 2;
        b.dy = ((float)rand()/(float)(RAND_MAX)) * 3;

        b.radius = rand()%120;
        unsigned int color = rand()%4;
        switch (color)
        {
            case 0:
                b.r = 255;
                b.g = 0;
                b.b = 0;
            break;
            
            case 1:
                b.g = 255;
                b.r = 0;
                b.b = 0;
            break;
            
            case 2:
                b.b = 255;
                b.r = 0;
                b.b = 0;
            break;
            
            default:
                b.g = 255;
                b.r = 0;
                b.b = 255;
            break; 
            }
        balls[i] = b;
    }
}

void update()
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    
    for (int x=0;x<screenWidth;x++)
        for (int y=0;y<screenHeight;y++)
        {
            float sumr=0.0;
            float sumg=0.0;
            float sumb=0.0f;
            for (int i=0;i<ligma;i++)
            {
                sumr += (balls[i].r / calcDistance(x,y,i)*10.0);
                sumg += (balls[i].g / calcDistance(x,y,i)*10.0);
                sumb += (balls[i].b / calcDistance(x,y,i)*10.0);
            }   
            if (sumr>255)
                sumr=255;
            if (sumg>255)
                sumg=255;
            if (sumb>255)
                sumb=255;

            DrawPixel(x,y,(Color){(unsigned char)sumr,(unsigned char)sumg,(unsigned char)sumb,255});
        }
        for (int i=0;i<ligma;i++)
        {
            balls[i].x += balls[i].dx;
            balls[i].y += balls[i].dy;
            if ((balls[i].x > screenWidth)||(balls[i].x < 0))
                balls[i].dx = -balls[i].dx;
            if ((balls[i].y > screenHeight)||(balls[i].y < 0))
                balls[i].dy = -balls[i].dy;
        }
    
    EndMode2D();
    EndDrawing();
}

int main (void)
{
    InitWindow(screenWidth, screenHeight, "raylib");
    SetTargetFPS(60);
    HideCursor();
    
    camera.offset= (Vector2) {0,0};
    camera.target = (Vector2) {0,0};
    camera.rotation = 0;
    camera.zoom = 1.0;
    
    initBalls();
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        update();
    }

    return 0;
}    
    