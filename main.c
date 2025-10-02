// 1.генерация тестовых данных
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// объявления функций
void massive(int *massiv, int lenght, int an);
void mix(int *massiv, int len_massiv);
int aver(int *massiv, int len_massiv);
int maximum(int *massiv, int len_massiv);
int minimum(int* massiv, int len_massiv);
int mediana(int* massiv, int len_massiv);
void copy_massive(int* massiv1, int* massiv2, int len_massiv);
int filter(int* filtered, int len_all);
void mark(int* all, char all_marked[][20], int len_all);
void tablo(int average, int average_filtered, int max, int max_filtered, int min, int min_filtered, int median, int median_filtered, int found_anom, int fixed_anom);
void draw_anomaly_graph(int* massiv, int len, int window_size);

void massive(int *massiv, int lenght,int an){
    srand(time(0));               // инициализация генератора
    int int_len_correct=lenght*(100-an)/100;  //
    int int_len_incorrect=lenght-int_len_correct;
    
    
    int correct[int_len_correct];
    for (int i=0;i<int_len_correct;i++){
        correct[i]=rand()%21 +50; // остаток от деления на 21 лежит в диапазоне от 0 до 20
    }
    int incorrect[int_len_incorrect];
    for (int j=0;j<int_len_incorrect;j++){
        if (rand()%2==0){
            incorrect[j]=rand()%11;  // диапазон от 0 до 10
        }else{
            incorrect[j]=rand()%1001+9000;  // диапазон от 9000 до 10000
        }
    }
    
    for (int k=0;k<int_len_correct;k++){
        massiv[k]=correct[k];
    }
    for (int m=0;m<int_len_incorrect;m++){
        massiv[int_len_correct+m]=incorrect[m];
    }
}


    // перемешивание массива all
void mix(int *massiv, int len_massiv){
    for (int i = 0; i < len_massiv; i++) {
        int j = rand() % len_massiv;  // случайный индекс
        int x = massiv[i];
        massiv[i] = massiv[j];
        massiv[j] = x;
    }
}

// 2. статистический анализ 
int aver(int *massiv, int len_massiv){  //
    int sum=0;
    for (int n=0;n<len_massiv;n++){
        sum+=massiv[n];
    }
    int average=sum/len_massiv;
    return average;
}

int maximum(int *massiv,int len_massiv){
    int max=0;
    for (int o=0;o<len_massiv;o++){
        if (massiv[o]>max){
            max=massiv[o];
        }
    }
    return max;
}

int minimum(int* massiv, int len_massiv){
    int min=10001;
    for (int p=0;p<len_massiv;p++){
        if (massiv[p]<min){
            min=massiv[p];
        }
    }
    return min;
}
int mediana(int* massiv,int len_massiv){
    int all_sorted[len_massiv];
    
    for (int i = 0; i < len_massiv; i++) {
        all_sorted[i] = massiv[i];
    }
    for (int i = 0; i < len_massiv - 1; i++) { //сортировка по возрастанию
        for (int j = 0; j < len_massiv - i - 1; j++) {
            if (all_sorted[j] > all_sorted[j + 1]) {
                int x= all_sorted[j];
                all_sorted[j] = all_sorted[j + 1];
                all_sorted[j + 1] = x;
            }
        }
    }
    int median=all_sorted[len_massiv/2];
    return median;
}
   
