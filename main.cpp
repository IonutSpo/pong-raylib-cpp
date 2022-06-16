#include "raylib.h"

struct AnimData
{   
    Texture2D texture;
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main() 
{   

    const int windowWidth{600};
    const int windowHeight{300};
    InitWindow(windowWidth, windowHeight, "Pong");

    AnimData ball;
    ball.texture = LoadTexture("textures/ball.png");
    ball.rec.width = ball.texture.width / 6;
    ball.rec.height = ball.texture.height;
    ball.rec.x = 0;
    ball.rec.y = 0;
    ball.pos.x = windowWidth / 2 - ball.rec.width / 2;
    ball.pos.y = windowHeight / 2 - ball.rec.height / 2;
    ball.frame = 0;
    ball.updateTime = 1.0/12.0;
    ball.runningTime = 0;
    
    AnimData leftPaddle;
    leftPaddle.texture = LoadTexture("textures/left_paddle.png");
    leftPaddle.rec.width = leftPaddle.texture.width;
    leftPaddle.rec.height = leftPaddle.texture.height;
    leftPaddle.rec.x = 0;
    leftPaddle.rec.y = 0;
    leftPaddle.pos.x = 0;
    leftPaddle.pos.y = windowHeight / 2 - leftPaddle.rec.height / 2;

    AnimData rightPaddle;
    rightPaddle.texture = LoadTexture("textures/right_paddle.png");
    rightPaddle.rec.width = rightPaddle.texture.width;
    rightPaddle.rec.height = rightPaddle.texture.height;
    rightPaddle.rec.x = 0;
    rightPaddle.rec.y = 0;
    rightPaddle.pos.x = windowWidth - rightPaddle.rec.width;
    rightPaddle.pos.y = windowHeight / 2 - rightPaddle.rec.height / 2;

    

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(BLACK);
        
        // delta time
        float dT{GetFrameTime()};
        
        ball.runningTime += dT;
        if (ball.runningTime >= ball.updateTime)
        {
            ball.runningTime = 0.0;
            
            // update ball animation frame
            ball.rec.x = ball.frame * ball.rec.width;
            ball.frame++;
            if (ball.frame > 5)
            {
                ball.frame = 0;
            }

        }

        // draw the ball
        DrawTextureRec(ball.texture, ball.rec, ball.pos, WHITE);
        DrawTextureRec(leftPaddle.texture, leftPaddle.rec, leftPaddle.pos, WHITE);
        DrawTextureRec(rightPaddle.texture, rightPaddle.rec, rightPaddle.pos, WHITE);

        EndDrawing();
        
    };

    UnloadTexture(ball.texture);
    UnloadTexture(leftPaddle.texture);
    UnloadTexture(rightPaddle.texture);
    CloseWindow();
}