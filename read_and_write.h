// ЧТЕНИЕ И ВЫВОД
#ifndef READ_AND_WRITE_H
#define READ_AND_WRITE_H

//                        ЧТЕНИЕ И ВЫВОД

// выводит матрицу на std::cout
void print_matrix(int k, std::vector<std::vector<bool>> matrix);

// выводит кодированную матрицу на std::cout
void code_print_matrix(int k, std::vector<std::vector<bool>> matrix);

// считывает матрицу из std::cin 
std::vector<std::vector<bool>> read_matrix();

// для кодирования матрицы
std::stack<bool> create_sequence_by_int(int c, int size);

// считывает кодированную матрицу из std::cin
std::vector<std::vector<bool>> code_read_matrix();

// выводит в std::cout функцию, заданную таблицей значений
void print_function(int k, std::vector<std::vector<int>> matrix);

#endif

