#include <stdio.h>
#include <math.h>
	#define MAX_LEITURAS 20

int main(void) {
      float sensor;
      double temperatura;
      double temperaturas[MAX_LEITURAS];
      int numero_leituras = 0;
      double temperatura_maxima;
      double temperatura_minima;
      double soma_temperaturas = 0;
      double temperatura_media;
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
            if (sensor == -1){
                  break;
            }
            temperatura = (((260*sensor)/1023.0)-20);
            if(temperatura >= -10 && temperatura<= 190){
                  printf("Temperatura: %.2f\n", temperatura);
		temperaturas[numero_leituras] = temperatura;
		numero_leituras++;
            }
            else{
                  printf("Valor fora da gama\n");
            }
	   if(numero_leituras == MAX_LEITURAS){
		break;
		}
            }

	for ( int i = 0; i < numero_leituras; i++) {
		printf("%.2f\n", temperaturas[i]);
			}
		printf("Número de temperaturas registadas: %d\n", numero_leituras);

	if (numero_leituras > 0) {
    		temperatura_maxima = temperaturas[0];

    	for (int i = 1; i < numero_leituras; i++) {
        	if (temperaturas[i] > temperatura_maxima) {
            		temperatura_maxima = temperaturas[i];
        		}
    		}

    		printf("Temperatura máxima: %.2f\n", temperatura_maxima);
		}

 if (numero_leituras > 0) {
                temperatura_minima = temperaturas[0];

        for (int i = 1; i < numero_leituras; i++) {
                if (temperaturas[i] < temperatura_minima) {
                        temperatura_minima = temperaturas[i];
                        }
                }

                printf("Temperatura mínima: %.2f\n", temperatura_minima);
                }

	if (numero_leituras > 0) {
    soma_temperaturas = 0;

    for (int i = 0; i < numero_leituras; i++) {
        soma_temperaturas += temperaturas[i];
    }

    temperatura_media = soma_temperaturas / numero_leituras;

    printf("Temperatura média: %.2f\n", temperatura_media);

       soma_quadrados = 0;

for (int i = 0; i < numero_leituras; i++) {
    soma_quadrados += (temperaturas[i] - temperatura_media) *
                      (temperaturas[i] - temperatura_media);
}

desvio_padrao = sqrt(soma_quadrados / numero_leituras);

printf("Desvio-padrão: %.2f\n", desvio_padrao);
}

	
return 0;
}
