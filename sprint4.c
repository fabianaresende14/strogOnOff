#include <stdio.h> 
#include <math.h>
#define número_máximo_leituras 20 

int main(void) {
      float sensor;
      double temperatura;
      int valores_lidos = 0;
      int sensores[número_máximo_leituras];
      double temperaturas[número_máximo_leituras];
      double soma = 0.0;
      double soma_quadrados = 0;
      double desvio_padrao;
 
      while(1){
            do {
                  printf("Escreva o valor que apareceu no sensor(-1 para sair): ");
                  if ((scanf("%f", &sensor) !=1) || (sensor != (int)sensor) || (sensor < 0 || sensor > 1023)  && (sensor != -1)) {
                        printf("Erro, insira um valor válido\n");
                        while (getchar() != '\n');
                  }
                  else{
                        break;
                  }
                  } while(1);

       if (sensor == -1 || valores_lidos >= 20){
                  break;
       }


            temperatura = (((260*sensor)/1023.0)-20);
            sensores[valores_lidos] = sensor;

       if(temperatura >= -10 && temperatura<= 190){
            printf("Temperatura: %.2f\n", temperatura);
            temperaturas[valores_lidos] = temperatura;
            valores_lidos++;
      }
 
      else{
            printf("Valor fora da gama\n");
      }
  }
   double mínimo = temperaturas[0];
   double máximo = temperaturas[0];

     for (int i = 0; i < valores_lidos; i++) {
         soma += temperaturas[i];
         if(temperaturas[i] < mínimo) {
            mínimo = temperaturas[i];
         }
         if(temperaturas[i] > máximo) {
           máximo = temperaturas[i];
         }
     }
        double media = soma / valores_lidos;
        printf(" Valores lidos (sensor -> temperatura):\n");
     for(int i=0; i < valores_lidos; i++) {  
         printf("%d->%.2f\n", sensores[i], temperaturas[i]);
     }
     for(int i=0; i < valores_lidos; i++) {
         soma_quadrados += (temperaturas[i] - media) * (temperaturas[i] - media);
     }
     desvio_padrao = sqrt(soma_quadrados / valores_lidos);
 
      printf("Número de valores lidos:%d\n", valores_lidos);
      printf("Temperatura mínima: %.2f\n", mínimo);
      printf("Temperatura máxima: %.2f\n", máximo);
      printf("Temperatura média: %.2f\n", media);
      printf("Desvio-padrão: %.2f\n", desvio_padrao);

      return 0;
 }
