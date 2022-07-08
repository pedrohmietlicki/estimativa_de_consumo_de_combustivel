#include <stdio.h>
#include "lib.h"
int main (){
    FILE *arquivo;
    int rpm, massa_do_carro;

    arquivo = fopen("hwycol.txt", "r");
    int tamanho = numeroDeLinhas(arquivo);
    fclose(arquivo);
    
    float torque, trajeto[tamanho][3];
    float consumo[tamanho];
    
    lerArquivo(trajeto);
    massa_do_carro = lerInt("Qual O peso do seu veículo em quilos?");
    rpm = lerInt("Qual a rotação de torque máximo do seu carro?");
    torque = lerFloat("Qual o torque máximo do seu motor ?");
    pegaAceleracao(trajeto, tamanho);
    pegaForcaResultante(trajeto,consumo,massa_do_carro,rpm, torque, tamanho);
    float consumoMedio =mediaCombustivelGasto(consumo, tamanho);
    printf("Consumo médio do seu veículo é de %.2f km/l", consumoMedio);
    



    return 0;
}