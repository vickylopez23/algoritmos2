#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if (x>=0){
        *y=x;
    }
    else{
        *y=-x;
    }
}

int main(void) {
    int a=0, res=0;
    a=-10;  
    int *p= &res;    
    absolute (a,p);  
    res= *p;         
    printf ("Valor absoluto es : %d \n",res);

    return EXIT_SUCCESS;
}
