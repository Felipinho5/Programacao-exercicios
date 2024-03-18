#include <stdio.h>
#include <stdlib.h>

// Nome: Felipe de Carvalho Santos (fiz sozinho)
// RA: 2760482311028
/* Este programa tem o objetivo de exibir para o usu�rio a cadeia hier�rquica relativa a
um funcion�rio de uma empresa com base em uma matriz que representa a empresa. Em outras
palavras, mostra quais funcion�rios s�o subordinados �quele inserido como entrada. */

void busca(int ordem, int funcionario, int *subordinados, int *cadeia, FILE *arq);
void bubbleSort(int v[], int n);
void troca(int *a, int *b);

int main(int argc, char *argv[])
{
    // Se os par�metros foram inseridos incorretamente, encerrar execu��o
    if(argc != 2)
    {
        fprintf(stderr, "Argumentos incorretos.");
        return 1;
    }

    // Declara��o de vari�veis e abertura do arquivo
    FILE *arq = fopen(argv[1], "r");
    int ordem, funcionario, subordinados = 0, i;

    fscanf(arq, "%d", &ordem);
    fscanf(arq, "%d", &funcionario);

    // Se o n�mero de funcion�rios for menor ou maior do que o permitido, encerrar execu��o
    if(ordem < 3 || ordem > 30)
    {
        fprintf(stderr, "A ordem da matriz deve ser maior do que 3 e menor do que 30.");
        fclose(arq);
        return 1;
    }

    // Aloca��o do vetor que cont�m a cadeia hier�rquica
    int *cadeia = (int*) malloc (ordem * sizeof(int));
    cadeia[0] = funcionario;

    // Chamada da fun��o para buscar funcion�rio e seus subordinados
    busca(ordem, funcionario, &subordinados, cadeia, arq);

    // Ordena��o da cadeia partindo do �ndice 1 (o 0 permanece)
    // para imprimi-la na ordem que pede o enunciado
    bubbleSort(cadeia, subordinados + 1);

    // Impress�o da cadeia hier�rquica
    for(i = 0; i < subordinados + 1; i++)
        printf("%d ", cadeia[i]);

    // Libera��o da mem�ria alocada
    free(cadeia);

    // Fechamento do arquivo de entrada
    fclose(arq);

    return 0;
}

void busca(int ordem, int funcionario, int *subordinados, int *cadeia, FILE *arq)
{
    // Declara��o de vari�veis
    int aux, i;
    int subordinadosAnterior = *subordinados;

    // Posicionamento do cursor na linha do funcion�rio especificado
    fseek(arq, 0, SEEK_SET);

    for(i = 0; i < ordem * funcionario + 2; i++)
        fscanf(arq, "%d", &aux);

    // Busca por subordinados na linha espec�fica do funcion�rio
    for(i = 0; i < ordem; i++)
    {
        fscanf(arq, "%d", &aux);

        if(aux == 1)
        {
            (*subordinados)++;
            cadeia[*subordinados] = i;
        }
    }

    // Se "subordinadosAnterior" for menor que "subordinados", houve subordinados
    // diretos na linha e, portanto, a fun��o deve ser chamada mais vezes
    aux = *subordinados;

    for(i = subordinadosAnterior; i < aux; i++)
    {
        funcionario = cadeia[i + 1];
        busca(ordem, funcionario, subordinados, cadeia, arq);
    }
}

void bubbleSort(int v[], int n)
{
    // Este bubbleSort ignora o �ndice zero
    for (int i = 0; i < n-1; i++)
        for (int j = 1; j < n-i-1; j++)
            if (v[j] > v[j+1])
                troca(&v[j], &v[j+1]);
}

void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
