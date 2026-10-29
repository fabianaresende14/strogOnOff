#include <stdio.h> 
#include <math.h>
#define número_máximo_leituras 20
#define min_sensor 0
#define max_sensor 1023
#define min_temperatura -10
#define max_temperatura 190
double calcular_temperatura(int a); 
double temperatura_valida(double a);
int validacao_sensor(int a);
double calcular_minimo(int b, double a[b]);
double calcular_maximo(int b, double a[b]);
double calcular_media(int b, double a[b]);
double calcular_desviopadrao(int b, double a[b], double c);
void apresentar_estatisticas(int a, int *b, double *c, double d, double e, double f, double g);

int main(void) {
      float sensor;
      double temperatura;
      int valores_lidos = 0;
      int sensores[número_máximo_leituras];
      double desvio_padrao;
      double minimo;
      double maximo;
      double media;
      double temperaturas[número_máximo_leituras];
 
      while(1){
            do {
                  printf("Escreva o valor que apareceu no sensor(-1 para sair): ");
                  if ((scanf("%f", &sensor) !=1) || validacao_sensor(sensor)) {
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


            temperatura = calcular_temperatura(sensor);
            sensores[valores_lidos] = sensor;
       
       if(temperatura_valida(temperatura)){
            printf("Temperatura: %.2f\n", temperatura);
            temperaturas[valores_lidos] = temperatura;
            valores_lidos++;
      }
 
      else{
            printf("Valor fora da gama\n");
      }
  }
     
      minimo = calcular_minimo(valores_lidos, temperaturas);
      maximo = calcular_maximo(valores_lidos, temperaturas);
      media = calcular_media(valores_lidos, temperaturas);
      desvio_padrao = calcular_desviopadrao(valores_lidos, temperaturas, media);
      apresentar_estatisticas(valores_lidos,sensores,temperaturas,minimo,maximo,media,desvio_padrao);

      return 0;
 }

double calcular_temperatura(int a)
{
 double res =(((260*a)/1023.0)-20);
 return res;
 }

 double temperatura_valida(double a)
 {
 return a >= min_temperatura && a <= max_temperatura;
 }
int validacao_sensor(int a){
      return (a != (int)a) || (a < min_sensor || a > max_sensor)  && (a != -1);
}
double calcular_minimo(int b, double a[b]){
       double minimo = a[0];
       for (int i = 0; i < b; i++) {
      
         if(a[i] < minimo) {
            minimo = a[i];
            return minimo;
         }
}
}
double calcular_maximo(int b, double a[b]){
       double maximo = a[0];
       for (int i = 0; i < b; i++) {
      
         if(a[i] > maximo) {
            maximo = a[i];
            return maximo;
         }
      }
}
double calcular_media(int b, double a[b]){
      double soma = 0;
       for (int i = 0; i < b; i++) {
         soma += a[i];
     }

return soma / b;
}
double calcular_desviopadrao(int b,double a[b],double c){
      double soma_quadrados = 0;
      for(int i=0; i < b; i++) {
         soma_quadrados += (a[i] - c) * (a[i] - c);
     }
     return sqrt(soma_quadrados / b);

}

void apresentar_estatisticas(int a, int *b, double *c, double d, double e, double f, double g){
      printf(" Valores lidos (sensor -> temperatura):\n");
      for(int i = 0; i < a; i++){
            printf("%d -> %.2f\n", b[i], c[i]);
      }
      printf("Número de valores lidos:%d\n", a);
      printf("Temperatura mínima: %.2f\n", d);
      printf("Temperatura máxima: %.2f\n", e);
      printf("Temperatura média: %.2f\n", f);
      printf("Desvio-padrão: %.2f\n", g);

}
