#ifndef MATH_H
#define MATH_H

#include "types.h"

// Функции генерации данных
void massive(data_t *massiv, int length, int anomaly_percent);
void mix(data_t *massiv, int len_massiv);

// Статистические функции
int aver(data_t *massiv, int len_massiv);
int maximum(data_t *massiv, int len_massiv);
int minimum(data_t *massiv, int len_massiv);
int mediana(data_t *massiv, int len_massiv);

// Функции работы с массивами
void copy_massive(data_t *massiv1, data_t *massiv2, int len_massiv);

// Функции фильтрации и анализа аномалий
int filter(data_t *filtered, int len_all);
void mark(data_t *all, char all_marked[][20], int len_all);

// Функции вывода и визуализации
void tablo(int average, int average_filtered, int max, int max_filtered, 
           int min, int min_filtered, int median, int median_filtered, 
           int found_anom, int fixed_anom);
void draw_anomaly_graph(data_t *massiv, int len, int window_size);

#endif // MATH_H
