#pragma once
#include <iostream>
#include "../include/raylib.h"
#include <vector>

//is clickable

class Toolbar{
  public:
    Toolbar();
    void init();
    bool isActive();
    bool iscreatable();
    bool isselectable();
    void updateToolbar();
    void drawToolBar();
  private:
    class Button{
      public:
        Button(Color color, int width, int height);
        Color getColor;
        Rectangle getRectangle();
        std::vector<Rectangle> buttonArray;
        void drawButtons();
        void generateButton();
        int numberOfButtons{2};
      private:
        Color _c;
        int _posx;
        int _posy;
        int _width;
        int _height;
        Rectangle linkModeToggle{};
        Rectangle selectionModeToggle{};
    };
    int _posx{0};
    int _posy{0};
    int _width;
    int _height;
};