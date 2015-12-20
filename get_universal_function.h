//                    ВОССТАНОВЛЕНИЕ УНИВЕРСАЛЬНОЙ ФУНКЦИИ
#ifndef GET_UNIVERSAL_FUNCTION_H
#define GET_UNIVERSAL_FUNCTION_H

// Возвращает точку с определением, соответствующую номеру строки t
point get_point_by_int(int k, int t);

// создает таблицу функции из набора точек со значениями функций
std::vector<std::vector<int>> get_function(int k, std::vector<point> seq);

// считывает набор строк и выводит в std::cout функцию
void get_and_print(int k, std::vector<int> list_of_strings);

#endif
