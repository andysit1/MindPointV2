#include "../headers/toolbar.h"

//ToolBar FUNCTIONST
Toolbar::Button::Button(Color color, int width, int height){
  this->_c = color;
  this->_width = width;
  this->_height = height;
}

void Toolbar::Button::generateButton(){
  int spacePerButton = GetScreenWidth();
  int changePosX = (spacePerButton / 2) + (_width / 2);
  int changePosY = (_height / 4);

  for (int i = 0; i < numberOfButtons; i++){
    Rectangle object{changePosX + (spacePerButton / 2) * (i + 1), changePosY, _width, _height};
    buttonArray.push_back(object);
  }
}

void Toolbar::Button::drawButtons(){
  for (int i = 0; i < numberOfButtons; i++){
    DrawRectangleV({buttonArray[i].x, buttonArray[i].y}, {float(_width), float(_height)}, BLUE);
  }
}

Toolbar::Toolbar(){
};

void Toolbar::init(){
}

bool Toolbar::isActive(){
  if(CheckCollisionPointRec(GetMousePosition(),{float(_posx), float(_posy), float(GetScreenWidth()), 150})){
     return false;
  }
  return true;
}

void Toolbar::updateToolbar(){

}

void Toolbar::drawToolBar(){
  DrawRectangle(_posx, _posy, GetScreenWidth(), 150, DARKGRAY);
}