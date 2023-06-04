#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    //scanf("%s", user_input);
    fgets(user_input, MAX_LENGTH, stdin); // lee hasta MAX_LENGTH-1 caracteres o hasta encontrar un \n

    if ((strlen(user_input)>0) && (user_input[strlen (user_input) - 1] == '\n')) // si el ultimo caracter es un \n
        user_input[strlen (user_input) - 1] = '\0'; // lo reemplazo por un \0
        
    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);
    return EXIT_SUCCESS;
}


