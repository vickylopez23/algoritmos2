#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.exists = 0;
    res.where = 0;
    int max = arr[0];
    int min = arr[0];
    for (unsigned int i = 0; i < length;i++){ 
        if (arr[i] == value){ 
            res.exists = 1;
            res.where = i;   
        }
        if (arr[i] > max){
            max = arr[i];
        }
        if (arr[i] < min){
            min = arr[i];
        }
    }
    res.is_upperbound = max <= value;
    res.is_lowerbound = min >= value;
    return res;
}



int main(void) {
    int a[ARRAY_SIZE] = {0, -1, 9, 4};
    int value;
    scanf("%i", &value);
    printf("Ahora ingresa los valores de cada elemento del array de %d elementos\n", ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++){
        scanf("%i", &a[i]);
    }
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    printf("%d", result.is_upperbound); // Imprime 1
    printf("%d", result.is_lowerbound); // Imprime 0
    printf("%u", result.exists);        // Imprime 1
    printf("%u", result.where);         // Imprime 2

    return EXIT_SUCCESS;
}
