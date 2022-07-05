#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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
    Vector2{800.f, 300.f}, 
    LoadTexture("characters/goblin_idle_spritesheet.png"), 
    LoadTexture("characters/goblin_run_spritesheet.png")
  };

  Enemy slime{
    Vector2{500.f, 700.f},
    LoadTexture("characters/slime_idle_spritesheet.png"), 
    LoadTexture("characters/slime_run_spritesheet.png")
  };

  Enemy* enemies[]{
    &goblin,
    &slime
  };

  for(auto enemy : enemies) {
    enemy->setTarget(&knight);
  }

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

    if(!knight.getAlive()) { // Character is not alive
      DrawText("Game Over", 55.f, 45.f, 40, RED);
      EndDrawing();
      continue; // Start next iteration of loop
    } else { // Character is alive
      std::string knightsHealth = "Health: ";
      knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
      DrawText(knightsHealth.c_str(), 55.5, 45.f, 40, RED);
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

    for (auto enemy : enemies) {
      enemy->tick(GetFrameTime());
    }

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      for (auto enemy : enemies) {
        if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec())) {
          enemy->setAlive(false);
        }
      }
    }
      
    // End drawing
    EndDrawing();
  }

  UnloadTexture(map);
  CloseWindow();
}