#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include "read_and_write.h"

//-------------------- Чтение и вывод ----------------------------------

void print_matrix(int k, std::vector<std::vector<bool>> matrix)
{
  std::cout << k << std::endl;
  std::cout << matrix.size() << " " << matrix[0].size() << std::endl;
  for (int i = 0; i < matrix.size(); ++i)
  {
    for (int j = 0; j < matrix[i].size(); ++j)
      if (matrix[i][j])
        std::cout << "1 ";
      else
        std::cout << "0 ";
    std::cout << std::endl;
  } 
}

void code_print_matrix(int k, std::vector<std::vector<bool>> matrix)
{
  std::cout << k << std::endl;
  std::cout << matrix.size() << " " << matrix[0].size() << std::endl;
  
  int step = 8;
  int tmp = 0;
  
  std::cout << step << std::endl;
  
  for (int i = 0; i < matrix.size(); ++i)
  {
	int j = 0;
	int c = 0;
	while (j + step < matrix[0].size()) 
	{
	  c = 0;
	  for (int a = 0; a < step; ++a)
	  {  
		c *= 2;
		if (matrix[i][j+a])
	      ++c;
	  }
	  std::cout << c << " ";
	  
      j += step;
	}
	
	c = 0;
	if (j < matrix[0].size())
	{
	  while (j < matrix[0].size())
	  {
	    c *= 2;
	    if (matrix[i][j])
	      ++c;
	    ++j;
	  }
	  std::cout << c << " ";
	}
	std::cout << std::endl;
  }
  return;
}

std::vector<std::vector<bool>> read_matrix()
{
  int n, m;
  std::cin >> n >> m;
  std::vector<bool> tmp(m, 0);
  std::vector<std::vector<bool>> matrix(n, tmp);
  int c;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
    { 
	  std::cin >> c;
	  if (c == 0) matrix[i][j] = false;
	  else matrix[i][j] = true;
    }
  return matrix;
}

std::stack<bool> create_sequence_by_int(int c, int size)
{
  std::stack<bool> answer;
  while (c > 0)
  {  
    answer.push(c % 2 != 0);
    c /= 2;
  }
  while (answer.size() < size)
    answer.push(false);
  return answer;
}

std::vector<std::vector<bool>> code_read_matrix()
{
  int n, m;
  std::cin >> n >> m;
  int step;
  std::cin >> step;
  
  std::vector<bool> tmp;
  std::vector<std::vector<bool>> matrix(n, tmp);
  
  int c;
  int j = 0;
  for (int i = 0; i < n; ++i)
  {
	j = 0;
	while (j < m/step)
	{
	  std::cin >> c;
	  auto seq = create_sequence_by_int(c, step);
	  while (seq.size() > 0)
	  {
		matrix[i].push_back(seq.top());
		seq.pop();
	  }
	  ++j;
	}

	if (m % step != 0)
	{
  	  std::cin >> c;
	  auto seq = create_sequence_by_int(c, m%step);
	  while (seq.size() > 0)
	  {
		matrix[i].push_back(seq.top());
		seq.pop();
	  }
	  ++j;
	}
  }
  return matrix;
}

void print_function(std::vector<std::vector<int>> matrix)
{
  int n = matrix.size();
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
      if (matrix[i][j] < 0)
        std::cout << "- ";
      else
        std::cout << matrix[i][j] << " ";
    std::cout << std::endl;
  }
  return;
}
