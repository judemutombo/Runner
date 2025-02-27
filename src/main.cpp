#include "raylib.h"
#include "Game.h"


int main()
{
    Color dark = {0, 0, 0, 255};

    const int screenWidth = 800;
    const int screenHeight = 600;

    Camera2D camera = { 0 };

    InitWindow(screenWidth, screenHeight, "Runner");
    SetTargetFPS(60);
    Game game;

    camera.target = game.target();
    camera.offset = (Vector2){ screenWidth/2.0f, (screenHeight/2.0f) + 150.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(dark);
            BeginMode2D(camera);
            game.handleInput();
            game.display();
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}