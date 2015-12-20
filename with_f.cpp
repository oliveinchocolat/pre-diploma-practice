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

