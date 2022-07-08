#include <math.h>
#include <stdio.h>
#define AreaFrontal 2.14
#define CoeficienteDeArrasto 0.35
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
void pegaAceleracao(float *trajeto, int tamanho){
    
    
    int linha;
    float velocidade, vAnterior = 0, aceleracao;
    for (int i = 0; i < tamanho; i++){
        linha = i * 3;
         velocidade = (*trajeto + linha + 1);
        aceleracao = velocidade - vAnterior;
        vAnterior = velocidade;
        *(trajeto + linha +2) = aceleracao;
    }
}

void pegaForcaResultante(float *trajeto,float *consumo, int massa, int rpm, float torque, int tamanho){
    int linha;
    float aceleracao , velocidade , forcaArrasto, forcaResultante, PotenciaInstantanea;
    float MelhorPotencia = (torque * (double) rpm * GravidadeTerrestre * 3.14) /60;
    float ConsumoMelhorPotencia = MelhorPotencia / (0.33 * 29500);
    float forcaAtrito = 0.01 * (float) massa * GravidadeTerrestre;
    for(int i = 0; i < tamanho; i++){
        linha = i * 3;
        velocidade = *(trajeto + linha +1);
        forcaArrasto = 0.5 * 1.20 * CoeficienteDeArrasto * AreaFrontal * pow(velocidade,2);
        aceleracao =  *(trajeto + linha + 2);

        forcaResultante = (massa * aceleracao) > 0.2 ? (massa * aceleracao) + forcaAtrito + forcaArrasto : forcaAtrito + forcaArrasto;
        *(trajeto + linha + 3 ) = forcaResultante;
        PotenciaInstantanea =  forcaResultante * velocidade;
        float consumoLPorHora = ConsumoMelhorPotencia * (0.15+ (1- 0.15) * PotenciaInstantanea / MelhorPotencia);
        *(consumo + i) = (velocidade * 3.6) / consumoLPorHora;
    }
}
float mediaCombustivelGasto(float *consumo, int tamanho){
    float soma = 0;
    for(int i = 0; i < tamanho; i++ ){
        soma += *(consumo + i);
    }
    return soma / tamanho;
}

int velocidade(){
    return 0;
}