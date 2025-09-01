#include "raylib.h"
#include "../includes/Game.h"
#include "../includes/config.h"


int main()
{
    Color dark = {0, 0, 0, 255};

    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    Camera2D camera = { 0 };

    InitWindow(screenWidth, screenHeight, "Runner");
    Game game;

    camera.offset = (Vector2){ screenWidth/2.0f, (screenHeight/2.0f) + 150.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    double previousTime = GetTime();    
    double currentTime = 0.0;    
    float deltaTime = 0.0f;  
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(dark);
            if(game.is2D()){
                BeginMode2D(camera);
                game.handleInput();
                game.display();
                game.checkCollision();
                EndMode2D();
            }else{
                game.handleInput();
                game.display();
                game.checkCollision();
            }
        EndDrawing();
        
        /* camera.target = game.target();
        currentTime = GetTime();
        deltaTime = (float)(currentTime - previousTime);
        previousTime = currentTime;
        game.setDeltaTime(deltaTime); */
    }

    CloseWindow();
    return 0;
}