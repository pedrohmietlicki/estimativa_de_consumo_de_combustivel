#ifndef MOTOR_H_INCLUDED
int velocidade();
void pegaAceleracao(float *trajeto, int tamanho);
void pegaForcaResultante(float *trajeto, float *consumo,int massa, int rpm, float torque, int tamanho);
void getFuelConsuptionIddle(float cc);
float mediaCombustivelGasto(float *consumo, int tamanho);
float pegaVelocidadeMedia(float *trajeto, float tamanho);
void calculaDados(float *trajeto, int tamanho, float torque, float *consumo, int rpm, int massa_do_carro);
#endif