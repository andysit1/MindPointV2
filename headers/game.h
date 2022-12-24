#include "../include/raylib.h"

class Game
{
public:
  Game(int width, int height, int fps, const char* title);
  ~Game() noexcept;


  void tick();
  bool isGameRunning() const;
  void InitGame();


private:
  void Update();
  void Draw();
};