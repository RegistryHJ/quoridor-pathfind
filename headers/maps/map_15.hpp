#ifndef MAP_15_HPP
#define MAP_15_HPP

#include <vector>

std::vector<std::vector<char>> map = {
  { '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+' },
  { '|', '.', ' ', '.', '|', '.', ' ', '.', ' ', 'S', ' ', '.', ' ', '.', ' ', '.', '|', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+' },
  { '|', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', '-', '+', '-', '+', '-', '+', '-', '+', ' ', '+', ' ', '+' },
  { '|', '.', '|', '.', '|', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', '|', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+' },
  { '|', '.', '|', '.', '|', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', '|', '.', '|' },
  { '+', ' ', '+', ' ', '+', '-', '+', '-', '+', ' ', '+', ' ', '+', '-', '+', '-', '+', ' ', '+' },
  { '|', '.', '|', '.', ' ', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+' },
  { '|', '.', '|', '.', ' ', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', '-', '+', '-', '+', '-', '+', '-', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', '-', '+', '-', '+', '-', '+', '-', '+', ' ', '+', ' ', '+' },
  { '|', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', '|' },
  { '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+' }
};

#endif