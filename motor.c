#include <math.h>
#include <stdio.h>
#define AreaFrontal 2.16
#define CoeficienteDeArrasto 0.38
#define RendimentoTransmissao 0.94
#define GravidadeTerrestre 9.81

/*
   0 = Tempo
   1 = Velocidade
   2 = Aceleração
   3 = Força resultante
   4 = Força de arrasto

*/

/**
 * @brief Retorna a aceleração para cada ponto do percurso.
 *
 * @param trajeto
 * @param Tamanho
 */
void pegaAceleracao(float **trajeto, int tamanho)
{

    int linha;
    float velocidade, vAnterior = 0, aceleracao;
    for (int i = 0; i < tamanho; i++)
    {
       
        velocidade = trajeto[i][1];
        aceleracao = velocidade - vAnterior;
        vAnterior = velocidade;
        trajeto[i][2] = aceleracao;
        
        
    }
}

void pegaForcaResultante(float **trajeto, float *consumo, int massa, int rpm, float torque, int tamanho)
{
    int linha;
    float aceleracao, velocidade, forcaArrasto, forcaResultante, PotenciaInstantanea;
    float MelhorPotencia = (torque * (double)rpm * GravidadeTerrestre * 3.14) / 60;
    float ConsumoMelhorPotencia = MelhorPotencia / (0.33 * 29500);
    float forcaAtrito = 0.01 * (float)massa * GravidadeTerrestre;
    for (int i = 0; i < tamanho; i++)
    {
        velocidade = trajeto[i][1];
        forcaArrasto = 0.5 * 1.20 * CoeficienteDeArrasto * AreaFrontal * pow(velocidade, 2);
        aceleracao = trajeto[i][2];

        forcaResultante = (massa * aceleracao) > 0.2 ? (massa * aceleracao) + forcaAtrito + forcaArrasto : forcaAtrito + forcaArrasto;
        trajeto[i][3] = forcaResultante;
        PotenciaInstantanea = forcaResultante * velocidade;
        float consumoLPorHora = ConsumoMelhorPotencia * (0.15 + (1 - 0.15) * PotenciaInstantanea / MelhorPotencia);
        *(consumo + i) = (velocidade * 3.6) / consumoLPorHora;
    }
}
float mediaCombustivelGasto(float *consumo, int tamanho)
{
    float soma = 0;
    for (int i = 0; i < tamanho; i++)
    {
        soma += consumo[i];
    }
    return soma / tamanho;
}
float distanciaPercorrida(float **trajeto, int tamanho)
{
    float percorrida = 0;
    int linha;
    for (int i = 0; i < tamanho; i++)
    {
        
        percorrida += trajeto[i][1];
    }
    return percorrida;
}

void aumentaMedia(float **trajeto, int tamanho)
{
    
    float maior = 0;
    for (int i = 0; i < tamanho; i++)
    {
        
        maior = trajeto[i][1] > maior ? trajeto[i][1] : maior;
    }

    float menor = maior;

    for (int i = 0; i < tamanho; i++)
    {
        
        menor = (trajeto[i][1] < menor) && trajeto[i][1] != 0 ? trajeto[i][1] : menor;
    }

    for (int i = 0; i < tamanho; i++)
    {
        
        if (trajeto[i][1] == menor)
        {
           trajeto[i][1] += 1;
        }
    }
}
void diminuiMedia(float **trajeto, int tamanho)
{

    float maior = 0;
    
    for (int i = 0; i < tamanho; i++)
    {
         maior = trajeto[i][1] > maior ? trajeto[i][1] : maior;
        
    }
    for (int i = 0; i < tamanho; i++)
    {
       if (trajeto[i][1] == maior) {
                trajeto[i][1] -= 1;
        }
        
        
       
    }

}
float calculaMediaVelocidade(float **trajeto, int tamanho) {
    float acumulador = 0;
    for (int i = 0; i < tamanho; i++)
    {
        acumulador += trajeto[i][1];
    }
    return acumulador / (float)tamanho;
}
float calculaVelocidade(float pontuacao, float **trajeto, int tamanho, float *consumo, int massa_do_carro, int rpm, float torque, float novaPontuacao, int sinal, float vInicial)
{

    sinal > 0 ? aumentaMedia(trajeto, tamanho) : diminuiMedia(trajeto, tamanho);
    pegaAceleracao(trajeto, tamanho);
    pegaForcaResultante(trajeto, consumo, massa_do_carro, rpm, torque, tamanho);
    float novoConsumo = mediaCombustivelGasto(consumo, tamanho);
    float novaDistancia = distanciaPercorrida(trajeto, tamanho);
    novaPontuacao = novaDistancia / novoConsumo;
    novaPontuacao = sinal > 0 ? novaPontuacao * 0.9 : novaPontuacao * 1.1;
    if ((novaPontuacao <= pontuacao) && (calculaMediaVelocidade(trajeto, tamanho) > (vInicial - 2)))
    {

        calculaVelocidade(novaPontuacao, trajeto, tamanho, consumo, massa_do_carro, rpm, torque, novaPontuacao, sinal, vInicial);
    }
    else if (sinal > 0)
        calculaVelocidade(novaPontuacao, trajeto, tamanho, consumo, massa_do_carro, rpm, torque, novaPontuacao, -1, vInicial);
    return novoConsumo;
}