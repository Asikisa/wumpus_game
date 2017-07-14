// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: FLTK widget draw pathes between rooms

#include "map_pathes.h"

namespace wumpus_game {

MapPathes::MapPathes(int level, double edge_length)
  : Fl_Widget(1, 1, 1, 1, "")
  , vxs_count_{(level+3)*4}
  , edge_length_{edge_length}
  , total_vxs_(vxs_count_)
  , inner_vxs_{}
  , middle_vxs_{}
  , outer_vxs_{}
{
  FillAllVertexes();
}

void MapPathes::FillAllVertexes()
{
  // Prepare

  double width = vxs_count_ * edge_length_;
  double height = width;
  double x0 = width/2;
  double y0 = height/2;

  // Get points of inner polygon 

  double ivxs_count_ = vxs_count_/4;
  double irad = width / 4;
  double istart_angle = 90;

  inner_vxs_ = draw_helpers::get_poly_vertexes(
    ivxs_count_, irad, istart_angle, x0, y0
  );
  
  // Get points of middle polygon

  double mvxs_count_ = vxs_count_/2;
  double mrad = irad * 2;
  double mstart_angle = 90;

  middle_vxs_ = draw_helpers::get_poly_vertexes(
    mvxs_count_, mrad, mstart_angle, x0, y0
  );
  
  // Get points of outer polygon

  double ovxs_count_ = vxs_count_/4;
  double orad = (width / 4) + (2 * (width / 3));
  double ostart_angle = 90 + (360 / ovxs_count_ / 2);

  outer_vxs_ = draw_helpers::get_poly_vertexes(
    ovxs_count_, orad, ostart_angle, x0, y0
  );

  // Fill total map vector by previously recieved polygons points

  double step = 2;
  double start_ivx = vxs_count_/2;
  draw_helpers::fill_vector_by_another(
    total_vxs_, inner_vxs_, start_ivx, step
  );

  step = 1;
  double start_mvx = 0;
  draw_helpers::fill_vector_by_another(
    total_vxs_, middle_vxs_, start_mvx, step
  );

  step = 2;
  double start_ovx = (vxs_count_/2)+1;
  draw_helpers::fill_vector_by_another(
    total_vxs_, outer_vxs_, start_ovx, step
  );
}

void MapPathes::draw()
{
  // Draw inner, middle and outer polygons

  draw_helpers::draw_poly(inner_vxs_, this);
  draw_helpers::draw_poly(middle_vxs_, this);
  draw_helpers::draw_poly(outer_vxs_, this);

  // Connect polygons as in 3 dimension dodecaedron

  draw_helpers::draw_edges(total_vxs_, this);
}

namespace draw_helpers {

PointVec get_poly_vertexes(
  double edges, double rad, double angle_start, double x0, double y0)
{
  std::vector<Point> res (edges);
  double angle_step = 360 / edges;
  double angle = angle_start;

  for (double i = 0; i < edges; ++i) {
    if (angle > 360) angle = angle - 360;
    Point p;
    p.x_ = cos(angle*pi()/180) * rad + x0;
    p.y_ = sin(angle*pi()/180) * rad + y0;
    res[i] = p;
    angle += angle_step;
  }
  return res;
}

bool fill_vector_by_another(
  PointVec& res, const PointVec& v, double start, double step)
{
  if (res.size() < v.size())
    return false;
  
  double i = start;
  for (auto v0 : v) {
    res[i] = v0;
    i += step;
  }

  return true;
}

void draw_points(const PointVec& v, MapPathes*, int)
{
  for (const auto& v0 : v) {
    fl_line_style(1,5);
    fl_color(FL_WHITE);    
    fl_point(v0.x_, v0.y_);
  }
  fl_line_style(0,1);
}

void draw_poly(const PointVec& v, MapPathes* surface)
{
  fl_color(FL_WHITE);    
  fl_line_style(1,5);

  for (std::size_t i = 0; i < v.size(); ++i) {
    auto p1 = v[i];
    auto p2 = v[0];
    if (i+1 != v.size()) {
      p2 = v[i+1];
    }
    fl_line(
      surface->x()+p1.x_, surface->y()+p1.y_,
      surface->x()+p2.x_, surface->y()+p2.y_
    );
  }
  fl_line_style(0,1);
}

void draw_edges(const PointVec& v, MapPathes* surface)
{
  double half = static_cast<int>(v.size()/2);
  for (int i = 0; i < half; ++i) {
    auto p1 = v[i];
    auto p2 = v[i+half];
    
    std::ostringstream s1{};
    std::ostringstream s2{};
    s1 << i;
    s2 << i+half;
    fl_color(FL_BLUE);
    fl_draw(
      s1.str().c_str(),
      surface->x()+p1.x_ + 20,
      surface->y()+p1.y_ + 20
    );
    fl_draw(
      s2.str().c_str(),
      surface->x()+p2.x_ + 20,
      surface->y()+p2.y_ + 20
    );
    fl_color(FL_WHITE);    
    fl_line_style(1,5);    
    fl_line(
      surface->x()+p1.x_, surface->y()+p1.y_,
      surface->x()+p2.x_, surface->y()+p2.y_
    );
    fl_line_style(0,1);
  }
}

}  // namespace draw_helpers

}  // namespace wumpus_game