// СТРУКТУРЫ
#ifndef STRUCTURES_H
#define STRUCTURES_H

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


#endif
