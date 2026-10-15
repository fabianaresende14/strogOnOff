
#include <stdio.h>

int main(void) {

    float sensor;
    double temperatura;

    printf("Escreva o valor que apareceu no sensor (introduza "-1" para sair do programa): ");

    while (1) {

        if ((scanf("%f", &sensor) != 1) || (sensor != (int)sensor)) {

            printf("Valor invalido.");

            while (getchar() != '\n');

        }
        else {

            if (sensor == -1) {
                break;
            }

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
        }

        printf(" Escreva o valor que apareceu no sensor: ");
    }

    return 0;
}
