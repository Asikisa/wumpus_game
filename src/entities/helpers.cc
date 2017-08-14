// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: general helpers

#include "helpers.h"

namespace wumpus_game {

namespace helpers {

void worry_neighboring_wumps(VWumpsPtr& wumps, std::vector<int>& neighbors)
{
  for (auto& w : wumps) {
    int room = w->GetCurrRoomNum(); 
    if (find_in_vector(neighbors, room)) w->Worried(true);
  }
}

bool kill_one_wump_in_room(VWumpsPtr& wumps, int room)
{
  // remake to more pretty
  bool kill{false};
  for (auto it = wumps.begin(); it != wumps.end();) {
    if (it->get()->GetCurrRoomNum() == room) {
      it->reset();
      it = wumps.erase(it);
      kill = true;
    } else {
      ++it;
    }
  }
  return kill;
}

bool is_in_one_room(Subject* subj1, Subject* subj2)
{
  if (subj1->GetCurrRoomNum() == subj2->GetCurrRoomNum())
    return true;
  return false;
}

// Returns subjects, placed in neighboring rooms, exclude current

std::vector<Subject::ID> subjects_in_neighboring_rooms(int room, Map* cave)
{
  std::vector<Subject::ID> res;
  Room* curr = cave->GetRoom(room);
  Room* next;
  
  next = curr->left_;
  for (auto const p : next->subjects_) {
    res.push_back(p->GetType());
  }

  next = curr->right_;
  for (auto const p : next->subjects_) {
    res.push_back(p->GetType());
  }

  next = curr->back_;
  for (auto const p : next->subjects_) {
    res.push_back(p->GetType());
  }
  return res;
}

// Convert std::vector<int> in std::string

std::string vint_to_string(const std::vector<int> &v, std::string delim)
{
  std::stringstream sst;
  for (std::size_t i = 0; i < v.size(); ++i) {
    if (i != 0) sst << delim;
    sst << v.at(i);
  }
  return sst.str();
}

}  // namespace helpers

}  // namespace wumpus_game