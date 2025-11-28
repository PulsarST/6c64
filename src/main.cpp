#include <raylib.h>

int main() {
    InitWindow(1280, 720, "Hello world");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);


        EndDrawing();
    }

    CloseWindow();
}