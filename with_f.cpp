#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include "structures.h"
#include "read_and_write.h"
#include "generation.h"
#include "grad_algo.h"

//                     ГРАДИЕНТНЫЙ АЛГОРИТМ С МОДИФИКАЦИЕЙ

// возвращает номер строки по точке
int number_by_mod(int k, point A);

// возвращает модицикации для создания "рамки"
std::vector<point> gen_list_of_modify_bounds(int k);

// реализует градиентный алгоритм с предварительной модификацией -- по умолчанию добавляет в покрытие все строки из mods
std::vector<int> grad_algo_with_mod(std::vector<std::vector<bool>> matrix, int k, std::vector<point> mods);

//                    ВОССТАНОВЛЕНИЕ УНИВЕРСАЛЬНОЙ ФУНКЦИИ

// Возвращает точку с определением, соответствующую номеру строки t
point get_point_by_int(int k, int t);

// создает таблицу функции из набора точек со значениями функций
std::vector<std::vector<int>> get_function(int k, std::vector<point> seq);

// считывает набор строк и выводит в std::cout функцию
void get_and_print(int k, std::vector<int> list_of_strings);

//                    MAIN

int main()
{
  int k;
  std::cin >> k;
  
  auto matrix = gen_matrix(k);
  auto mods = gen_list_of_modify_bounds(k);
  auto list = grad_algo_with_mod(matrix, k, mods);
  
  if (list.size() == 0)
  { 
    std::cout << "Impossible";
  }
  if (list.size() > 0)
  {
    std::cout << "Possible, size = " << list.size() << std::endl;
    get_and_print(k, list);
  }
  std::cout << std::endl;
  
  return 0;
}


//-------------- Градиентный алгоритм с модификациями ------------------


std::vector<point> gen_list_of_modify_bounds(int k)
{
  std::vector<point> res;
  point tmp;

  for (int i = 0; i < k; ++i)
  {
	tmp.x_1 = 0;
	tmp.x_2 = i;
	tmp.y = 0;
	res.push_back(tmp);
  }

  for (int i = 1; i < k; ++i)
  {
	tmp.x_2 = 0;
	tmp.x_1 = i;
	tmp.y = 0;
	res.push_back(tmp);
  }

  for (int i = 1; i < k; ++i)
  {
	tmp.x_1 = i;
	tmp.x_2 = k-1;
	tmp.y = i;
	res.push_back(tmp);
  }

  for (int i = 1; i < k-1; ++i)
  {
	tmp.x_1 = k-1;
	tmp.x_2 = i;
	tmp.y = i;
	res.push_back(tmp);
  }

  for (int i = 1; i < k-1; ++i)
  {
	tmp.x_1 = i;
	tmp.x_2 = 1;
	tmp.y = k - i;
	res.push_back(tmp);
  }
  
  return res;
}

std::vector<int> grad_algo_with_mod(std::vector<std::vector<bool>> matrix, int k, std::vector<point> mods)
{
  std::vector<bool> tmp(matrix[0]);
  std::vector<bool> flag_of_col(tmp.size(), false);
  std::vector<int> list_of_string;
  auto number_of_one = count_number_one(matrix, flag_of_col);

  int index_mod = 0;
  for (auto i = mods.begin(); i != mods.end(); ++i)
  {
	index_mod = number_by_mod(k, *i);
    delete_str_block(index_mod, matrix, flag_of_col, k, number_of_one); 
	list_of_string.push_back(index_mod);
  }
  
  int index_max = 0;
  
  while ((!empty_one(number_of_one))&&(!all_col_under(flag_of_col)))
  {
	index_max = find_max(number_of_one);
	if (index_max != -1)
	{
	  delete_str_block(index_max,matrix, flag_of_col, k, number_of_one); 
	  list_of_string.push_back(index_max);
    }
  }

  if (all_col_under(flag_of_col))
    return list_of_string;
  std::vector<int> reserve_list(0, 0);
  return reserve_list;
}

int number_by_mod(int k, point A)
{
  return (A.y + A.x_2 * k + A.x_1 * k * k);
}

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

