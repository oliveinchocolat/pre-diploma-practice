//                      ГРАДИЕНТНЫЙ АЛГОРИТМ
#ifndef GRAD_ALGO_H
#define GRAD_ALGO_H
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

#endif
