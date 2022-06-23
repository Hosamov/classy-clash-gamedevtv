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
  Texture2D map = LoadTexture("nature_tileset/worldmap.png");\
  Vector2 mapPos{0.0, 0.0};

  float speed{4.0};

  SetTargetFPS(60);
  while(!WindowShouldClose()) { 
    // Start drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // Direction logic
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0; // Up direction is negative val
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    if (Vector2Length(direction) != 0.0) {
      // Set mapPos = mapPos - direction
      mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
    }

    // Draw the map
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // End drawing
    EndDrawing();
  }

  UnloadTexture(map);
  CloseWindow();
}