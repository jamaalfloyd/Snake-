/** Contains helper functions for the snake game.
@file snake_helper.cpp
@author Jamaal Floyd
*/

#include "snake_helper.h"

#include <iostream>
#include <set>
#include <vector>

#include "lib/snake.h"
using namespace std;

void draw_walls(char board[HEIGHT + 2][WIDTH + 2]) {
  for (int top = 0; top < WIDTH + 2; top++) {
    board[0][top] = '#';
  }
  for (int bottom = 0; bottom < WIDTH + 2; bottom++) {
    board[HEIGHT + 1][bottom] = '#';
  }
  for (int lside = 0; lside < HEIGHT + 2; lside++) {
    board[lside][0] = '#';
  }
  for (int rside = 0; rside < HEIGHT + 2; rside++) {
    board[rside][WIDTH + 1] = '#';
  }

  return;
}

void draw_snake(char board[HEIGHT + 2][WIDTH + 2],
                const std::vector<Pos> snake) {
  for (uint index = 1; index < snake.size(); index++) {
    Pos body = snake.at(index);
    board[body.y][body.x] = 'O';
  }
  Pos head = snake.at(0);
  board[head.y][head.x] = '@';

  return;
}

void draw_food(char board[HEIGHT + 2][WIDTH + 2], const std::set<Pos> food) {
  for (auto it = food.begin(); it != food.end(); it++) {
    Pos f = *it;
    board[f.y][f.x] = '+';
  }
  return;
}

Pos new_head(const vector<Pos> snake, Move move) {
  Pos head = snake.at(0);
  if (move == UP) {
    head.y -= 1;
  }
  if (move == DOWN) {
    head.y += 1;
  }
  if (move == RIGHT) {
    head.x += 1;
  }
  if (move == LEFT) {
    head.x -= 1;
  }
  return head;
}

bool collide_walls(const vector<Pos> snake, Move move) {
  Pos head = new_head(snake, move);
  if (move == UP) {
    return head.y == 0;
  }
  if (move == DOWN) {
    return head.y == HEIGHT + 1;
  }
  if (move == RIGHT) {
    return head.x == WIDTH + 1;
  }
  if (move == LEFT) {
    return head.x == 0;
  }
  return false;
}

bool collide_snake(const vector<Pos> snake, Move move) {
  Pos head = new_head(snake, move);
  for (uint index = 1; index < snake.size(); index++) {
    if (head == snake.at(index - 1)) return true;
  }
  return false;
}

bool collide_food(const vector<Pos> snake, Move move, const set<Pos> food) {
  Pos head = new_head(snake, move);
  for (auto it = food.begin(); it != food.end(); it++) {
    if (head == *it) return true;
  }
  return false;
}