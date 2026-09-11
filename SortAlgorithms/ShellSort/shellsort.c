#include <stdio.h>

#define tamanhoV 8

void shellSort(int v[], int tam)
{
    int gap, i, j, copia;

    for(gap = tam / 2; gap > 0; gap /= 2)
    {
        for(i = gap; i < tam; i++)
        {
            copia= v[i];
            for(j = i; j >= gap && v[j - gap] > copia; j -= gap)
            {
                v[j] = v[j - gap];
            }
            v[j] = copia;
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
    shellSort(v, tamanhoV);
    imprimirVetor(v, tamanhoV);

    return 0;
}