#ifndef TYPES_H
#define TYPES_H

// Определения типов для проекта анализатора аномалий
typedef int data_t;  // Основной тип данных для массива

// Константы для анализа аномалий
#define NORMAL_MIN 50
#define NORMAL_MAX 70
#define ANOMALY_LOW_MAX 10
#define ANOMALY_HIGH_MIN 9000
#define ANOMALY_HIGH_MAX 10000

// Размеры и параметры
#define DEFAULT_ARRAY_SIZE 288
#define DEFAULT_WINDOW_SIZE 20
#define DEFAULT_ANOMALY_PERCENT 5

#endif // TYPES_H
