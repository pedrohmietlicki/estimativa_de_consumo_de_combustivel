#ifndef MOTOR_H_INCLUDED
int velocidade();
void pegaAceleracao(float **trajeto, int tamanho);
void pegaForcaResultante(float **trajeto, float *consumo,int massa, int rpm, float torque,int tamanho);
void getFuelConsuptionIddle(float cc);
float mediaCombustivelGasto(float *consumo, int tamanho);
float distanciaPercorrida(float **trajeto, int tamanho);
void aumentaMedia(float **trajeto, int tamanho, int aux);
void diminuiMedia(float **trajeto, int tamanho, int aux);
float calculaVelocidade(float pontuacao, float **trajeto, int tamanho ,float *consumo, int massa_do_carro, int rpm, float torque, float novaPontuacao , int sinal, float vIncial);
float calculaMediaVelocidade(float **trajeto, int tamanho);
     

#endif