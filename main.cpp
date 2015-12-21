#include <iostream>
#include <vector>
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
  
  auto matrix_for_grad_algorithm = gen_matrix(k);
  auto user_mods = gen_list_of_modify_bounds(k);
  auto coverage = grad_algo_with_mod(matrix_for_grad_algorithm, k, user_mods);
  
  if (coverage.size() == 0)
  { 
    std::cout << "Impossible";
  }
  if (coverage.size() > 0)
  {
    std::cout << "Possible, size = " << coverage.size() << std::endl;
    auto universal_function = get_univ_function_by_coverage(k, coverage);
    print_function(universal_function);
  }
  std::cout << std::endl;
  
  return 0;
}

