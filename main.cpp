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
    leftPaddle.velocity = 120;

    Paddle rightPaddle;
    rightPaddle.texture = LoadTexture("textures/right_paddle.png");
    rightPaddle.rec.width = rightPaddle.texture.width;
    rightPaddle.rec.height = rightPaddle.texture.height;
    rightPaddle.rec.x = 0;
    rightPaddle.rec.y = 0;
    rightPaddle.pos.x = windowWidth - rightPaddle.rec.width;
    rightPaddle.pos.y = windowHeight / 2 - rightPaddle.rec.height / 2;
    rightPaddle.velocity = 120;

    Texture2D table = LoadTexture("textures/background.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(BLACK);

        // draw the table (background) raylib doesn't render it...
        DrawTextureEx(table, Vector2{0.0, 0.0}, 0.0, 0.0, WHITE);

        // draw the ball and paddles
        DrawTextureRec(ball.texture, ball.rec, ball.pos, WHITE);
        DrawTextureRec(leftPaddle.texture, leftPaddle.rec, leftPaddle.pos, WHITE);
        DrawTextureRec(rightPaddle.texture, rightPaddle.rec, rightPaddle.pos, WHITE);
         
        // delta time
        float dT{GetFrameTime()};

        // move the ball 
        ball.pos.x += ball.velocityX * dT;
        ball.pos.y += ball.velocityY * dT;

        // check if the ball left the screen and declare a winner
        if (ball.pos.x < -ball.rec.width)
        {      
            leftPaddle.pos.x = 0;
            leftPaddle.pos.y = windowHeight / 2 - leftPaddle.rec.height / 2;

            rightPaddle.pos.x = windowWidth - rightPaddle.rec.width;
            rightPaddle.pos.y = windowHeight / 2 - rightPaddle.rec.height / 2;

            DrawText("Right Player Wins!", windowWidth / 2 - MeasureText("Right Player Wins!", 30) / 2, windowHeight / 2, 30, RED);
        }
        if (ball.pos.x > windowWidth + ball.rec.width)
        {   
            leftPaddle.pos.x = 0;
            leftPaddle.pos.y = windowHeight / 2 - leftPaddle.rec.height / 2;

            rightPaddle.pos.x = windowWidth - rightPaddle.rec.width;
            rightPaddle.pos.y = windowHeight / 2 - rightPaddle.rec.height / 2;

            DrawText("Left Player Wins!", windowWidth / 2 - MeasureText("Left Player Wins!", 30) / 2, windowHeight / 2, 30, RED);
        }
       
        // check collision between ball and the paddles
        float pad{20};

        Rectangle ballRec
        {
            ball.pos.x + (pad/2),
            ball.pos.y + (pad/2),
            ball.rec.width - pad,
            ball.rec.height - pad
        };
        
        Rectangle leftPaddleRec
        {
           leftPaddle.pos.x + pad,
           leftPaddle.pos.y + pad,
           leftPaddle.rec.width - 2*pad,
           leftPaddle.rec.height - 2*pad
        };

        Rectangle rightPaddleRec
        {
            rightPaddle.pos.x + pad,
            rightPaddle.pos.y + pad,
            rightPaddle.rec.width - 2*pad,
            rightPaddle.rec.height - 2*pad
        };

        if (CheckCollisionRecs(ballRec, rightPaddleRec)) 
        {
            if (ball.velocityX > 0)
            {
                ball.velocityX *= -1;
            }
        }
    
        if (CheckCollisionRecs(ballRec, leftPaddleRec))
        {
            if (ball.velocityX < 0)
            {
                ball.velocityX *= -1.1;
            }
        }

        // check if the ball goes off the screen
        if (ball.pos.y < -20 + ball.rec.height / 2)
        {   
            ball.pos.y = -20 + ball.rec.height;
            ball.velocityY *= -1;
        }
        if (ball.pos.y > windowHeight - ball.rec.height / 2)
        {   
            ball.pos.y = windowHeight - ball.rec.height;
            ball.velocityY *= -1;
        }

        // move the paddles
        if (IsKeyDown(KEY_A) && leftPaddle.pos.y >= -pad) leftPaddle.pos.y -= leftPaddle.velocity * dT;

        if (IsKeyDown(KEY_D) && leftPaddle.pos.y <= windowHeight - rightPaddle.rec.height + pad) leftPaddle.pos.y += leftPaddle.velocity * dT;
       
        if (IsKeyDown(KEY_UP) && rightPaddle.pos.y >= -pad) rightPaddle.pos.y -= rightPaddle.velocity * dT;

        if (IsKeyDown(KEY_DOWN) && rightPaddle.pos.y <= windowHeight - rightPaddle.rec.height + pad) rightPaddle.pos.y += rightPaddle.velocity * dT;
        
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

        EndDrawing();
        
    };

    UnloadTexture(ball.texture);
    UnloadTexture(leftPaddle.texture);
    UnloadTexture(rightPaddle.texture);
    UnloadTexture(table);
    CloseWindow();
}