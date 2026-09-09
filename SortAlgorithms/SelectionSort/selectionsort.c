#include <stdio.h>

#define tamanhoV 8

void selectionSort(int v[], int tamanho)
{ 
    int i, j, copia, menorIndicie;

    for(i = 0; i < tamanho - 1; i++)
    {
        menorIndicie = i;

        for(j = i + 1; j < tamanho; j++)
        {
            if(v[j] < v[menorIndicie])
            {
                menorIndicie = j;
            }
        }

        if(v[menorIndicie] != v[i])
        {
            copia = v[menorIndicie];
            v[menorIndicie] = v[i];
            v[i] = copia;
        }
    }
}

void imprimirVetor(int v[], int tamanho)
{
    for(int i =0; i < tamanho; i++)
    {
        printf("%d ", v[i]);
    }

    printf("\n");
}

int main()
{
    int v[tamanhoV] = {5, 3, 1, 2, 4, 7, 2, 6};

    imprimirVetor(v, tamanhoV);
    selectionSort(v, tamanhoV);
    imprimirVetor(v, tamanhoV);

    return 0;
}