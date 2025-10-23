# Makefile для проекта анализатора аномалий
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
TARGET = anomaly_analyzer
SOURCES = main.c szc/math.c
OBJECTS = $(SOURCES:.c=.o)

# Основная цель
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Компиляция объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Установка зависимостей (если нужно)
install:
	@echo "Установка зависимостей не требуется"

.PHONY: all clean run install
