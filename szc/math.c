#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/math.h"

// 1. Генерация тестовых данных
void massive(data_t *massiv, int length, int anomaly_percent) {
    srand(time(0));               // инициализация генератора
    int int_len_correct = length * (100 - anomaly_percent) / 100;
    int int_len_incorrect = length - int_len_correct;
    
    data_t correct[int_len_correct];
    for (int i = 0; i < int_len_correct; i++) {
        correct[i] = rand() % 21 + NORMAL_MIN; // остаток от деления на 21 лежит в диапазоне от 0 до 20
    }
    
    data_t incorrect[int_len_incorrect];
    for (int j = 0; j < int_len_incorrect; j++) {
        if (rand() % 2 == 0) {
            incorrect[j] = rand() % (ANOMALY_LOW_MAX + 1);  // диапазон от 0 до 10
        } else {
            incorrect[j] = rand() % (ANOMALY_HIGH_MAX - ANOMALY_HIGH_MIN + 1) + ANOMALY_HIGH_MIN;  // диапазон от 9000 до 10000
        }
    }
    
    for (int k = 0; k < int_len_correct; k++) {
        massiv[k] = correct[k];
    }
    for (int m = 0; m < int_len_incorrect; m++) {
        massiv[int_len_correct + m] = incorrect[m];
    }
}

// Перемешивание массива
void mix(data_t *massiv, int len_massiv) {
    for (int i = 0; i < len_massiv; i++) {
        int j = rand() % len_massiv;  // случайный индекс
        data_t x = massiv[i];
        massiv[i] = massiv[j];
        massiv[j] = x;
    }
}

// 2. Статистический анализ 
int aver(data_t *massiv, int len_massiv) {
    int sum = 0;
    for (int n = 0; n < len_massiv; n++) {
        sum += massiv[n];
    }
    int average = sum / len_massiv;
    return average;
}

int maximum(data_t *massiv, int len_massiv) {
    int max = 0;
    for (int o = 0; o < len_massiv; o++) {
        if (massiv[o] > max) {
            max = massiv[o];
        }
    }
    return max;
}

int minimum(data_t *massiv, int len_massiv) {
    int min = 10001;
    for (int p = 0; p < len_massiv; p++) {
        if (massiv[p] < min) {
            min = massiv[p];
        }
    }
    return min;
}

int mediana(data_t *massiv, int len_massiv) {
    data_t all_sorted[len_massiv];
    
    for (int i = 0; i < len_massiv; i++) {
        all_sorted[i] = massiv[i];
    }
    
    // Сортировка по возрастанию
    for (int i = 0; i < len_massiv - 1; i++) {
        for (int j = 0; j < len_massiv - i - 1; j++) {
            if (all_sorted[j] > all_sorted[j + 1]) {
                data_t x = all_sorted[j];
                all_sorted[j] = all_sorted[j + 1];
                all_sorted[j + 1] = x;
            }
        }
    }
    int median = all_sorted[len_massiv / 2];
    return median;
}

// Копирование массива
void copy_massive(data_t *massiv1, data_t *massiv2, int len_massiv) {
    for (int i = 0; i < len_massiv; i++) {
        massiv2[i] = massiv1[i];
    }
}

// 3. Фильтрация аномалий
int filter(data_t *filtered, int len_all) {
    // заменяю аномалии на среднее арифметическое соседних нормальных значений
    int found_anom = 0;
    int fixed_anom = 0;
    
    for (int i = 0; i < len_all; i++) {
        if (filtered[i] < NORMAL_MIN || filtered[i] > NORMAL_MAX) {
            found_anom += 1;
            int left_normal = -1; // поиск левого нормального значения
            int index_left = -1;
            for (int j = i - 1; j >= 0; j--) {
                if (filtered[j] >= NORMAL_MIN && filtered[j] <= NORMAL_MAX) {
                    left_normal = filtered[j];
                    index_left = j;
                    break;
                }
            }
            
            int right_normal = -1; //поиск правого нормального значения
            int index_right = -1;
            for (int j = i + 1; j < len_all; j++) {
                if (filtered[j] >= NORMAL_MIN && filtered[j] <= NORMAL_MAX) {
                    right_normal = filtered[j];
                    index_right = j;
                    break;
                }
            }
            
            //если справа и слева от аномалии нормальные значения:
            if (left_normal != -1 && right_normal != -1) {
                filtered[i] = (left_normal + right_normal) / 2;
                fixed_anom += 1;
            } else if (left_normal != -1) {
                // если не нашлось правого нормального значения , ищем второе левое
                int second_left = -1;
                for (int j = index_left - 1; j >= 0; j--) {
                    if (filtered[j] >= NORMAL_MIN && filtered[j] <= NORMAL_MAX) {
                        second_left = filtered[j];
                        break;
                    }
                }
                if (second_left != -1) {
                    filtered[i] = (left_normal + second_left) / 2;
                }
            } else if (right_normal != -1) {
                // если не нашлось левого нормального значения,ищем второе правое
                int second_right = -1;
                for (int j = index_right + 1; j < len_all; j++) {
                    if (filtered[j] >= NORMAL_MIN && filtered[j] <= NORMAL_MAX) {
                        second_right = filtered[j];
                        break;
                    }
                }
                if (second_right != -1) {
                    filtered[i] = (right_normal + second_right) / 2;
                }
            }
        }
    }
    return found_anom; // возвращаем количество найденных аномалий
}

