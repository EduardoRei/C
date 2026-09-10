#include <stdio.h>

#define tamanhoV 8

void trocar(int *pa, int *pb)
{
    int aux = *pa;
    *pa = *pb;
    *pb = aux;
}

int particionar(int v[], int inicio, int fim)
{
    int pivo = v[fim];
    int i = inicio;

    for(int j = inicio; j < fim; j++) 
    {
        if (v[j] <= pivo)
        {
            trocar(&v[i], &v[j]);
            i++;
        }
    }

    trocar(&v[i], &v[fim]);
    return i;
}

void quickSort(int v[], int inicio, int fim)
{
    if(inicio < fim)
    {
        int meio = particionar(v, inicio, fim);
        quickSort(v, inicio, meio - 1);
        quickSort(v, meio + 1, fim);
    }
}

void imprimirVetor(int v[], int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int v[tamanhoV] = {6, 2, 4, 6, 7, 1, 3, 5};

    imprimirVetor(v, tamanhoV);
    quickSort(v, 0, tamanhoV - 1);
    imprimirVetor(v, tamanhoV);

    return 0;
}