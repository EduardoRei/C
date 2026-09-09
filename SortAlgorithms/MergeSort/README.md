# Merge Sort

Ordenação por intercalação: divide o vetor ao meio recursivamente até sobrarem pedaços de
um único elemento (que já estão ordenados por definição) e depois intercala esses pedaços
dois a dois, sempre pegando o menor entre as frentes das duas metades. É o exemplo clássico
de *dividir para conquistar*.

## Como funciona

1. `mergeSort` recebe `inicio` e `fim`. Se `inicio >= fim`, o trecho tem 0 ou 1 elemento e já está ordenado.
2. Calcula `meio = (inicio + fim) / 2` e chama a si mesmo para `[inicio, meio]` e `[meio + 1, fim]`.
3. Com as duas metades já ordenadas, `merge` copia cada uma para os vetores auxiliares `esquerda` e `direita`.
4. Percorre os dois auxiliares em paralelo e devolve para `v[k++]` sempre o menor entre `esquerda[i]` e `direita[j]`.
5. Quando um dos lados acaba, os `while` finais despejam o resto do outro lado (que já está ordenado).
6. Ao terminar a intercalação da chamada mais externa, o vetor inteiro está ordenado.

A comparação usa `<=`: em caso de empate o elemento da esquerda entra primeiro, e é isso
que garante a estabilidade do algoritmo.

### Exemplo

```
Entrada: 5 2 4 7 1 3 2 6

Divisão:   [5 2 4 7] [1 3 2 6]
           [5 2] [4 7]   [1 3] [2 6]
           [5][2] [4][7] [1][3] [2][6]

Intercala: [2 5] [4 7]   [1 3] [2 6]
           [2 4 5 7]     [1 2 3 6]
Saída:     1 2 2 3 4 5 6 7
```

## Complexidade

| Caso | Comparações | Tempo |
|------|-------------|-------|
| Melhor | ~`n·log n / 2` | **O(n log n)** |
| Médio | ~`n·log n` | **O(n log n)** |
| Pior | ~`n·log n` | **O(n log n)** |

- **Espaço:** `O(n)` — não é *in-place*: cada `merge` aloca os vetores `esquerda` e `direita`, e a recursão ainda usa `O(log n)` de pilha.
- **Estável:** sim — o `<=` na intercalação preserva a ordem relativa dos elementos iguais.
- **Divisões:** a árvore de recursão tem `log n` níveis e cada nível intercala `n` elementos, daí o `n log n`.

Diferente do bubble e do insertion sort, não existe melhor caso especial: mesmo com o vetor
já ordenado a recursão desce até os elementos isolados e intercala tudo de volta.

## Quando usar

Boa escolha quando o pior caso importa (`O(n log n)` garantido, ao contrário do quicksort) e
quando a estabilidade é necessária — por exemplo, ao ordenar registros por uma segunda chave
sem perder a ordem da primeira. Também é a base da ordenação externa, quando os dados não
cabem na memória. O custo é o espaço extra `O(n)`.

## Compilar e executar

```bash
gcc -Wall -g mergesort.c -o mergesort.out
./mergesort.out
```
