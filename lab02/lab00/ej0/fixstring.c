#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

//devuelve la longitud de la cadena guardada en el parámetro s
unsigned int fstring_length(fixstring s) {
    unsigned int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}


    

//, la función fstring_eq() indica si las cadenas s1 y s2 son iguales (contienen la misma cadena),
bool fstring_eq(fixstring s1, fixstring s2) {
    bool eq = true;
    unsigned int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        eq = eq && s1[i] == s2[i];
        i++;
    }
    return eq;
}
///indica si la cadena guardada en s1 es menor o igual que la guardada en s2 en el sentido
//del orden alfabético
bool fstring_less_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) {
            return true;
        } else if (s1[i] > s2[i]) {
            return false;
        }
        i++;
    }
    return true;
}

