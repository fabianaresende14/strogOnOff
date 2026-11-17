#include <stdio.h>
#include <string.h>
#include <math.h>

#define numero_maximo_leituras 20
#define min_sensor 0
#define max_sensor 1023
#define min_temperatura -10
#define max_temperatura 190
#define n_sensores 3 //número de sensores existentes

// Estrutura para guardar a calibração dos sensores 
struct sensor_info {
    char nome[20];
    double ganho;
    double desvio;
};

// Estrutura para guardar todos os dados de cada leitura registada
struct leitura {
    char sensor[20];
    int instante;
    float valor_sensor;
    double temperatura;
};

// Protótipos das funções
int encontrar_sensor(char sensor_lido[], struct sensor_info sensores[], int nº_sensores);
double calcular_temperatura(float valor_sensor_lido, struct sensor_info sensores);
int temperatura_valida(double temperatura);
int validacao_sensor(float valor_sensor_lido);
double calcular_minimo(int contagem_por_sensor, double temp_sensor[contagem_por_sensor]);
double calcular_maximo(int contagem_por_sensor, double temp_sensor[contagem_por_sensor]);
double calcular_media(int contagem_por_sensor, double temp_sensor[contagem_por_sensor]);
double calcular_desviopadrao(int contagem_por_sensor, double temp_sensor[contagem_por_sensor], double media);
void apresentar_estatisticas(int valores_lidos, struct leitura leituras[], struct sensor_info sensores[], int nº_sensores);

int main(void) {
    //Calibração
    struct sensor_info sensores[n_sensores] = {
        {"TEMP1", 260.0, -20.0},
        {"TEMP2", 250.0, -15.0},
        {"TEMP3", 240.0, -10.0}
    };

    struct leitura leituras[numero_maximo_leituras];
    int valores_lidos = 0;
    char linha[100];

    while (valores_lidos < numero_maximo_leituras) {
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break;
        }

        // Condição de saída
        if (strcmp(linha, "FIM\n") == 0 || strcmp(linha, "FIM") == 0) {
            break;
        }

        char sensor_lido[20];
        int instante_lido;
        float valor_sensor_lido;
        char extra; // Para detetar caracteres inválidos após os números (ex: "TEMP2 2 10abc")

        // A função sscanf() vai devolver o nº de campos que leu corretamente
        int campos = sscanf(linha, "%19s %d %f %c", sensor_lido, &instante_lido, &valor_sensor_lido, &extra);

        if (campos < 1) {
            continue; // Ignora linhas em branco e volta ao início do ciclo
        }

        // 1. Verificar se o sensor existe
        int indice_sensor = encontrar_sensor(sensor_lido, sensores, n_sensores);
        if (indice_sensor == -1) {
            printf("Sensor desconhecido\n");
            continue;
        }

        // 2. Verificar se a linha tem 3 campos e valor do sensor entre 0 e 1023)
        if (campos != 3 || validacao_sensor(valor_sensor_lido)) {
            printf("Linha inválida\n");
            continue;
        }

        // 3. Calcular e validar a temperatura
        double temperatura = calcular_temperatura(valor_sensor_lido, sensores[indice_sensor]);

        if (temperatura_valida(temperatura)) {
            printf("%.2f\n", temperatura);

            // Guardar na struct de leituras
            strcpy(leituras[valores_lidos].sensor, sensor_lido);
            leituras[valores_lidos].instante = instante_lido;
            leituras[valores_lidos].valor_sensor = valor_sensor_lido;
            leituras[valores_lidos].temperatura = temperatura;
            valores_lidos++;
        } else {
            printf("Valor fora da gama\n");
        }
    }

    apresentar_estatisticas(valores_lidos, leituras, sensores, n_sensores);

    return 0;
}

