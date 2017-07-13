// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include "forms/form_main.h"
#include "forms/form_popup.h"
#include "forms/group_rooms.h"

namespace wumpus_game {

struct Windows
{
  Windows();
  ~Windows();
  void Show();
  void Close();
  void Redraw();
  // void NewRooms(int, ,);
  void AddWidget(Fl_Widget*);
  void RemoveWidget(Fl_Widget*); 
  void ShowWidget(Fl_Widget*);
  void HideWidget(Fl_Widget*); 
  
  void RedrawRooms(int);
  
  FormMain*   main_wnd_;
  FormPopup*  popup_wnd_;
  GroupRooms* box_rooms_;
};

}  // namespace wumpus_game

#endif  // GUI_WINDOWS_H