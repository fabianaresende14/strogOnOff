#include <stdio.h>

int main(void) {

    float sensor; // float para não aceitar numeros decimais
    double temperatura;

    printf("Escreva o valor que apareceu no sensor: ");
    
    if (sensor >= 0 && sensor <= 1023) {

        temperatura = (((260 * sensor) / 1023.0) - 20);

        if (temperatura >= -10 && temperatura <= 190) {
            printf("%.2f\n", temperatura);
        }
        else {
            printf("Valor fora da gama\n");
        }
    }

    else {
        printf("Valor fora da gama\n");
    }

    return 0;
}
