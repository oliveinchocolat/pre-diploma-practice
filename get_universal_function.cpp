#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include "structures.h"
#include "read_and_write.h"
#include "generation.h"
#include "grad_algo.h"
#include "mod_grad_algo.h"
#include "get_universal_function.h"


//----------------- Восстановление универсальной функции ---------------

point get_point_by_int(int k, int t)
{
  point a;
  a.y = t % k;
  t = t / k;
  a.x_2 = t % k;
  a.x_1 = t / k;
  return a;
}

std::vector<std::vector<int>> get_function(int k, std::vector<point> seq)
{
  std::vector<int> tmp(k, -1);
  std::vector<std::vector<int>> funct(k, tmp);
  
  for (int i = 0; i < seq.size(); ++i)
  {
	funct[seq[i].x_1][seq[i].x_2] = seq[i].y;
  }
  return funct;
}


void print_function(int k, std::vector<std::vector<int>> matrix)
{
  for (int i = 0; i < k; ++i)
  {
    for (int j = 0; j < k; ++j)
      if (matrix[i][j] < 0)
        std::cout << "- ";
      else
        std::cout << matrix[i][j] << " ";
    std::cout << std::endl;
  }
  return;
}

void get_and_print(int k, std::vector<int> list_of_strings)
{
  std::vector<point> answer;
  for (auto t = list_of_strings.begin(); t != list_of_strings.end(); ++t)
  {
	point tmp = get_point_by_int(k, (*t));
	answer.push_back(tmp);
  }
  
  auto funct = get_function(k, answer);
  print_function(k, funct);
  return;  
}

