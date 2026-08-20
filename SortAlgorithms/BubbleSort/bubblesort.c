#include <stdio.h>

#define TAMANHO 10

void imprimir(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void bubbleSort(int vetor[], int tamanho){
    int trocou;

    do
    {
        trocou = 0;
        for(int i = 0; i < tamanho - 1; i++)
        {
            if(vetor[i] > vetor[i + 1])
            {
                int aux = vetor[i + 1];
                vetor[i + 1] = vetor[i];
                vetor[i] = aux;
                trocou = 1;
            }
        }
    } while (trocou != 0);
}

int main(){
    int vetor[TAMANHO] = {5, 2, 6, 3, 4, 2, 8, 9, 10, 1};

    imprimir(vetor, TAMANHO);
    bubbleSort(vetor, TAMANHO);
    imprimir(vetor, TAMANHO);

    return 0;
}
