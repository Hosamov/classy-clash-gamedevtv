#include "raylib.h"
#include "raymath.h"

int main() {
  // Window dimensions
  int windowDimensions[2];
  windowDimensions[0] = 384; // Window width
  windowDimensions[1] = 384; // Window height

  // Initialize the window
  InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");

  // Map variables
  Texture2D map = LoadTexture("nature_tileset/worldmap.png");

  SetTargetFPS(60);
  while(!WindowShouldClose()) { 
    // Start drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // Draw the background
    Vector2 mapPos{0.0, 0.0};
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // End drawing
    EndDrawing();
  }

  UnloadTexture(map);
  CloseWindow();
}