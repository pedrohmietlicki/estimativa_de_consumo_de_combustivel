float pegaMaior(float *vetor[], int tamanho, int linha){
    float maior = 0;
    for(int i = 0; i< tamanho; i++){
        maior = vetor[i][linha] > maior ? vetor[i][linha] : maior;
    }
    printf("%f\n",maior);
}