#include <stdio.h>
#include <string.h>
#include <math.h>

#define MaxLeituras 20
#define MinSensor 0
#define MaxSensor 1023
#define MinTemperatura -10
#define MaxTemperatura 190
#define QuantSensores 3 //número de sensores existentes

// Estrutura para guardar a calibração dos sensores contndo o nome, ganho e desvio
struct InfoSensor {
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
int encontrar_sensor(char sensorLido[], struct InfoSensor sensores[], int SensorNo);
double calcular_temperatura(float SensorValue, struct InfoSensor sensores);
int temperatura_valida(double temperatura);
int validacao_sensor(float SensorValue);
double calcular_minimo(int SensorCount, double TempSensor[SensorCount]);
double calcular_maximo(int SensorCount, double TempSensor[SensorCount]);
double calcular_media(int SensorCount, double TempSensor[SensorCount]);
double calcular_desviopadrao(int SensorCount, double TempSensor[SensorCount], double media);
void apresentar_estatisticas(int valoresLidos, struct leitura leituras[], struct InfoSensor sensores[], int SensorNo);
int linha_duplicada(const char SensorLido[], int InstanteLido, const struct leitura leituras[], int valoresLidos);

int main(void) {


    //Dados de calibração dos sensores
    struct InfoSensor sensores[QuantSensores] = {
        {"TEMP1", 260.0, -20.0},
        {"TEMP2", 250.0, -15.0},
        {"TEMP3", 240.0, -10.0}
    };

    struct leitura leituras[MaxLeituras];
    int valoresLidos = 0;
    char linha[100];

    while (valoresLidos < MaxLeituras) { // Não ler mais do que o máximo permitido 
        if (fgets(linha, sizeof(linha), stdin) == NULL) { // a função fgets devolve NULL se der erro
            break;
        }

        // Condição de saída
        if (strcmp(linha, "FIM\n") == 0 || strcmp(linha, "FIM") == 0 || strcmp(linha, "FIM\t") == 0) {
            break;
        }

        char SensorLido[20];
        int InstanteLido;
        float SensorValue;
        char extra; // Para detetar caracteres inválidos após os números (ex: "TEMP2 2 10abc")

        // A função sscanf() vai devolver o nº de campos que leu corretamente e guardar na variável campos
        int campos = sscanf(linha, "%19s %d %f %c", SensorLido, &InstanteLido, &SensorValue, &extra);

        if (campos < 1) {
            continue; // Ignora linhas em branco e volta ao início do ciclo
        }

        // Verificar se o sensor existe
        int indice_sensor = encontrar_sensor(SensorLido, sensores, QuantSensores); // A função encontar_sensor devolve o indice no array sensores 
        if (indice_sensor == -1) {
            printf("Sensor desconhecido\n");
            continue;
        }

        // Verificar se o formato da linha é válido
        if (campos != 3 || validacao_sensor(SensorValue)) {
            printf("Linha inválida\n");
            continue;
        }

        if (linha_duplicada(SensorLido, InstanteLido, leituras, valoresLidos)) {
            printf("Linha duplicada\n");
            continue;
        }

        // Calcular e validar a temperatura
        double temperatura = calcular_temperatura(SensorValue, sensores[indice_sensor]);

        if (temperatura_valida(temperatura)) {
            printf("%.2f\n", temperatura);

            // Guardar na struct de leituras
            strcpy(leituras[valoresLidos].sensor, SensorLido); // Tem strcpy para copiar o nome do sensor para a struct pois trata-se de uma string
            leituras[valoresLidos].instante = InstanteLido;
            leituras[valoresLidos].valor_sensor = SensorValue;
            leituras[valoresLidos].temperatura = temperatura;
            valoresLidos++;
        } else {
            printf("Valor fora da gama\n");
        }
    }

    apresentar_estatisticas(valoresLidos, leituras, sensores, QuantSensores);

    return 0;
}

// Procura o nome do sensor na lista de configuraões e devolve o índice (ou -1 se não existir)
int encontrar_sensor(char SensorLido[], struct InfoSensor sensores[], int SensorNo) {
    for (int i = 0; i < SensorNo; i++) {
        if (strcmp(SensorLido, sensores[i].nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Calcula a temperatura usando o ganho e desvio específicos do sensor e devolve o valor da temperatura
double calcular_temperatura(float SensorValue, struct InfoSensor sensores) {
    double res = ((sensores.ganho * (double)SensorValue) / (double)MaxSensor) + sensores.desvio;
    return res;
}

// Condição para a temperatura estar dentro dos valores máximos e mínimos permitidos
int temperatura_valida(double temperatura) {
    return temperatura >= MinTemperatura && temperatura <= MaxTemperatura;
}

// Condição para verificar se o valor do sensor é inválido 
int validacao_sensor(float SensorValue) {
    return ((SensorValue != (int)SensorValue) || (SensorValue< MinSensor || SensorValue > MaxSensor));
}

// Cálcula o valor mínimo do array de temperaturas, retornando-o, assim como a sua ordem no array
double calcular_minimo(int SensorCount, double TempSensor[SensorCount]) {
    double minimo = TempSensor[0];
    for (int i = 0; i < SensorCount; i++) {
        if (TempSensor[i] < minimo) {
            minimo = TempSensor[i];
        }
    }
    return minimo;
}
// Cálcula o valor máximo do array de temperaturas, retornando-o, assim como a sua ordem no array
double calcular_maximo(int SensorCount, double TempSensor[SensorCount]) {
    double maximo = TempSensor[0];
    for (int i = 0; i < SensorCount; i++) {
        if (TempSensor[i] > maximo) {
            maximo = TempSensor[i];
        }
    }
    return maximo;
}
// Cálcula a média do array de temperaturas através da soma dos elementos e retorna-a
double calcular_media(int SensorCount, double TempSensor[SensorCount]) {
    double soma = 0;
    for (int i = 0; i < SensorCount; i++) {
        soma += TempSensor[i];
    }
    return soma / SensorCount;
}
// Cálcula o desvio padrão do array de temperaturas através da fórmula do desvio padrão e retorna-o
double calcular_desviopadrao(int SensorCount, double TempSensor[SensorCount], double media) {
    double soma_quadrados = 0;
    for (int i = 0; i < SensorCount; i++) {
        soma_quadrados += (TempSensor[i] - media) * (TempSensor[i] - media);
    }
    return sqrt(soma_quadrados / SensorCount);
}


void apresentar_estatisticas(int valoresLidos, struct leitura leituras[], struct InfoSensor sensores[], int SensorNo) {
    printf("\nLeituras registadas (sensor instante: valor -> temperatura):\n");
    for (int i = 0; i < valoresLidos; i++) {
        printf("%s %d: %3.0f -> %6.2f\n",
               leituras[i].sensor, leituras[i].instante, leituras[i].valor_sensor, leituras[i].temperatura);
    }

    // Para cada sensor conhecido, agrupa as suas temperaturas e calcula as estatísticas
    for (int s = 0; s < SensorNo; s++) {
        double TempSensor[MaxLeituras];
        int SensorCount = 0;

        for (int i = 0; i < valoresLidos; i++) {
            if (strcmp(leituras[i].sensor, sensores[s].nome) == 0) {
                TempSensor[SensorCount] = leituras[i].temperatura;
                SensorCount++;
            }
        }

        // Só apresenta estatísticas se o sensor tiver pelo menos 1 leitura
        if (SensorCount > 0) {
            double minimo = calcular_minimo(SensorCount, TempSensor);
            double maximo = calcular_maximo(SensorCount, TempSensor);
            double media = calcular_media(SensorCount, TempSensor);
            double desvio_padrao = calcular_desviopadrao(SensorCount, TempSensor, media);

            printf("\nSensor %s\n", sensores[s].nome);
            printf("Número de valores lidos: %d\n", SensorCount);
            printf("Temperatura mínima:    %6.2f\n", minimo);
            printf("Temperatura máxima:    %6.2f\n", maximo);
            printf("Temperatura média:     %6.2f\n", media);
            printf("Desvio-padrão:         %6.2f\n", desvio_padrao);
        }
    }
}

int linha_duplicada(const char SensorLido[], int InstanteLido, const struct leitura leituras[], int valoresLidos) {
    for (int i = 0; i < valoresLidos; i++) {
        if (strcmp(leituras[i].sensor, SensorLido) == 0 && leituras[i].instante == InstanteLido) {
            return 1;
        }
    }
    return 0;
}
