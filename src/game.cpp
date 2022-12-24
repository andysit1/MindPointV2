#include <assert.h>
#include "../headers/game.h"
#include "../headers/canvas.h"
#include "../headers/toolbar.h"
//this file is start everything needed for the canvas....

Canvas canvas;
Toolbar toolbar;

Game::Game(int width, int height, int fps, const char* title)
{
  assert(!GetWindowHandle());
  SetTargetFPS(fps);
  InitWindow(width, height,title);
}
Game::~Game() noexcept
{
  assert(GetWindowHandle());
  CloseWindow();
}
bool Game::isGameRunning() const
{
  return WindowShouldClose();
}

void Game::InitGame()
{
}

void Game::Update()
{
  ClearBackground({26, 27, 32, 1});
  canvas.updateCameraView();
  canvas.conditionCheck();
  canvas.updateNote();
  toolbar.updateToolbar();
  canvas.iscreatable = toolbar.isActive();
}

void Game::Draw()
{
  canvas.drawNote();
  toolbar.drawToolBar();
  canvas.drawToggleButtons();
}

void Game::tick()
{
  BeginDrawing();
  Update();
  Draw();
  EndDrawing();
}
