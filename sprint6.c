#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUMERO_MAXIMO_LEITURAS 20
#define MIN_SENSOR 0
#define MAX_SENSOR 1023
#define MIN_TEMPERATURA -10
#define MAX_TEMPERATURA 190
#define NUM_SENSORES 3

// Estrutura para centralizar a calibração dos sensores num único ponto
struct sensor_info {
    char nome[20];
    double ganho;
    double desvio;
};

// Estrutura para guardar todos os dados de cada leitura registada
struct leitura {
    char sensor[20];
    int instante;
    int valor;
    double temperatura;
};

// Protótipos das funções (mantendo as vossas funções originais adaptadas)
int encontrar_sensor(char *nome, struct sensor_info lista[], int total);
double calcular_temperatura(int a, struct sensor_info s);
int temperatura_valida(double a);
int validacao_sensor(int a);
double calcular_minimo(int b, double a[b]);
double calcular_maximo(int b, double a[b]);
double calcular_media(int b, double a[b]);
double calcular_desviopadrao(int b, double a[b], double c);
void apresentar_estatisticas(int total_leituras, struct leitura leituras[], struct sensor_info lista_sensores[], int total_sensores);

int main(void) {
    // Único ponto do código onde os dados de calibração estão definidos
    struct sensor_info lista_sensores[NUM_SENSORES] = {
        {"TEMP1", 260.0, -20.0},
        {"TEMP2", 250.0, -15.0},
        {"TEMP3", 240.0, -10.0}
    };

    struct leitura leituras[NUMERO_MAXIMO_LEITURAS];
    int valores_lidos = 0;
    char linha[100];

    while (valores_lidos < NUMERO_MAXIMO_LEITURAS) {
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break;
        }

        // Remove o '\n' do final da linha
        linha[strcspn(linha, "\r\n")] = '\0';

        // Condição de saída
        if (strcmp(linha, "FIM") == 0) {
            break;
        }

        char nome_lido[20];
        int instante_lido, valor_lido;
        char extra; // Para detetar caracteres inválidos após os números (ex: "TEMP2 2 10abc")

        // Tenta ler os 3 campos separados por espaços
        int campos = sscanf(linha, "%19s %d %d %c", nome_lido, &instante_lido, &valor_lido, &extra);

        if (campos < 1) {
            continue; // Ignora linhas em branco
        }

        // 1. Verificar se o sensor existe
        int idx_sensor = encontrar_sensor(nome_lido, lista_sensores, NUM_SENSORES);
        if (idx_sensor == -1) {
            printf("Sensor desconhecido\n");
            continue;
        }

        // 2. Verificar se o formato da linha é válido (3 campos exatos e valor do sensor entre 0 e 1023)
        if (campos != 3 || !validacao_sensor(valor_lido)) {
            printf("Linha inválida\n");
            continue;
        }

        // 3. Calcular e validar a temperatura
        double temperatura = calcular_temperatura(valor_lido, lista_sensores[idx_sensor]);

        if (temperatura_valida(temperatura)) {
            printf("%.2f\n", temperatura);

            // Guardar na struct de leituras
            strcpy(leituras[valores_lidos].sensor, nome_lido);
            leituras[valores_lidos].instante = instante_lido;
            leituras[valores_lidos].valor = valor_lido;
            leituras[valores_lidos].temperatura = temperatura;
            valores_lidos++;
        } else {
            printf("Valor fora da gama\n");
        }
    }

    apresentar_estatisticas(valores_lidos, leituras, lista_sensores, NUM_SENSORES);

    return 0;
}

// Procura o nome do sensor na lista de configuração e devolve o índice (ou -1 se não existir)
int encontrar_sensor(char *nome, struct sensor_info lista[], int total) {
    for (int i = 0; i < total; i++) {
        if (strcmp(nome, lista[i].nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Calcula a temperatura usando o ganho e desvio específicos do sensor
double calcular_temperatura(int a, struct sensor_info s) {
    double res = ((s.ganho * a) / 1023.0) + s.desvio;
    return res;
}

// Condição para a temperatura estar dentro dos valores máximos e mínimos permitidos
int temperatura_valida(double a) {
    return a >= MIN_TEMPERATURA && a <= MAX_TEMPERATURA;
}

// Condição para o valor lido do sensor ser válido (entre 0 e 1023)
int validacao_sensor(int a) {
    return (a >= MIN_SENSOR && a <= MAX_SENSOR);
}

// As vossas 4 funções matemáticas mantidas intactas:
double calcular_minimo(int b, double a[b]) {
    double minimo = a[0];
    for (int i = 0; i < b; i++) {
        if (a[i] < minimo) {
            minimo = a[i];
        }
    }
    return minimo;
}

double calcular_maximo(int b, double a[b]) {
    double maximo = a[0];
    for (int i = 0; i < b; i++) {
        if (a[i] > maximo) {
            maximo = a[i];
        }
    }
    return maximo;
}

double calcular_media(int b, double a[b]) {
    double soma = 0;
    for (int i = 0; i < b; i++) {
        soma += a[i];
    }
    return soma / b;
}

double calcular_desviopadrao(int b, double a[b], double c) {
    double soma_quadrados = 0;
    for (int i = 0; i < b; i++) {
        soma_quadrados += (a[i] - c) * (a[i] - c);
    }
    return sqrt(soma_quadrados / b);
}

// Apresenta a lista geral e chama as vossas funções estatísticas para cada sensor
void apresentar_estatisticas(int total_leituras, struct leitura leituras[], struct sensor_info lista_sensores[], int total_sensores) {
    printf("\nLeituras registadas (sensor instante: valor -> temperatura):\n");
    for (int i = 0; i < total_leituras; i++) {
        printf("%s %d: %3d -> %6.2f\n",
               leituras[i].sensor, leituras[i].instante, leituras[i].valor, leituras[i].temperatura);
    }

    // Para cada sensor conhecido, agrupa as suas temperaturas e calcula as estatísticas
    for (int s = 0; s < total_sensores; s++) {
        double temp_sensor[NUMERO_MAXIMO_LEITURAS];
        int count = 0;

        for (int i = 0; i < total_leituras; i++) {
            if (strcmp(leituras[i].sensor, lista_sensores[s].nome) == 0) {
                temp_sensor[count] = leituras[i].temperatura;
                count++;
            }
        }

        // Só apresenta estatísticas se o sensor tiver pelo menos 1 leitura
        if (count > 0) {
            double minimo = calcular_minimo(count, temp_sensor);
            double maximo = calcular_maximo(count, temp_sensor);
            double media = calcular_media(count, temp_sensor);
            double desvio_padrao = calcular_desviopadrao(count, temp_sensor, media);

            printf("\nSensor %s\n", lista_sensores[s].nome);
            printf("Número de valores lidos: %d\n", count);
            printf("Temperatura mínima:    %6.2f\n", minimo);
            printf("Temperatura máxima:    %6.2f\n", maximo);
            printf("Temperatura média:     %6.2f\n", media);
            printf("Desvio-padrão:         %6.2f\n", desvio_padrao);
        }
    }
}
