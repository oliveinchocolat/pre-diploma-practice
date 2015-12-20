#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

//                    СТРУКТУРЫ

// линейная функция двух переменных
struct lin_function
{
  int a_0, a_1, a_2;
};

// пара линейных функций
struct pair_of_lin
{
  lin_function f, g;
};

// точка (x_1, x_2) с возможным значением y
struct point
{
  int x_1, x_2;
  int y;
};


//                        ЧТЕНИЕ И ВЫВОД

// выводит матрицу на std::cout
void print_matrix(int k, std::vector<std::vector<bool>> matrix);

// выводит кодированную матрицу на std::cout
void print_matrix_byte(int k, std::vector<std::vector<bool>> matrix);

// считывает матрицу из std::cin 
std::vector<std::vector<bool>> read_matrix();

// для кодирования матрицы
std::stack<bool> create_seq_by_int(int c, int size);

// считывает кодированную матрицу из std::cin
std::vector<std::vector<bool>> read_matrix_byte();


//                      ГЕНЕРАЦИЯ МАТРИЦЫ

// результат подстановки точки A в линейную функцию f
int result_of_substitution(point A, lin_function f, int k);

// вычисление значения одной клетки матрицы
bool one_cell(point A, pair_of_lin B, int k);

// проверяет на равенство функции пары
bool is_equal(pair_of_lin B);

// генерирует столбец матрицы
std::vector<pair_of_lin> gen_col(int k);

// генерирует строку матрицы
std::vector<point> gen_str(int k);

// генерирует матрицу
std::vector<std::vector<bool>> gen_matrix(int k);


//                      ГРАДИЕНТНЫЙ АЛГОРИТМ

// проверяет наличие единиц в матрице
bool empty_one(std::vector<int> number_of_one);

// подсчитывает вектор количества единиц в строках матрицы
std::vector<int> count_number_one(std::vector<std::vector<bool>> matrix, std::vector<bool> flags);

// ищет максимум во входном векторе
int find_max(std::vector<int> seq);

// удаляет столбец из матрицы, меняя вектор количества единиц в строке
void delete_column(int index_col, std::vector<std::vector<bool>>& matrix, std::vector<int>& ones);

// удаляет одну строку. При real_string = true удаляет, добавляя в покрытие, иначе не добавляя
void delete_one(int index_string, std::vector<std::vector<bool>>& matrix, 
                                  std::vector<bool>& flags, bool real_string, 
                                  std::vector<int>& ones);

// проверяет, все ли столбцы покрыты
bool all_col_under(std::vector<bool> flags);

// удаляет блок строк
void delete_str_block(int index_string, std::vector<std::vector<bool>>& matrix, std::vector<bool>& flags, int k, 
                                        std::vector<int>& ones);

// реализует градиентный алгоритм
std::vector<int> grad_algo(std::vector<std::vector<bool>> matrix, int k);

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

// выводит в std::cout функцию, заданную таблицей значений
void print_function(int k, std::vector<std::vector<int>> matrix);

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
  
  //for (int i = 0; i < list.size(); ++i)
    //std::cout << list[i] + 1 << " ";
  if (list.size() == 0)
  { 
    std::cout << "Impossible";
    //std::cerr << "Impossible" << std::endl;
  }
  if (list.size() > 0)
  {
    std::cout << "Possible, size = " << list.size() << std::endl;
    get_and_print(k, list);
  }
  std::cout << std::endl;
  
  return 0;
}

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

void print_matrix_byte(int k, std::vector<std::vector<bool>> matrix)
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
	while (j + step < matrix[0].size()) // 7?
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

std::stack<bool> create_seq_by_int(int c, int size)
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

std::vector<std::vector<bool>> read_matrix_byte()
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
	  auto seq = create_seq_by_int(c, step);
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
	  auto seq = create_seq_by_int(c, m%step);
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
        //std::cout << "-1 ";
        std::cout << "- ";
      else
        std::cout << matrix[i][j] << " ";
    std::cout << std::endl;
  }
  return;
}

void get_and_print(int k, std::vector<int> list_of_strings)
{
  //int t = 0;
  std::vector<point> answer;
//  int k = 12;
  //std::cin >> k;
  for (auto t = list_of_strings.begin(); t != list_of_strings.end(); ++t)
//  while (std::cin >> t)
  {
	point tmp = get_point_by_int(k, (*t));
	answer.push_back(tmp);
  }
  
  auto funct = get_function(k, answer);
  print_function(k, funct);
  return;  
}

