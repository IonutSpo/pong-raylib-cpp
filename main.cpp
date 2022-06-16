#include "raylib.h"

struct Ball
{   
    Texture2D texture;
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
    float velocityX;
    float velocityY;
};

struct Paddle
{
    Texture2D texture;
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
    float velocity;
};

int main() 
{   

    const int windowWidth{600};
    const int windowHeight{300};
    InitWindow(windowWidth, windowHeight, "Pong");

    Ball ball;
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
    ball.velocityX = 150;
    ball.velocityY = 150;
    
    Paddle leftPaddle;
    leftPaddle.texture = LoadTexture("textures/left_paddle.png");
    leftPaddle.rec.width = leftPaddle.texture.width;
    leftPaddle.rec.height = leftPaddle.texture.height;
    leftPaddle.rec.x = 0;
    leftPaddle.rec.y = 0;
    leftPaddle.pos.x = 0;
    leftPaddle.pos.y = windowHeight / 2 - leftPaddle.rec.height / 2;
    leftPaddle.velocity = 80;

    Paddle rightPaddle;
    rightPaddle.texture = LoadTexture("textures/right_paddle.png");
    rightPaddle.rec.width = rightPaddle.texture.width;
    rightPaddle.rec.height = rightPaddle.texture.height;
    rightPaddle.rec.x = 0;
    rightPaddle.rec.y = 0;
    rightPaddle.pos.x = windowWidth - rightPaddle.rec.width;
    rightPaddle.pos.y = windowHeight / 2 - rightPaddle.rec.height / 2;
    rightPaddle.velocity = 80;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(BLACK);
        
        // delta time
        float dT{GetFrameTime()};

        // move the ball 
        ball.pos.x += ball.velocityX * dT;
        ball.pos.y += ball.velocityY * dT;

        // check if the ball goes off the screen
        if (ball.pos.y < 0 + ball.rec.height / 2)
        {   
            ball.pos.y = 0 + ball.rec.height;
            ball.velocityY *= -1;
        }
        if (ball.pos.y > windowHeight - ball.rec.height / 2)
        {   
            ball.pos.y = windowHeight - ball.rec.height;
            ball.velocityY *= -1;
        }

        // move the paddles
        if (IsKeyDown(KEY_A)) leftPaddle.pos.y -= leftPaddle.velocity * dT;
      
        if (IsKeyDown(KEY_D)) leftPaddle.pos.y += leftPaddle.velocity * dT;
       
        if (IsKeyDown(KEY_UP)) rightPaddle.pos.y -= rightPaddle.velocity * dT;

        if (IsKeyDown(KEY_DOWN)) rightPaddle.pos.y += rightPaddle.velocity * dT;
        
        ball.runningTime += dT;
        if (ball.runningTime >= ball.updateTime)
        {
            ball.runningTime = 0.0;
            
            // update ball animation frames
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