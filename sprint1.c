#include <stdio.h>
int main(void) {
      float sensor;//float para não aceitar numeros decimais
      double temperatura;
      printf("Escreva o valor que apareceu no sensor: ");
      if ((scanf("%f", &sensor) !=1) || (sensor != (int)sensor)) {
          return (printf("Erro\n"));
      }
      else if (sensor >= 0 && sensor <= 1023) {
            temperatura = (((260*sensor)/1023.0)-20);
            printf("Temperatura: %.2f\n", temperatura);
      }
      
      else{
            printf("Erro\n");
      }

      return 0;
 }
