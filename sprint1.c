#include <stdio.h>
int main(void) {
      int sensor;
      double temperatura;
      printf("Escreva o valor que apareceu no sensor:");

      if (scanf("%d", &sensor) !=1) {
          return (printf("Error\n");
      }
      else if (sensor >= 0 && sensor <= 1023) {
            temperatura = (((260*sensor)/1023.0)-20);
            printf("Temperatura:%.2f\n", temperatura);
      }
      else{
            printf("Erro\n");
      }

      return 0;
 }
