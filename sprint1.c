#include <stdio.h>

int main(void){
    float tempi;
    float tempf;
    scanf("%f",&tempi);
    tempf = (260 * tempi) / 1023 - 20;
    printf("A temperatura é:  %.2f\n",tempf);
    return 0;
}
