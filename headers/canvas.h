#pragma once
#include <iostream>
#include "../include/raylib.h"
#include <vector>

class Canvas{
private:
  class Note
  {
    public:
      //linked List starting point
      int listPosition;
      Note* next{nullptr};

      Note(float posx, float posy, int width, int height);
      void remove();
      void draw();
      void checkConidition();
      void select();
      Rectangle getRectangle();
      bool selected{false};
      Color _c;
      Vector2 getPosition();
    private:
      float _posx;
      float _posy;
      float _width;
      float _height;
      Rectangle noteHitBox{};
      bool mouseScaleReady{false};
      bool mouseScaleMode{false};
      bool noteRepositionReady{false};
      bool noteRepositionMode{false};
  };

public:
  //list location of notes
  std::vector<Note*> headNote;
  void addNote(Note* head, Note* note);
  void printLinked(Note* head);
  Rectangle canvas = {0, 0, GetScreenWidth(), GetScreenHeight()};
  Note* currentHeadNote{nullptr};
  Canvas();
  void drawNote();
  void updateNote();
  void setNote();
  void generateNoteOjbect();
  void conditionCheck();
  void drawToggleButtons();
  void linkNotes();
  void drawNotePairs(Note* obj1, Note* obj2);
  void updateCameraView();
  bool iscreatable{true};
  bool createMode{false};
private:
  std::vector<Note> notes;
  std::vector<Note> selectedNotes;
  std::vector<Note> groupedNotes;
  bool linkMode{false};
  Color logicBox;
  Color linkBox;
  Vector2 noteSize {200, 150};
};