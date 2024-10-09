#ifndef MAP_16_HPP
#define MAP_16_HPP

#include <vector>

std::vector<std::vector<char>> map = {
  { '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', 'S', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', ' ', '+', ' ', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', ' ', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+' },
  { '|', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+' },
  { '|', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', '-', '+', '-', '+', ' ', '+', '-', '+', '-', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', '|' },
  { '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', ' ', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', '-', '+', '-', '+' },
  { '|', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '|' },
  { '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+', ' ', '+' },
  { '|', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', ' ', 'E', '|' },
  { '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+', '-', '+' }
};

#endif