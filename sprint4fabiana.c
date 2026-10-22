#include <stdio.h>
#define numeromaxleituras 20
#include <math.h>

int main(void) {
      float sensor;
      double temperatura;
      int valoresLidos = 0;
      double soma = 0.0;
      int sensores[numeromaxleituras];
      double temperaturas[numeromaxleituras];
      double somaQuadrados = 0;
      double desvioPadrao;

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


            if (sensor == -1 || valoresLidos >= 20){

                  break;
            }
            temperatura = (((260*sensor)/1023.0)-20);

           if(temperatura >= -10 && temperatura<= 190){
                  printf("Temperatura: %.2f\n", temperatura);
                sensores[valoresLidos] = sensor;
            temperaturas[valoresLidos] = temperatura;
            valoresLidos++;

            }
            else{
                  printf("Valor fora da gama\n");
                }
                 }

      double minimoTemp = temperaturas[0];
      double maxTemp = temperaturas[0];
    

        for (int i = 0; i < valoresLidos; i++) {
            soma += temperaturas[i];
            if (temperaturas[i] < minimoTemp) {
            minimoTemp = temperaturas[i];
}
            if (temperaturas[i] > maxTemp) {
            maxTemp = temperaturas[i];
}
}
     double media = soma / valoresLidos;
        for(int i = 0; i < valoresLidos; i++) {
        printf("%d->%.2f\n", sensores[i], temperaturas[i]);
}
        for(int i = 0; i < valoresLidos; i++) {
        somaQuadrados += (temperaturas[i] - media) * (temperaturas[i] - media) ;
}
        desvioPadrao = sqrt(somaQuadrados / valoresLidos);


        printf("Número de valores lidos: %d\nTemperatura mínima: %.2f\nTemperatura máxima: %.2f\nTemperatura média: %.2f\nDesvio-padrão: %.2f\n", valoresLidos, minimoTemp, maxTemp, media, desvioPadrao);
      return 0;
 }