void copy_massive(int* massiv1,int* massiv2 ,int len_massiv){
    for (int i = 0; i < len_massiv; i++) {
        massiv2[i] = massiv1[i];
    }
}
    
    

    
//3. фильтрация аномалий
int filter(int* filtered,int len_all) {
        // заменяю аномалии на среднее арифметическое соседних нормальных значений
    int found_anom=0;
    int fixed_anom=0;
    for (int i = 0; i < len_all; i++) {
        if (filtered[i] < 50 || filtered[i] > 70) {
            found_anom+=1;
            int left_normal = -1; // поиск левого нормального значения
            int index_left= -1;
            for (int j = i - 1; j >= 0; j--) {
                if (filtered[j] >= 50 && filtered[j] <= 70) {
                    left_normal = filtered[j];
                    index_left = j;
                    break;
                }
            }
            int right_normal = -1; //поиск правого нормального значения
            int index_right = -1;
            for (int j = i + 1; j < len_all; j++) {
                if (filtered[j] >= 50 && filtered[j] <= 70) {
                    right_normal = filtered[j];
                    index_right = j;
                    break;
                }
            }
                //если справа и слева от аномалии нормальные значения:
            if (left_normal != -1 && right_normal != -1) {
                filtered[i] = (left_normal + right_normal) / 2;
                fixed_anom+=1;
            } else if (left_normal != -1) {
                    // если не нашлось правого нормального значения , ищем второе левое
                int second_left = -1;
                for (int j = index_left - 1; j >= 0; j--) {
                    if (filtered[j] >= 50 && filtered[j] <= 70 ) {
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
                    if (filtered[j] >= 50 && filtered[j] <= 70 ) {
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
void mark(int* all, char all_marked[][20], int len_all){
    //char all_marked[len_all][20]; //выделяем аномалии как строки
    for (int k = 0; k < len_all; k++) {
        if (all[k] < 50 || all[k] > 70) {
            sprintf(all_marked[k], "{%d}", all[k]);
        } else {
            sprintf(all_marked[k], "%d", all[k]);
        }
    }
}

    // таблица из аски символов
void tablo(int average, int average_filtered,int max,int max_filtered,int min,int min_filtered, int median, int median_filtered, int found_anom, int fixed_anom){
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

// функция для рисования графика аномалий
void draw_anomaly_graph(int* massiv, int len, int window_size) {
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════════════════════\n");
    printf("                           ГРАФИК ДИНАМИКИ АНОМАЛИЙ                               \n");
    printf("═══════════════════════════════════════════════════════════════════════════════════\n");
    printf("'█' - аномалия, '·' - нормальное значение\n");
    printf("\n");
    
    //  количество окон
    int windows = len / window_size;
    if (len % window_size != 0){
        windows++;
    }
    
    // для каждого окна считаем процент аномалий
    for (int w = 0; w < windows; w++) {
        int start = w * window_size;
        int end = start + window_size;
        if (end > len){
            end = len;
        } 
        
        int anomalies = 0;
        int total = end - start;
        
        //  аномалии в окне
        for (int i = start; i < end; i++) {
            if (massiv[i] < 50 || massiv[i] > 70) {
                anomalies++;
            }
        }
        
        float anomaly_percent = (float)anomalies / total * 100;
        
        //  график
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

    
int main(void){
    int len=2000;
    int massiv[len];
    int massiv2[len];
    char massiv3[len][20];
    massive(massiv,len ,5); //заполнила массив
    mix(massiv,len); //перемешала его
    
    int sr_arifm1=aver(massiv,len ); 
    int max1=maximum(massiv,len );
    int min1=minimum(massiv, len);
    int med1=mediana(massiv, len);
    copy_massive(massiv, massiv2, len);
    int found_anom = filter(massiv2, len);
    mark(massiv, massiv3, len);

    // cтатистический анализ после фильтрации
    int sr_arifm2 = aver(massiv2, len);
    int max2 = maximum(massiv2, len);
    int min2 = minimum(massiv2, len);
    int med2 = mediana(massiv2, len);

    printf("Первые 50 элементов массива с выделенными аномалиями:\n");

    int len_for_print = (50 > len ? len: 50);
    for (int l = 0; l < len_for_print; l++) {
        printf("%s\n", massiv3[l]);
    }

    // вывод графика динамики аномалий
    draw_anomaly_graph(massiv, len, 20); 

    // вывод статистической таблицы
    tablo(sr_arifm1, sr_arifm2, max1, max2, min1, min2, med1, med2, found_anom, found_anom);
    
    return 0;
}
