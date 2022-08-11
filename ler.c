#include <stdio.h>
#include <stdlib.h>
int lerInt(char *mensagem)
{
    int valor = 0;

    printf("%s \n", mensagem);
    scanf("%d", &valor);

    return valor;
}
float lerFloat(char *mensagem)
{
    float valor = 0;

    printf("%s \n", mensagem);
    scanf("%f", &valor);

    return valor;
}

int lerArquivo(float *trajeto)
{
    FILE *arquivo;
    arquivo = fopen("us06col.txt", "r");
    char tempo[50], velocidade[50];
    int i = 0;
    int linha = 0;
    rewind(arquivo);
    while (fscanf(arquivo, "%s %s\n", &tempo, &velocidade) != EOF)
    {
        *(trajeto + linha + 0) = (float)atof(tempo);
        // Converte milhas por hora para m/s
        *(trajeto + linha + 1) = atof(velocidade) / 2.237;
        i++;
        linha = i * 3;
        fflush(stdin);
    }
    fclose(arquivo);
}

int numeroDeLinhas()
{
    FILE *arquivo;
    arquivo = fopen("us06col.txt", "r");
    int linhas = 0;
    char *linha[10];
    char chr = getc(arquivo);
    while (chr != EOF)
    {
        if (chr == '\n')
            linhas++;
        chr = getc(arquivo);
    }
    fclose(arquivo);
    return linhas;
}