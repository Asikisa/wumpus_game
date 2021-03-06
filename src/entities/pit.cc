// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementations of the bottomless Pit class

#include "pit.h"

namespace wumpus_game {

Pit::Pit(Map* cave) : Enemy(cave)
{
  type_ = Subject::PIT;
}

}  // namespace wumpus_game