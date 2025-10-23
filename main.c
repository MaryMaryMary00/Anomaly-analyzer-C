// Анализатор аномалий - главный файл
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/math.h"

int main(void) {
    int len = DEFAULT_ARRAY_SIZE;
    data_t massiv[len];
    data_t massiv2[len];
    char massiv3[len][20];
    
    // Генерация и перемешивание данных
    massive(massiv, len, DEFAULT_ANOMALY_PERCENT);
    mix(massiv, len);
    
    // Статистический анализ до фильтрации
    int sr_arifm1 = aver(massiv, len); 
    int max1 = maximum(massiv, len);
    int min1 = minimum(massiv, len);
    int med1 = mediana(massiv, len);
    
    // Копирование и фильтрация
    copy_massive(massiv, massiv2, len);
    int found_anom = filter(massiv2, len);
    mark(massiv, massiv3, len);

    // Статистический анализ после фильтрации
    int sr_arifm2 = aver(massiv2, len);
    int max2 = maximum(massiv2, len);
    int min2 = minimum(massiv2, len);
    int med2 = mediana(massiv2, len);

    // Вывод результатов
    printf("Первые 50 элементов массива с выделенными аномалиями:\n");
    for (int l = 0; l < 50; l++) {
        printf("%s\n", massiv3[l]);
    }

    // Вывод графика динамики аномалий
    draw_anomaly_graph(massiv, len, DEFAULT_WINDOW_SIZE); 

    // Вывод статистической таблицы
    tablo(sr_arifm1, sr_arifm2, max1, max2, min1, min2, med1, med2, found_anom, found_anom);
    
    return 0;
}