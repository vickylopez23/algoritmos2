#include <stdlib.h>
#include <stdbool.h>

size_t string_length(const char *str) {
    size_t c = 0;
    if(str != NULL) {
        while(true) { // recorro el string hasta encontrar el caracter nulo
            if(str[c] == '\0') { // si el caracter es nulo
                break; // termino el ciclo
            } else { // si no
                c++; // incremento el contador
            }
        }

    }
    return c;
}

//retorna un string con todos los caracteres c removidos
char *string_filter(const char *str, char c) {
    size_t unfiltered_length = string_length(str); // longitud del string sin filtrar
    char *filtered = malloc(unfiltered_length+1); // sumo 1 para el caracter nulo
    size_t j = 0; // indice para el string filtrado

    for(unsigned int i=0; i<=unfiltered_length; i++) { // recorro el string sin filtrar
        if(str[i]!=c) { // si el caracter no es c
            filtered[j] = str[i]; // lo agrego al string filtrado
            j++; // incremento el indice del string filtrado
        }
    }

    filtered = realloc(filtered, sizeof(char)*j); // redimensiono el string filtrado

    return filtered;
}