//                    ВОССТАНОВЛЕНИЕ УНИВЕРСАЛЬНОЙ ФУНКЦИИ
#ifndef GET_UNIVERSAL_FUNCTION_H
#define GET_UNIVERSAL_FUNCTION_H

// Возвращает точку с определением, соответствующую номеру строки string_number
point get_point_by_string_number(int k, int string_number);

// создает таблицу функции из набора точек со значениями функций
std::vector<std::vector<int>> get_function_by_points(int k, std::vector<point> list_of_values);

// считывает набор строк и выводит в std::cout функцию
std::vector<std::vector<int>> get_univ_function_by_coverage(int k, std::vector<int> list_of_strings);

#endif
