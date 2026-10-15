#include <stdio.h>
int main(void) {
      float sensor;
      double temperatura;
      while(1){
            do {
                  printf("Escreva o valor que apareceu no sensor(-1 para sair): ");
                  if ((scanf("%f", &sensor) !=1) || (sensor != (int)sensor) || (sensor < 0 || sensor > 1023)  && (sensor != -1)) {
                        printf("Erro\n");
                        while (getchar() != '\n');
                  }
                  else{
                        break;
                  }
                  } while(1);
            if (sensor == -1){
                  break;
            }
            temperatura = (((260*sensor)/1023.0)-20);
            if(temperatura >= -10 && temperatura<= 190){
                  printf("Temperatura: %.2f\n", temperatura);
            }
            else{
                  printf("Valor fora da gama\n");
            }
            }
      return 0;
 }
