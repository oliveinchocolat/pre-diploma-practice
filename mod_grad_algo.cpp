#include <vector>

#include "structures.h"
#include "grad_algo.h"
#include "mod_grad_algo.h"


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

