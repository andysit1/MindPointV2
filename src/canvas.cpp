#include "../headers/canvas.h"
#define MOUSE_SCALE_MARK_SIZE   12
//NOTE FUNCTIONS


Canvas::Canvas()
:createMode{false}
{
  cam.zoom = 1;
};

Canvas::Note::Note(float posx, float posy, int width, int height)
        :
        _c(YELLOW)
{
  _posx = posx;
  _posy = posy;
  _width = width;
  _height = height;
}

Rectangle Canvas::Note::getRectangle(){
  return Rectangle{_posx, _posy, _width, _height};
}

Rectangle Canvas::Note::getInputRectangle(){
  return Rectangle{_posx + 10 , _posy + (_height / 2), _width - 20, 45};
}


void Canvas::Note::draw(){
  DrawRectangle(_posx, _posy, _width, _height, _c);
  DrawRectangleRec(getInputRectangle(), LIGHTGRAY);


  if(noteRepositionReady){
    DrawRectangle(_posx - MOUSE_SCALE_MARK_SIZE, _posy - MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, YELLOW);
    DrawRectangleLinesEx({_posx, _posy, _width, _height}, 1, RED);
    DrawRectangle(_posx - MOUSE_SCALE_MARK_SIZE, _posy - MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, YELLOW);

  }

  if (mouseScaleReady){
    DrawRectangleLinesEx({_posx, _posy, _width, _height}, 1, RED);
    DrawTriangle((Vector2){ _posx + _width - MOUSE_SCALE_MARK_SIZE, _posy + _height },
                             (Vector2){ _posx + _width, _posy + _height },
                             (Vector2){ _posx+ _width, _posy + _height - MOUSE_SCALE_MARK_SIZE }, RED);
  }

  if (selected){
    DrawRectangleLinesEx({_posx, _posy, _width, _height}, 1, BLUE);
  }


  DrawRectangle(_posx + _width - 20, _posy, 20, 20, editingTextToggle);
  DrawRectangleRec(getInputRectangle(), PURPLE);

  DrawText(text, _posx + (_width / 2) - (MeasureText(text, 30) / 2), _posy + 20, 30, BLACK);

}

//https://www.raylib.com/examples.html -> logic found here
void Canvas::Note::checkConidition(){
  if (CheckCollisionPointRec(GetMousePosition(), getInputRectangle())){
    getTextInputs();
  }

  if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ _posx - MOUSE_SCALE_MARK_SIZE, _posy - MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE})){
    noteRepositionReady = true;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      noteRepositionMode = true;
    }
  }else{
    noteRepositionReady = false;
  }

  //CheckCollisionPointRec(GetMousePosition(), (Rectangle){ _posx + _width - MOUSE_SCALE_MARK_SIZE, _posy + _height - MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE
  if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ _posx + _width - MOUSE_SCALE_MARK_SIZE, _posy + _height - MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE})){
    mouseScaleReady = true;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      mouseScaleMode = true;
    }
  }else{
    mouseScaleReady = false;
  }

 //  const int screenWidth = 1600; const int screenHeight = 900;
  if(noteRepositionMode){
    noteRepositionReady = true;
    this->_posx = GetMousePosition().x;
    this->_posy = GetMousePosition().y;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) noteRepositionMode = false;
  }
  //tops the mouse scale mode on release of left button
  //has limitation to the mouse scale mark size aka so stop the box  stinking to 0 or the size which is required to be clickable
  if (mouseScaleMode)
  {
      mouseScaleReady = true;

      //what changes the width and height of box
      this->_width = (GetMousePosition().x - _posx);
      this->_height = (GetMousePosition().y - _posy);

      // Check minimum rec size
      if (_width < MOUSE_SCALE_MARK_SIZE) _width = MOUSE_SCALE_MARK_SIZE;
      if (_height < MOUSE_SCALE_MARK_SIZE) _height = MOUSE_SCALE_MARK_SIZE;

      // Check maximum rec size
      if (_width> (GetScreenWidth() - _posx)) _width = GetScreenWidth() - _width;
      if ( _height > (GetScreenHeight() - _posy)) _height = GetScreenHeight() - _posy;

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) mouseScaleMode = false;
  }
}

//logic found here -> https://www.raylib.com/examples/text/loader.html?name=text_input_box
void Canvas::Note::getTextInputs(){
  std::cout << text << std::endl;
  //key can stack if press at the same time
  int key = GetCharPressed();

  //makes sure the keys are within a range
  while (key > 0){
    if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)){
      text[letterCount] = (char)key;
      text[letterCount+1] = '\0';
      letterCount++;
    }
    key = GetCharPressed();  // Check next character in the queue
  }
  //gets of letter on backspace
  if (IsKeyPressed(KEY_BACKSPACE)){
    letterCount--;
    if (letterCount < 0) letterCount = 0;
    text[letterCount] = '\0';
  }
}

//gets the center of note
Vector2 Canvas::Note::getPosition(){
  return Vector2{_posx + (_width / 2), _posy + (_height / 2)};
}

void Canvas::Note::select(){
  selected = !selected;
}

