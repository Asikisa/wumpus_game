// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Room class

#include "room.h"

namespace wumpus_game {

bool Room::IsEmpty() const
{
  return (subjects_.empty()) ? true : false;
}

}  // namespace wumpus_game