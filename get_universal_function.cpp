#include <vector>
#include <stack>

#include "structures.h"
#include "read_and_write.h"
#include "get_universal_function.h"

//----------------- Восстановление универсальной функции ---------------

point get_point_by_string_number(int k, int string_number)
{
  point result_point;
  
  result_point.y = string_number % k;
  string_number = string_number / k;
  result_point.x_2 = string_number % k;
  result_point.x_1 = string_number / k;
  
  return result_point;
}

std::vector<std::vector<int>> get_function_matrix(int k, std::vector<point> list_of_values)
{
  std::vector<int> tmp(k, -1);
  std::vector<std::vector<int>> result_function(k, tmp);
  
  for (int i = 0; i < list_of_values.size(); ++i)
  {
	result_function[list_of_values[i].x_1][list_of_values[i].x_2] = list_of_values[i].y;
  }
  return result_function;
}

void get_and_print_univ_function(int k, std::vector<int> list_of_strings)
{
  std::vector<point> answer;
  for (auto t = list_of_strings.begin(); t != list_of_strings.end(); ++t)
  {
	point tmp = get_point_by_string_number(k, (*t));
	answer.push_back(tmp);
  }
  
  auto funct = get_function_matrix(k, answer);
  print_function(funct);
  return;  
}
