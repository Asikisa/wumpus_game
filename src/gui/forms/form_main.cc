// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main window for gui windows container

#include "form_main.h"

namespace wumpus_game {

FormMain::FormMain ()
: Fl_Window(425, 400, "Hunt the Wumpus")
, img_cover_{(new Fl_PNG_Image("../src/gui/forms/img/bg.png"))}
, img_bg_{(new Fl_Tiled_Image(img_cover_,0,0))}
, box_cover_{new Fl_Box(-5, 0, 435, 625)}
, box_level_{new Fl_Box(2, 54, 425, 390)}
, box_label_{new Fl_Box(30, 20, 370, 45, "HUNT THE WUMPUS")}
, btn_start_{new Fl_Button(27, 655, 105, 25, "Start new")}
, btn_help_{new Fl_Button(165, 655, 105, 25, "Help")}
, btn_quit_{new Fl_Button(297, 655, 105, 25, "Quit")}
{
  TuneAppearance();
  end();
}

FormMain::~FormMain()
{
  delete btn_quit_;
  delete btn_help_;
  delete btn_start_;
  delete box_label_;
  delete box_level_;
  delete box_cover_;
  delete img_cover_;
}

void FormMain::Redraw(int level)
{
  int offset = 30;
  int w = draw_consts::level_width(level) + offset * 2;
  int h = w + 100;
  
  resize(1, 1, w, h);
  position((Fl::w() - this->w())/2, (Fl::h() - this->h())/2);
  box_cover_->resize(-5, 0, this->w(), this->h());
  box_level_->resize(2, 54, this->w(), this->h()/2);
  box_label_->resize(30, 20, this->w()-60 , 45);
  btn_start_->resize(27, this->h()-40, 105, 25);
  btn_help_->resize(165, this->h()-40, 105, 25);
  btn_quit_->resize(297, this->h()-40, 105, 25);

  redraw();
}

void FormMain::TuneAppearance()
{
  set_modal();
  color((Fl_Color)34);
  position((Fl::w() - this->w())/2, (Fl::h() - this->h())/2);
  // box_cover_->image(img_bg_);
  // box_cover_->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
  image(img_bg_);
  box_label_->box(FL_PLASTIC_UP_FRAME);
  box_label_->color((Fl_Color)84);
  box_label_->labelsize(28);
  box_label_->labelcolor((Fl_Color)115);
}

}  // namespace wumpus_game