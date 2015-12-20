#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include "structures.h"
#include "read_and_write.h"
#include "generation.h"
#include "grad_algo.h"


//-------------------- Градиентный алгоритм ----------------------------

bool empty_one(std::vector<int> number_of_one)
{
  bool flag = true;
  for (int i = 0; i < number_of_one.size(); ++i)
    if (number_of_one[i] > 0) flag = false;
  return flag;
}

std::vector<int> count_number_one(std::vector<std::vector<bool>> matrix, std::vector<bool> flags)
{
  std::vector<int> current_number(matrix.size(), 0);
  for (int i = 0; i < matrix.size(); ++i)
    for (int j = 0; j < matrix[i].size(); ++j)
      if ((matrix[i][j])&&(!flags[j])) current_number[i]++;
  return current_number;
}

int find_max(std::vector<int> seq)
{
  int current_max = 0;
  for (int i = 1; i < seq.size(); ++i)
    if (seq[i] > seq[current_max]) current_max = i;
    
  if (seq[current_max] == 0) return -1;
  return current_max;
}

void delete_column(int index_col, std::vector<std::vector<bool>>& matrix, std::vector<int>& ones)
{
  for (int i = 0; i < matrix.size(); ++i)
    if (matrix[i][index_col])
    {
      matrix[i][index_col] = false;
      ones[i]--;
    }
  return;
}

void delete_one(int index_string, std::vector<std::vector<bool>>& matrix, 
                                  std::vector<bool>& flags, bool real_string, 
                                  std::vector<int>& ones)
{
  for (int j = 0; j < matrix[index_string].size(); ++j)
  {
    if (matrix[index_string][j]) 
      if (real_string)
      {
	    delete_column(j, matrix, ones);
	    flags[j] = true;
      }
      else
      {
        matrix[index_string][j] = false;
        ones[index_string]--;
      }
  }    
  return;
}

bool all_col_under(std::vector<bool> flags)
{
  bool f = true;
  for (int i = 0; i < flags.size(); ++i)
    if (!flags[i]) f = false;
  return f; 
}

void delete_str_block(int index_string, std::vector<std::vector<bool>>& matrix, std::vector<bool>& flags, int k, 
                                        std::vector<int>& ones)
{
  for (int i = 0; i < k; ++i)
    if ((index_string/k)*k+i == index_string)
      delete_one((index_string/k)*k+i, matrix, flags, true, ones);
    else
      delete_one((index_string/k)*k+i, matrix, flags, false, ones);
  return;
}

std::vector<int> grad_algo(std::vector<std::vector<bool>> matrix, int k)
{
  std::vector<bool> tmp(matrix[0]);
  std::vector<bool> flag_of_col(tmp.size(), false);
  std::vector<int> list_of_string;
  auto number_of_one = count_number_one(matrix, flag_of_col);
  
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