// Procura o nome do sensor e devolve o índice (ou -1 se não existir)
int encontrar_sensor(char sensor_lido[], struct sensor_info sensores[], int nº_sensores) {
    for (int i = 0; i < nº_sensores; i++) {
        if (strcmp(sensor_lido, sensores[i].nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Calcula a temperatura usando o ganho e desvio específicos do sensor e devolve o valor da temperatura
double calcular_temperatura(float valor_sensor_lido, struct sensor_info sensores) {
    double res = ((sensores.ganho * valor_sensor_lido) / 1023.0) + sensores.desvio;
    return res;
}

// Condição para a temperatura estar dentro dos valores máximos e mínimos permitidos
int temperatura_valida(double temperatura) {
    return temperatura >= min_temperatura && temperatura <= max_temperatura;
}

// Condição para verificar se o valor do sensor é inválido 
int validacao_sensor(float valor_sensor_lido) {
    return ((valor_sensor_lido != (int)valor_sensor_lido) || (valor_sensor_lido< min_sensor || valor_sensor_lido > max_sensor));
}
// Cálcula o valor mínimo do array de temperaturas, retornando-o, assim como a sua ordem no array
double calcular_minimo(int contagem_por_sensor, double temp_sensor[contagem_por_sensor]) {
    double minimo = temp_sensor[0];
    for (int i = 0; i < contagem_por_sensor; i++) {
        if (temp_sensor[i] < minimo) {
            minimo = temp_sensor[i];
        }
    }
    return minimo;
}
// Cálcula o valor máximo do array de temperaturas, retornando-o, assim como a sua ordem no array
double calcular_maximo(int contagem_por_sensor, double temp_sensor[contagem_por_sensor]) {
    double maximo = temp_sensor[0];
    for (int i = 0; i < contagem_por_sensor; i++) {
        if (temp_sensor[i] > maximo) {
            maximo = temp_sensor[i];
        }
    }
    return maximo;
}
// Cálcula a média do array de temperaturas através da soma dos elementos e retorna-a
double calcular_media(int contagem_por_sensor, double temp_sensor[contagem_por_sensor]) {
    double soma = 0;
    for (int i = 0; i < contagem_por_sensor; i++) {
        soma += temp_sensor[i];
    }
    return soma / contagem_por_sensor;
}
// Cálcula o desvio padrão do array de temperaturas através da fórmula do desvio padrão e retorna-o
double calcular_desviopadrao(int contagem_por_sensor, double temp_sensor[contagem_por_sensor], double media) {
    double soma_quadrados = 0;
    for (int i = 0; i < contagem_por_sensor; i++) {
        soma_quadrados += (temp_sensor[i] - media) * (temp_sensor[i] - media);
    }
    return sqrt(soma_quadrados / contagem_por_sensor);
}


void apresentar_estatisticas(int valores_lidos, struct leitura leituras[], struct sensor_info sensores[], int nº_sensores) {
    printf("\nLeituras registadas (sensor instante: valor -> temperatura):\n");
    for (int i = 0; i < valores_lidos; i++) {
        printf("%s %d: %3.0f -> %6.2f\n",
               leituras[i].sensor, leituras[i].instante, leituras[i].valor_sensor, leituras[i].temperatura);
    }

    // Para cada sensor conhecido, agrupa as suas temperaturas e calcula as estatísticas
    for (int s = 0; s < nº_sensores; s++) {
        double temp_sensor[numero_maximo_leituras];
        int contagem_por_sensor = 0;

        for (int i = 0; i < valores_lidos; i++) {
            if (strcmp(leituras[i].sensor, sensores[s].nome) == 0) {
                temp_sensor[contagem_por_sensor] = leituras[i].temperatura;
                contagem_por_sensor++;
            }
        }

        // Só apresenta estatísticas se o sensor tiver pelo menos 1 leitura
        if (contagem_por_sensor > 0) {
            double minimo = calcular_minimo(contagem_por_sensor, temp_sensor);
            double maximo = calcular_maximo(contagem_por_sensor, temp_sensor);
            double media = calcular_media(contagem_por_sensor, temp_sensor);
            double desvio_padrao = calcular_desviopadrao(contagem_por_sensor, temp_sensor, media);

            printf("\nSensor %s\n", sensores[s].nome);
            printf("Número de valores lidos: %d\n", contagem_por_sensor);
            printf("Temperatura mínima:    %6.2f\n", minimo);
            printf("Temperatura máxima:    %6.2f\n", maximo);
            printf("Temperatura média:     %6.2f\n", media);
            printf("Desvio-padrão:         %6.2f\n", desvio_padrao);
        }
    }
}
