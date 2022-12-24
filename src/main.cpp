#include "../headers/game.h"

int main(){
  const int screenWidth = 1600;
  const int screenHeight = 900;
  Game game(screenWidth, screenHeight, 60, "SandBox3");

  game.InitGame();
  while (!game.isGameRunning())    // Detect window close button or ESC key
  {
    game.tick();
  }

  CloseWindow();        // Close window and OpenGL context

  return 0;
}