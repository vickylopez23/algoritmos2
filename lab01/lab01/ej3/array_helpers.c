#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    // Abrir el archivo en modo lectura                            
    FILE *file = fopen(filepath, "r"); 
    int num; // Número leído del archivo
    unsigned int cont = 0u; // Contador de elementos leídos
    unsigned int len; // Longitud de la matriz
    //leo el arch hasta el final
    while(fscanf (file,"%d",&num)!= EOF){
         if(cont==0){   // Si es el primer número, es la longitud de la matriz
            len = num; // Guardar la longitud de la matriz
            assert(len <= max_size); // Verificar que la longitud de la matriz no exceda el máximo permitido
        }
        else{
            array[cont-1]=num; // Guardar el número leído en el array
        }
        ++cont; // Incrementar el contador de elementos leídos
    }

    fclose(file); // Cerrar el archivo
    return(len); // Devolver la longitud de la matriz

    
}
    


void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0; i < length; ++i) {
        if (i == length -1){
            printf("%d", a[i]); // Imprimir el elemento sin coma
        }
        else {
            printf("%d, ", a[i]); // Imprimir el elemento con coma
        }
    }

    printf("] \n"); // Imprimir el corchete final
}