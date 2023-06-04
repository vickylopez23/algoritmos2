#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x>=0){
        y=x;
    }
    else{
        y=-x;
    }
}

int main(void) {
    int a=0, r=0;

    a=-10;
    absolute(a,r);
    printf ("Valor de absoluto: %d \n",r);

    return EXIT_SUCCESS;
}
//En el teorico  10

//Muestra 0 por pantalla
