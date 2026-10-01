#include <stdio.h>
int main(void) {
      int sensor;
      printf("Escreva o valor que apareceu no sensor:");
      scanf("%d", &sensor);

      if (sensor >= 0 && sensor <= 1023) {
            double temperatura = (((260*sensor)/1023.0)-20);
            printf("Temperatura:%.2f\n", temperatura);
      }
      else{
            printf("Erro\n");
      }

      return 0;
 }