// Маркировка аномалий
void mark(data_t *all, char all_marked[][20], int len_all) {
    for (int k = 0; k < len_all; k++) {
        if (all[k] < NORMAL_MIN || all[k] > NORMAL_MAX) {
            sprintf(all_marked[k], "{%d}", all[k]);
        } else {
            sprintf(all_marked[k], "%d", all[k]);
        }
    }
}

// Таблица из ASCII символов
void tablo(int average, int average_filtered, int max, int max_filtered, 
           int min, int min_filtered, int median, int median_filtered, 
           int found_anom, int fixed_anom) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           СТАТИСТИЧЕСКИЕ МЕТРИКИ                                \n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                  \n");
    printf("║  ДО ФИЛЬТРАЦИИ:                    ПОСЛЕ ФИЛЬТРАЦИИ:                              \n");
    printf("║                                                                                  \n");
    printf("║  ┌─────────────────┐              ┌─────────────────┐                              \n");
    printf("║  │ Среднее: %6d │              │ Среднее: %6d │                              \n", average, average_filtered);
    printf("║  └─────────────────┘              └─────────────────┘                              \n");
    printf("║                                                                                  \n");
    printf("║  ┌─────────────────┐              ┌─────────────────┐                              \n");
    printf("║  │ Максимум:%6d │              │ Максимум:%6d │                              \n", max, max_filtered);
    printf("║  └─────────────────┘              └─────────────────┘                              \n");
    printf("║                                                                                  \n");
    printf("║  ┌─────────────────┐              ┌─────────────────┐                            \n");
    printf("║  │ Минимум: %6d │              │ Минимум: %6d │                            \n", min, min_filtered);
    printf("║  └─────────────────┘              └─────────────────┘                            \n");
    printf("║                                                                                  \n");
    printf("║  ┌─────────────────┐              ┌─────────────────┐                            \n");
    printf("║  │ Медиана: %6d │              │ Медиана: %6d │                              \n", median, median_filtered);
    printf("║  └─────────────────┘              └─────────────────┘                            \n");
    printf("║                                                                                  \n");
    printf("║  ┌─────────────────┐              ┌─────────────────┐                            \n");
    printf("║  │ Количество: 288 │              │ Количество: 288 │                            \n");
    printf("║  └─────────────────┘              └─────────────────┘                            \n");
    printf("║                                                                                  \n");
    printf("║  ┌─────────────────┐              ┌─────────────────┐                            \n");
    printf("║  │Найдено аном.:%3d│              │Найдено аном.:%3d│                              \n", found_anom, found_anom);
    printf("║  └─────────────────┘              └─────────────────┘                            \n");
    printf("║                                                                                  \n");
    printf("║  ┌─────────────────┐              ┌─────────────────┐                            \n");
    printf("║  │ Исправлено: %3d │              │ Исправлено: %3d │                              \n", fixed_anom, fixed_anom);
    printf("║  └─────────────────┘              └─────────────────┘                            \n");
    printf("║                                                                                  \n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

// Функция для рисования графика аномалий
void draw_anomaly_graph(data_t *massiv, int len, int window_size) {
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════════════════════\n");
    printf("                           ГРАФИК ДИНАМИКИ АНОМАЛИЙ                               \n");
    printf("═══════════════════════════════════════════════════════════════════════════════════\n");
    printf("'█' - аномалия, '·' - нормальное значение\n");
    printf("\n");
    
    // количество окон
    int windows = len / window_size;
    if (len % window_size != 0) windows++;
    
    // для каждого окна считаем процент аномалий
    for (int w = 0; w < windows; w++) {
        int start = w * window_size;
        int end = start + window_size;
        if (end > len) {
            end = len;
        } 
        
        int anomalies = 0;
        int total = end - start;
        
        // подсчет аномалий в окне
        for (int i = start; i < end; i++) {
            if (massiv[i] < NORMAL_MIN || massiv[i] > NORMAL_MAX) {
                anomalies++;
            }
        }
        
        float anomaly_percent = (float)anomalies / total * 100;
        
        // отрисовка графика
        printf("Окно %2d [%3d-%3d]: ", w+1, start+1, end);
        
        int bar_length = 50;
        int filled_length = (int)(anomaly_percent / 100 * bar_length);
        
        for (int i = 0; i < bar_length; i++) {
            if (i < filled_length) {
                printf("█");
            } else {
                printf("·");
            }
        }
        
        printf(" %5.1f%% (%d/%d)\n", anomaly_percent, anomalies, total);
    }
    
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════════════════════\n");
}
