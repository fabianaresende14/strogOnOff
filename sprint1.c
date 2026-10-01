#include <stdio.h>

int main(void){
    double tempi;
    double tempf;
    scanf("%f",&tempi);
    tempf = (260 * tempi) / 1023.0 - 20;
    printf("A temperatura é:  %.2f\n",tempf);
    return 0;
}
