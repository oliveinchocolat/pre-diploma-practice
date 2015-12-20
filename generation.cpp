#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include "structures.h"
#include "read_and_write.h"
#include "generation.h"


//-------------------- Генерация ---------------------------------------

int result_of_substitution(point A, lin_function f, int k)
{
  return (A.x_1 * f.a_1 + A.x_2 * f.a_2 + f.a_0)%k;
}

bool one_cell(point A, pair_of_lin B, int k)
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

std::vector<pair_of_lin> gen_col(int k)
{
  std::vector<pair_of_lin> list;
  pair_of_lin para;
  lin_function f_1, f_2;
  
  for (int a1 = 0; a1 < k; ++a1)
  for (int a2 = 0; a2 < k; ++a2)
  for (int a0 = 0; a0 < k; ++a0)
  {
	f_1.a_1 = a1;
	f_1.a_2 = a2;
	f_1.a_0 = a0;
	para.f = f_1;
	
	for (int b1 = 0; b1 < k; ++b1)
	for (int b2 = 0; b2 < k; ++b2)
	for (int b0 = 0; b0 < k; ++b0)
	{
	  f_2.a_1 = b1;
	  f_2.a_2 = b2;
	  f_2.a_0 = b0;
	  para.g = f_2;
	  if (!is_equal(para))
	    list.push_back(para);
	}
  }
  return list;
}

std::vector<point> gen_str(int k)
{
  std::vector<point> list;
  point C;
  for (int i = 0; i < k; ++i)
   for (int j = 0; j < k; ++j)
    for (int l = 0; l < k; ++l)
    {
	  C.x_1 = i;
	  C.x_2 = j;
	  C.y = l;
	  list.push_back(C);
	}
  return list;   
}

std::vector<std::vector<bool>> gen_matrix(int k)
{
  auto list_of_col = gen_col(k);
  auto list_of_str = gen_str(k);
  
  std::vector<bool> tmp(list_of_col.size(), 0);
  std::vector<std::vector<bool>> matrix(list_of_str.size(), tmp);
  
  
  for (int i = 0; i < matrix.size(); ++i)
    for (int j = 0; j < matrix[i].size(); ++j)
      matrix[i][j] = one_cell(list_of_str[i], list_of_col[j], k);
      
  return matrix;
}
