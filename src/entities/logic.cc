// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#include "logic.h"

namespace wumpus_game {

Logic::Logic()
  : level_{}
  , player_turn_{true}
  , game_over_cause_{Subject::EMPTY}
  , curr_level_{1}
  , rooms_history_{ }
{
  NotifyObservers(Event::MODEL_READY);
}

void Logic::NewLevel()
{
  NewLevel(curr_level_); 
}

void Logic::NewLevel(unsigned int num)
{
  curr_level_ = num;

  int base = config::GetMapBase(curr_level_);
  int arrows = config::GetArrowsCount(curr_level_);
  int wump = config::GetWumpsCount(curr_level_);
  int bat = config::GetBatsCount(curr_level_);
  int pit = config::GetPitsCount(curr_level_);

  level_ = Level(base, arrows, wump, bat, pit);

  game_over_cause_ = Subject::UNKNOWN;
  player_turn_ = true;
  rooms_history_.clear();

  NotifyObservers(Event::NEW_LEVEL);
  NotifyObservers(Event::READY_TO_INPUT);
}

void Logic::Turn(int action, int room)
{
  if (!game_over_cause_) {
    PlayerTurn(action, room);
    GuideTurn();
  }
  if (!player_turn_ && !game_over_cause_) {
      PitsTurn();
      BatsTurn();
      WumpsTurn();
  }
  if (!game_over_cause_) {
    NotifyObservers(Event::READY_TO_INPUT);
  }
  else {
    if (game_over_cause_ == Subject::PLAYER) {
      curr_level_ != config::levels_max ? ++curr_level_ : curr_level_ = 1;
    }
  }
}

void Logic::PlayerTurn(int action, int room)
{
  player_turn_ = true;
  bool does = false;
  switch (action) 
  {
    case 0 : does = PlayerMove(room); break;
    case 1 : does = PlayerShot(room); break;
    default : NotifyObservers(Event::UNKNOWN_COMMAND); break;
  }
  player_turn_ = !does;
}

bool Logic::PlayerShot(int to_room)
{
  auto& player = level_.player_;
  auto& wumps  = level_.wumps_;
  auto cave   = level_.cave_.get();
  
  int from_room = player->GetCurrRoomNum();
  
  if (!map_helpers::IsNeighboringRooms(to_room, from_room, cave)) {
    NotifyObservers(Event::SHOT_NOT_NEIGHBOR);
    return false;
  }

  if (!player->Shot()) {
    game_over_cause_ = Subject::WUMP;
    NotifyObservers(Event::HAVE_NOT_ARROWS);
    NotifyObservers(Event::GAME_OVER);
    return false;
  }
  
  NotifyObservers(Event::PLAYER_DOES_SHOT);

  auto neighbors = map_helpers::GetNeighboringRooms(from_room, cave);
  helpers::WorryNeighboringWumps(wumps, neighbors);

  if (helpers::KillOneWumpInRoom(wumps, to_room)) {
    NotifyObservers(Event::ONE_WUMP_KILLED);
  }

  return true;
}

bool Logic::PlayerMove(int room)
{
  auto& player = level_.player_;      
  
  std::string msg{""};
  if (!player->Move(room, msg)) {
    NotifyObservers(Event::MOVE_NOT_NEIGHBOR);
    return false; 
  }

  rooms_history_.push_back(room);
  NotifyObservers(Event::PLAYER_DOES_MOVE);
  return true;
}

void Logic::WumpsTurn()
{
  auto& player = level_.player_;
  auto& wumps = level_.wumps_;
  
  for (auto& wump : wumps) {
    if (wump->Worried()) {
      wump->MoveRandom();
      wump->Worried(false);
    }
    if (helpers::IsInOneRoom(wump.get(), player.get())) {
      player->Kill();
      game_over_cause_ = Subject::WUMP;
      NotifyObservers(Event::GAME_OVER);
      break;
    }
  }
}

void Logic::BatsTurn()
{
  auto& player = level_.player_;
  auto& bats = level_.bats_;

  for (auto& bat : bats) {
    if (helpers::IsInOneRoom(bat.get(), player.get())) {
      player->TeleportRandom();
      bat->TeleportRandom();
      rooms_history_.push_back(player->GetCurrRoomNum());
      NotifyObservers(Event::MOVED_BY_BATS);
      break;
    }
  }
}

void Logic::PitsTurn()
{
  auto& player = level_.player_;  
  auto& pits = level_.pits_;

  for (auto& pit : pits) {
    if (helpers::IsInOneRoom(pit.get(), player.get())) {
      player->Kill();
      game_over_cause_ = Subject::PIT;
      NotifyObservers(Event::GAME_OVER);
      break;
    }
  }
}

void Logic::GuideTurn()
{
  auto& wumps  = level_.wumps_;
  auto* player = level_.player_.get();
  auto* guide = level_.guide_.get();

  // Conditions to player win

  bool meets_guide = helpers::IsInOneRoom(player, guide);
  bool wumps_dead  = helpers::AliveSubjectsCount(wumps) == 0 ? true : false;

  if (meets_guide) {
    NotifyObservers(Event::MEETS_GUIDE);
  }
  
  if (meets_guide && wumps_dead) {
    game_over_cause_ = Subject::PLAYER;
    NotifyObservers(Event::GAME_OVER);
  }

}

}  // namespace wumpus_game