//                     ГРАДИЕНТНЫЙ АЛГОРИТМ С МОДИФИКАЦИЕЙ
#ifndef MOD_GRAD_ALGO_H
#define MOD_GRAD_ALGO_H

//                     ГРАДИЕНТНЫЙ АЛГОРИТМ С МОДИФИКАЦИЕЙ

// возвращает номер строки по точке
int number_by_mod(int k, point A);

// возвращает модицикации для создания "рамки"
std::vector<point> gen_list_of_modify_bounds(int k);

// реализует градиентный алгоритм с предварительной модификацией -- по умолчанию добавляет в покрытие все строки из mods
std::vector<int> grad_algo_with_mod(std::vector<std::vector<bool>> matrix, int k, std::vector<point> mods);


#endif
