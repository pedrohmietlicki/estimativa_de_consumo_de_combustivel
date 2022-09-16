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


int lerArquivo(float **trajeto, int tamanho)
{
    FILE *arquivo =fopen("us06col.txt", "r");
    float tempo, velocidade;
    int i = 0, acum = 0;
    int linha = 0;

    while (fscanf(arquivo, "%f %f\n", &tempo, &velocidade) != EOF)
    {
         trajeto[i][0] = tempo;
        // // Converte milhas por hora para m/s
        trajeto[i][1] = (float)(velocidade / 2.237);
        i++;

        // fflush(stdin);
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