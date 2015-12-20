// ГЕНЕРАЦИЯ МАТРИЦЫ
#ifndef GENERATION_H
#define GENERATION_H

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

#endif
