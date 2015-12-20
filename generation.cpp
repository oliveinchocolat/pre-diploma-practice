#include <vector>

#include "structures.h"
#include "generation.h"

//-------------------- Генерация ---------------------------------------

int result_of_substitution(point A, lin_function f, int k)
{
  return (A.x_1 * f.a_1 + A.x_2 * f.a_2 + f.a_0)%k;
}

bool one_cell_value(point A, pair_of_lin B, int k)
{
  if ((result_of_substitution(A, B.f, k) == A.y)&&(result_of_substitution(A, B.g, k) != A.y))
    return true;
  return false;
}

bool is_equal(pair_of_lin B)
{
  if (B.f.a_0 != B.g.a_0) return false;
  if (B.f.a_1 != B.g.a_1) return false;
  if (B.f.a_2 != B.g.a_2) return false;
  return true;
}

std::vector<pair_of_lin> gen_list_of_columns(int k)
{
  std::vector<pair_of_lin> list_of_columns;
  pair_of_lin current_pair;

  for (current_pair.f.a_1 = 0; current_pair.f.a_1 < k; ++current_pair.f.a_1)
   for (current_pair.f.a_2 = 0; current_pair.f.a_2 < k; ++current_pair.f.a_2)
    for (current_pair.f.a_0 = 0; current_pair.f.a_0 < k; ++current_pair.f.a_0)
    {
	  for (current_pair.g.a_1 = 0; current_pair.g.a_1 < k; ++current_pair.g.a_1)
	   for (current_pair.g.a_2 = 0; current_pair.g.a_2 < k; ++current_pair.g.a_2)
	    for (current_pair.g.a_0 = 0; current_pair.g.a_0 < k; ++current_pair.g.a_0)
	    {
	      if (!is_equal(current_pair))
	        list_of_columns.push_back(current_pair);
	    }
    }

  return list_of_columns;
}

std::vector<point> gen_list_of_strings(int k)
{
  std::vector<point> list_of_strings;
  point current_point;
  for (current_point.x_1 = 0; current_point.x_1 < k; ++current_point.x_1)
   for (current_point.x_2 = 0; current_point.x_2 < k; ++current_point.x_2)
    for (current_point.y = 0; current_point.y < k; ++current_point.y)
    {
	  list_of_strings.push_back(current_point);
	}
  return list_of_strings;   
}

std::vector<std::vector<bool>> gen_matrix(int k)
{
  auto list_of_col = gen_list_of_columns(k);
  auto list_of_str = gen_list_of_strings(k);
  
  std::vector<bool> tmp(list_of_col.size(), 0);
  std::vector<std::vector<bool>> matrix(list_of_str.size(), tmp);
  
  
  for (int i = 0; i < matrix.size(); ++i)
    for (int j = 0; j < matrix[i].size(); ++j)
      matrix[i][j] = one_cell_value(list_of_str[i], list_of_col[j], k);
      
  return matrix;
}
