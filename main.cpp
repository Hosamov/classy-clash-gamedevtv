#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

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
  const float mapScale{4.0f};

  Character knight{windowDimensions[0], windowDimensions[1]};

  // Draw props
  Prop props[2]{
    Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
    Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
  };

  Enemy goblin{
    Vector2{0.f, 0.f}, 
    LoadTexture("characters/goblin_idle_spritesheet.png"), 
    LoadTexture("characters/goblin_run_spritesheet.png")
  };

  goblin.setTarget(&knight);

  SetTargetFPS(60);
  while(!WindowShouldClose()) { 
    // Start drawing
    BeginDrawing();
    ClearBackground(WHITE);

    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

    // Draw the map
    DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
    
    // Draw the props
    for(auto prop : props) {
      prop.Render(knight.getWorldPos());
    }

    knight.tick(GetFrameTime());
    // Check map bounds
    if(knight.getWorldPos().x < 0.f || 
       knight.getWorldPos().y < 0.f ||
       knight.getWorldPos().x + windowDimensions[0] > map.width * mapScale ||
       knight.getWorldPos().y + windowDimensions[1] > map.height * mapScale ) 
    {
      knight.undoMovement();
    }

    // Check prop collisions
    for(auto prop: props) {
      if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) {
        knight.undoMovement();
      }
    }

    goblin.tick(GetFrameTime());

    // End drawing
    EndDrawing();
  }

  UnloadTexture(map);
  CloseWindow();
}