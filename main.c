#include <stdio.h>
#include "lib.h"
int main()
{

    int rpm, massa_do_carro;

    int tamanho = numeroDeLinhas();

    float torque, trajeto[tamanho][3];
    float consumo[tamanho];
    lerArquivo(trajeto);
    massa_do_carro = lerInt("Qual O peso do seu veiculo em quilos?");
    rpm = lerInt("Qual a rotação de torque máximo do seu carro?");
    torque = lerFloat("Qual o torque máximo do seu motor ?");
    pegaAceleracao(trajeto, tamanho);
    pegaForcaResultante(trajeto,consumo,massa_do_carro,rpm, torque, tamanho);
    float consumoMedio =mediaCombustivelGasto(consumo, tamanho);
    printf("Consumo médio do seu veículo é de %.2f km/l", consumoMedio);
    

    float novoConumo = calculaVelocidade(pontOrigem, trajeto, tamanho, consumo, massa_do_carro, rpm, torque, 0, 1, vInicial);

    printf("Velocidade media depois do ajuste %.2f km/h\n", calculaMediaVelocidade(trajeto, tamanho) * 3.6);
    printf("Consumo medio do seu veiculo e de %.2f km/l\n", consumoMedio);
    printf("Consumo medio apos ajuste e de %.2f km/l\n", novoConumo);

    return 0;
}