//CANVAS FUNCTIONS

void Canvas::updateNote(){
  for (int i = 0; i < notes.size(); i++){
    notes[i].checkConidition();
  }
  // if (iscreatable){
  //   std::cout << "triggered" << std::endl;
  // }
}

void Canvas::drawNote(){
  for (int i = 0; i < notes.size(); i++){
    notes[i].draw();
  }
}

void Canvas::generateNoteOjbect(){
  Note object(GetMousePosition().x, GetMousePosition().y, noteSize.x, noteSize.y);
  notes.push_back(object);
}

//toggle buttons basic logic and drawing
void Canvas::drawToggleButtons(){
  if (CheckCollisionPointRec(GetMousePosition(), {1500, 0, 100, 100})){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      createMode = !createMode;
    }
  }

  if (CheckCollisionPointRec(GetMousePosition(), {1400, 0, 100, 100})){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      linkMode = !linkMode;
    }
  }

  if (createMode == true){
    logicBox = {RED};
    HideCursor();
  }else{
    logicBox = {GREEN};
    ShowCursor();
  }

  if (linkMode == true){
    linkBox = {RED};
  }else{
    linkBox = {GREEN};
    //resets our linked tree
    currentHeadNote = nullptr;
    //resets the selected boxes borders
    for(int i = 0; i < notes.size(); i++){
      notes[i].selected = false;
    }
  }
  DrawRectangle(1600 - 100, 0, 100, 100, logicBox);
  DrawRectangle(1600 - 200, 0, 100, 100, linkBox);
}

void Canvas::conditionCheck(){
  //when createmode -> checks if colliding with other notes and controls iscreatble...
  if (createMode == true){
    Color rectColor{BLUE};
    for (int i = 0; i < notes.size(); i++){
      if (CheckCollisionRecs({GetScreenToWorld2D(GetMousePosition(), cam).x, GetScreenToWorld2D(GetMousePosition(), cam).y, noteSize.x, noteSize.y}, notes[i].getRectangle())){
        rectColor = RED;
        iscreatable = false;
      }
      DrawRectangleV(GetMousePosition(), noteSize, rectColor);
    }
  }

  //must be creatable and in create mode

  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && createMode && iscreatable == true){
    generateNoteOjbect();
  }

  for (int i = 0; i < notes.size(); i++){
    if (linkMode && CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), cam), notes[i].getRectangle()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
      notes[i].select();
      if (currentHeadNote == nullptr){
        currentHeadNote = &notes[i];
        std::cout  << "Head" << " " << currentHeadNote << std::endl;
        Note* head = &notes[i];
        notes[i].listPosition = headNote.size();
        headNote.push_back(head);
      }else{
        addNote(currentHeadNote, &notes[i]);
      }
    }
  }
  linkNotes();
}

//takes the head of note and starts a new list.
void Canvas::addNote(Note* head, Note* note){
  //points to current head of the list
  Note* current = head;
  //gets last position of pointer
  while (current->next != nullptr){
    current = current->next;
  }
  current->next = note;
  note->listPosition = current->listPosition + 1;
}

void Canvas::printLinked(Note* head){
  Note* current = head;

  while (current->next != nullptr){
    drawNotePairs(current, current->next);
    std::cout << current << std::endl;
    current = current->next;
  }
}
//WIP
void Canvas::updateCameraView(){
//I want to zoom in a and out of a the canvas... WIP
  // if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
  //   Vector2 delta = GetMouseDelta();
  //   delta = Vector2Scale(delta, -1.0f / cam.zoom);
  //   cam.target = Vector2Add(cam.target, delta);
	// }
  // float wheel = GetMouseWheelMove();
  // if (wheel != 0)
  // {
  //   // get the world point that is under the mouse
  //   Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);

  //   // set the offset to where the mouse is
  //   cam.offset = GetMousePosition();

  //   // set the target to match, so that the camera maps the world space point under the cursor to the screen space point under the cursor at any zoom
  //   cam.target = mouseWorldPos;

  //   // zoom
  //   cam.zoom += wheel * 0.125f;
  //   if (cam.zoom < 0.125f)
  //     cam.zoom = 0.125f;
	// 	}

  //   std::cout << GetScreenToWorld2D(GetMousePosition(), cam).x << " " << GetScreenToWorld2D(GetMousePosition(), cam).y  << std::endl;
  //   std::cout << GetWorldToScreen2D(GetMousePosition(), cam).x << " " << GetWorldToScreen2D(GetMousePosition(), cam).y << std::endl;
}

void Canvas::drawNotePairs(Note* obj1, Note* obj2){
  DrawLineEx(obj1->getPosition(), obj2->getPosition(), 10.0f, RED);

}

void Canvas::linkNotes(){
  for (int i = 0; i < headNote.size(); i++){
    std::cout << headNote.size() << std::endl;
    printLinked(headNote[i]);
  }
  // if (headNote.size() >= 2){
  //   DrawRectangle(GetScreenWidth() / 2, GetScreenHeight() - 200, 400, 200, PURPLE);
  // }
}
