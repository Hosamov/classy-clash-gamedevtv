#include "raylib.h"
#include "raymath.h"

class Character {
  public:
    Vector2 getWorldPos() { return worldPos; }

  private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};
};

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

  Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
  Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
  Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
  Vector2 knightPos{
    (float)windowDimensions[0]/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
    (float)windowDimensions[1]/2.0f - 4.0f * (0.5f * (float)knight.height)
  };
  // 1 : facing right, -1 : facing left
  float rightLeft{1.f};
  // animation variables
  float runningTime{};
  int frame{};
  const int maxFrames{6};
  const float updateTime{1.f/12.f};

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
      direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; // Ternary operator
      knight = knight_run;
    } else {
      knight = knight_idle;
    }

    // Draw the map
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    // update animation frame
    runningTime += GetFrameTime(); // delta time
    if (runningTime >= updateTime) {
      frame++;
      runningTime = 0.f;
      if (frame > maxFrames) frame = 0;
    }

    // Draw the character
    Rectangle source{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
    Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
    DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

    // End drawing
    EndDrawing();
  }

  UnloadTexture(map);
  CloseWindow();
}