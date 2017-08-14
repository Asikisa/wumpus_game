// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: contains enum for messaging between model and view

#ifndef ENUMS_H
#define ENUMS_H

namespace wumpus_game {

  enum class Event
  {
    MODEL_READY = 0,
    UNKNOWN_COMMAND,
    READY_TO_INPUT,
    NEW_LEVEL,
    GAME_OVER,
    MOVED_BY_BATS,
    HAVE_NOT_ARROWS,
    SHOT_NOT_NEIGHBOR,
    MOVE_NOT_NEIGHBOR,
    PLAYER_DOES_SHOT,
    PLAYER_DOES_MOVE,
    ONE_WUMP_KILLED
  };

  enum class PlayerState
  {
    STAY = 0,
    WALK,
    SHOT,
    MOVED_BY_BATS,
    KILLED_BY_WUMP,
    KILLED_BY_PITS,
    KILL_WUMP,
    HAVENT_ARROWS,
    FEELS_WUMP,
    FEELS_BATS,
    FEELS_PITS,
    UNKNOWN_STATE
  };

  enum class RoomState
  {
    ON,
    OFF,
    MARK
  };

  enum class InfoStuff
  {
    COVER,
    ARROWS,
    PITS,
    BATS,
    WUMPS,
    LEVEL,
    CONTINUE_IMAGE,
    CONTINUE_DEIMAGE
  };
   
}  // namespace wumpus_game

#endif  // EVENTS_H