#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval){
    double currentTime = GetTime();// inbuit method of raylib to get the time intervel
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() 
{
    InitWindow(500,620,"raylib Tetris"); // creating window of 300 x 600 

    // 1 event handling 2 updating positions 3 drawing objects 
    SetTargetFPS(60); // run game at 50 fps if not set speed depends on computer

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
          
    Game game = Game();
    // game loop 
    while (WindowShouldClose() == false)//check for click of esc button or x sign click if clicked return true 
    { 
        game.HandleInput();
        if(EventTriggered(0.2)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 30, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 30, 2, WHITE);
        if(game.gameOver){
            DrawTextEx(font, "GAME OVER", {320, 450}, 30, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);




        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 30, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
        EndDrawing();
    }
    CloseWindow(); // closing window 
}

