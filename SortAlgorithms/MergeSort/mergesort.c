#include <stdio.h>
#include <stdlib.h>

#define tamanho 8

void merge(int v[], int inicio, int meio, int fim)
{
    int i, j, k, n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *esquerda = malloc(n1 * sizeof(int));
    int *direita = malloc(n2 * sizeof(int));

    for(i = 0; i < n1; i++)
    {
        esquerda[i] = v[inicio + i];
    }
    for(j = 0; j < n2; j++)
    {
        direita[j] = v[meio + 1 + j];
    }

    i = 0, j = 0, k = inicio; // intercalação

    while(i < n1 && j < n2)
    {
        if(esquerda[i] <= direita[j])
        {
            v[k++] = esquerda[i++];
        }
        else
        {
            v[k++] = direita[j++];
        }
    }

    while (i < n1)
    {
        v[k++] = esquerda[i++];
    }

    while (j < n2)
    {
        v[k++] = direita[j++];
    }
    
    free(esquerda);
    free(direita);    
}

void mergeSort(int v[], int inicio, int fim)
{
    int meio;
    if(inicio < fim) 
    {
        meio = inicio + (fim - inicio) / 2;
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

void imprimirVetor(int vetor[], int t){
    for(int i = 0; i < t; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}


int main()
{
    int v[tamanho] = {5,2,4,7,1,3,2,6};

    imprimirVetor(v,tamanho);
    mergeSort(v, 0, tamanho - 1);
    imprimirVetor(v, tamanho);

    return 0;
} 