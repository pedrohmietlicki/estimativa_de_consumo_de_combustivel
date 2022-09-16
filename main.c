#include <stdio.h>
#include "lib.h"
#include <stdlib.h>
int main()
{

    int rpm, massa_do_carro;
    int tamanho = numeroDeLinhas();
    printf("%d\n",tamanho * sizeof(float));
    float **trajeto;
    trajeto = (float **)malloc(tamanho * sizeof(float *));
    for(int i = 0; i< tamanho; i++){
        trajeto[i] = (float *) malloc(4 * sizeof(float));
        trajeto[i][0] =2;
        trajeto[i][1] =0;
    }
    float torque;
    float *consumo;
    consumo =  malloc(tamanho *sizeof(float));
    lerArquivo(trajeto,tamanho);
    massa_do_carro = lerInt("Qual O peso do seu veiculo em quilos?");
    rpm = lerInt("Qual a rotacao de torque máximo do seu carro?");
    torque = lerFloat("Qual o torque ma-ximo do seu motor ?");
    pegaAceleracao(trajeto, tamanho);
    pegaForcaResultante(trajeto, consumo, massa_do_carro, rpm, torque, tamanho);
    float consumoMedio = mediaCombustivelGasto(consumo, tamanho);
    float distanciaPerco = distanciaPercorrida(trajeto, tamanho);
    float pontOrigem = distanciaPerco / consumoMedio;
    float vInicial = calculaMediaVelocidade(trajeto, tamanho);
    printf("Velocidade media antes do ajuste %.2f km/h\n", vInicial * 3.6);

    float novoConumo = calculaVelocidade(pontOrigem, trajeto, tamanho, consumo, massa_do_carro, rpm, torque, 0, 1, vInicial);

    printf("Velocidade media depois do ajuste %.2f km/h\n", calculaMediaVelocidade(trajeto, tamanho) * 3.6);
    printf("Consumo medio do seu veiculo e de %.2f km/l\n", consumoMedio);
    printf("Consumo medio apos ajuste e de %.2f km/l\n", novoConumo);

    return 0;
}