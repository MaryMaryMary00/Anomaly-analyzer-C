#!/bin/bash
# Простой скрипт сборки проекта анализатора аномалий

echo "Компиляция проекта анализатора аномалий..."

# Компиляция
gcc -Wall -Wextra -std=c99 -I./include main.c szc/math.c -o anomaly_analyzer

if [ $? -eq 0 ]; then
    echo "✅ Компиляция успешна!"
    echo "Запуск программы:"
    echo "  ./anomaly_analyzer"
else
    echo "❌ Ошибка компиляции!"
    exit 1
fi
