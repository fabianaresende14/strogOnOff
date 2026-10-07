#include <stdio.h>

int main(void) {

    float sensor;
    double temperatura;

    printf("Escreva o valor que apareceu no sensor: ");

    while ((scanf("%f", &sensor) != 1) || (sensor != (int)sensor)) {
        printf("Valor invalido. Escreva um valor inteiro: ");

        while (getchar() != '\n');
    }

    if (sensor < 0 || sensor > 1023) {
        printf("Valor fora da gama\n");
    }
    else {

        temperatura = ((260 * sensor) / 1023.0) - 20;

        if (temperatura < -10 || temperatura > 190) {
            printf("Valor fora da gama\n");
        }
        else {
            printf("%.2f\n", temperatura);
        }
    }

    return 0;
}
