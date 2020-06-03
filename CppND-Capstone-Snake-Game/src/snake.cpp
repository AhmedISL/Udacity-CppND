#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::update() {
  SDL_Point previousCell{
      static_cast<int>(headX),
      static_cast<int>(headY)
  };  // Capture the head's cell before updating.

  updateHead_();

  SDL_Point currentCell{
      static_cast<int>(headX),
      static_cast<int>(headY)
  };  // Capture the head's cell after updating.

  /*
   * Update all of the body vector items 
   * if the snake head has moved to a new cell.
   */
  if (currentCell.x != previousCell.x || currentCell.y != previousCell.y) {
    updateBody_(std::move(currentCell), std::move(previousCell));
  }
}

void Snake::updateHead_() {
  switch (direction) {
      
    case Direction::kUp:
      headY -= speed;
      break;

    case Direction::kDown:
      headY += speed;
      break;

    case Direction::kLeft:
      headX -= speed;
      break;

    case Direction::kRight:
      headX += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  headX = fmod(headX + _gridWidth, _gridWidth);
  headY = fmod(headY + _gridHeight, _gridHeight);
}

void Snake::updateBody_(SDL_Point &&currentHeadCell, SDL_Point &&previousHeadCell) {
  // Add previous head location to vector
  body.push_back(std::move(previousHeadCell));

  if (!_growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    _growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (currentHeadCell.x == item.x && currentHeadCell.y == item.y) {
      alive = false;
      break;
    }
  }
}

void Snake::growBody() { 
  _growing = true; 
}

// Check if the cell is occupied by snake.
bool Snake::snakeCell(int x, int y) {
  if (x == static_cast<int>(headX) && y == static_cast<int>(headY)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}