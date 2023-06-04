#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    
    FILE * file;
    file = fopen(filepath,"r");
    int num;
    unsigned int cont = 0u;
    unsigned int len;

    while(fscanf(file,"%d",&num) != EOF){
        if(cont==0){
            len = num;
            assert(len <= max_size);
        }
        else{
            array[cont-1]=num;
        }
        ++cont;
    }

    fclose(file);
    return(len);

    
}

void array_dump(int a[], unsigned int length) {
    
    printf("[");

    for (unsigned int i = 0u; i < length; ++i) {
        if (i == length-1) {
            printf("%d", a[i]);
        }
        else {
            printf("%d, ", a[i]);
        }
    }

    printf("] \n");
}


bool array_is_sorted(int a[], unsigned int length){
    bool sort = true; //true = sorted
    for (unsigned int i = 0; i < length-1; ++i){ //length-1 porque no quiero que se salga del array en el ultimo elemento
        if (a[i]>a[i+1]){ //si el elemento actual es mayor que el siguiente
            sort = false;  //no esta ordenado
        }
    }
    return(sort); //devuelvo el valor de sort
}