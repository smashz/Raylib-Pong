#include <raylib.h>
#include "objects.h"
#include <stdio.h>
//#include "objects.cpp"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "PONG - [raylib]");

    
    
    Ball ball;
    Walls player;
    Walls cpu;

    // lOAD RECTANGLES ********
    Rectangle playerRect = { player.playerRecX, player.RecY, player.recWidth, player.recHeight }; 
    Rectangle cpuRect = { cpu.cpuRecX, cpu.RecY, cpu.recWidth, cpu.recHeight }; 
    ///************************

    //bool recCollision = CheckCollisionCircleRec(ball.Position, ball.Radius, playerRect);

    bool pause = 1;
    bool started = 1;
    int framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;



        if (!pause)
        {

            // Player Movement
            if (IsKeyDown(KEY_DOWN)) {
                playerRect.y += 5;
            } 
            if (IsKeyDown(KEY_UP)) {
                playerRect.y -= 5;
            }    
            //*******************

            // CPU Movement
            if (IsKeyDown(KEY_RIGHT)) {
                cpuRect.y += 5;
            } 
            if (IsKeyDown(KEY_LEFT)) {
                cpuRect.y -= 5;
            }    
            //*******************

            ball.Position.x += ball.Speed.x;
            ball.Position.y += ball.Speed.y;

            // Check x.walls collision for bouncing
            if ((ball.Position.x >= (GetScreenWidth() - ball.Radius)) || (ball.Position.x <= ball.Radius))
            {
                //ball.Speed.x *= -1;
                if(ball.Speed.x < 0){
                    player.Score++;
                }
                if(ball.Speed.x > 0){
                    cpu.Score++;
                }

                ball.Position = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};

            } 
            if ((ball.Position.y >= (GetScreenHeight() - ball.Radius)) || (ball.Position.y <= ball.Radius))
            {
                ball.Speed.y *= -1;
            } 
            if (CheckCollisionCircleRec(ball.Position, ball.Radius, playerRect)){ // player collison
        
            
            if (ball.Position.x < playerRect.x || ball.Position.x > playerRect.x + playerRect.width) { // check if ball.Position on the x axis is less than x axis of Rectangle
                // or if ball position on the x axis is greater than rectangle x axis + width to detetected bottom hits
                ball.Speed.x *= -1; // Reverse X velocity if the ball hits the left or right side of the rectangle
            }

            if (ball.Position.y < playerRect.y || ball.Position.y > playerRect.y + playerRect.height) {
                ball.Speed.y *= -1; // Reverse Y velocity if the ball hits the top or bottom side of the rectangle
            }
            
            if(ball.Position.x <= playerRect.x || ball.Position.y <= playerRect.y){
                ball.Speed.x *= -1;
                ball.Speed.y *= -1;
            }
        }
        if (CheckCollisionCircleRec(ball.Position, ball.Radius, cpuRect)){ // cpu collison
            
            if (ball.Position.x < cpuRect.x || ball.Position.x > cpuRect.x + cpuRect.width || ball.Position.y >= cpu.recWidth) { // check if ball.Position on the x axis is less than x axis of Rectangle
                // or if ball position on the x axis is greater than rectangle x axis + width to detetected bottom hits
                ball.Speed.x *= -1; // Reverse X velocity if the ball hits the left or right side of the rectangle
            }

            if (ball.Position.y < cpuRect.y || ball.Position.y > cpuRect.y + cpuRect.height || ball.Position.y >= cpu.recWidth) {
                ball.Speed.y *= -1; // Reverse Y velocity if the ball hits the top or bottom side of the rectangle
            }
        }
        }
        else{
            framesCounter++;
        } 
        //-----------------------------------------------------
        

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

            char buffer[100];
            sprintf(buffer, "%d"  " : %d", player.Score, cpu.Score);  // Convert the float to a string with 2 decimal places


            ClearBackground(BLACK);
            DrawRectangleRec(playerRect, PURPLE);
            DrawRectangleRec(cpuRect, PURPLE);
            DrawCircleV(ball.Position, (float)ball.Radius, MAROON);
            
            DrawText(buffer, 365, GetScreenHeight() - 400, 25, LIGHTGRAY);
            
            
            // On pause, we draw a blinking message
            if(pause && started){
                DrawText("PRESS SPACE TO START", 200, 200, 30, GRAY);
            }

            else if(!pause){
                DrawText("PRESS SPACE to PAUSE GAME", 10, GetScreenHeight() - 25, 20, LIGHTGRAY); 
            }
            

            DrawFPS(10, 10);

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}