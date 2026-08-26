#include <stdio.h>

#define TAMANHO_VETOR 10

void InsertionSort(int *vetor, int tamanho)
{
    int chave, i, j;
    for(j = 1; j < tamanho; j++)
    {
        chave = vetor[j];
        i = j - 1;
        while (i >= 0 && vetor[i] > chave)
        {
            vetor[i + 1] = vetor[i];
            i = i - 1;
        }
        vetor[i + 1] = chave;
    }
}

void imprimir(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main(){
    
    int vetor[TAMANHO_VETOR] = {6, 4, 7, 0, 2, 3, 1, 8, 9, 5};

    imprimir(vetor, TAMANHO_VETOR);

    InsertionSort(vetor, TAMANHO_VETOR);

    imprimir(vetor, TAMANHO_VETOR);

    return 0;
}