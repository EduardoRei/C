# Insertion Sort

Ordenação por inserção: percorre o vetor comparando uma chave referente à posição atual no vetor com os valores anteriores já ordenados; se forem maiores, desloca eles uma casa pra frente e vai comparando até achar onde a chave deveria estar.

## Como funciona
1. Inicia na posição 1, pois todo vetor com uma casa já está ordenado, e percorre até o tamanho - 1.
2. Se `chave < vetor[i]`, desloca uma casa para a direita `vetor[i + 1] = vetor[i]`
3. Repete a comparação até encontrar onde a chave deve se manter naquele momento.
4. Caso `chave >= vetor[i]` a chave se mantém na mesma posição e passa pra próxima repetição.
5. Quando a passagem chegar na última posição, o vetor está ordenado.

### Exemplo

```
Entrada: 5 2 6 3 4 2 8 9 10 1

Passagem 1: 2 5 6 3 4 2 8 9 10 1 <- chave 2: o 5 desloca uma casa e o 2 entra antes dele.
Passagem 2: 2 5 6 3 4 2 8 9 10 1 <- chave 6: é maior que o 5 e se mantém na mesma posição.
Passagem 3: 2 3 5 6 4 2 8 9 10 1 <- chave 3: o 6 e o 5 deslocam e o 3 entra depois do 2.
Passagem 4: 2 3 4 5 6 2 8 9 10 1 <- chave 4: o 6 e o 5 deslocam e o 4 entra depois do 3.
...
Saída:   1 2 2 3 4 5 6 8 9 10
```

## Complexidade

| Caso | Comparações | Tempo |
|------|-------------|-------|
| Melhor (já ordenado) | `n - 1` | **O(n)** |
| Médio | ~`n²/4` | **O(n²)** |
| Pior (ordem inversa) | ~`n²/2` | **O(n²)** |

- **Espaço:** `O(1)` — ordena no próprio vetor (*in-place*), usando só a variável `chave` que guarda o valor sendo inserido.
- **Estável:** sim — elementos iguais não trocam de posição relativa, pois o deslocamento só ocorre em `>` estrito.
- **Deslocamentos no pior caso:** `O(n²)`.

No melhor caso o vetor já está ordenado, então o `while` falha logo na primeira comparação de cada chave: é uma comparação por passagem, `n - 1` no total, daí o `O(n)`.

## Quando usar

Vale a pena em vetores pequenos ou quase ordenados, onde o custo por elemento é baixo e o `O(n²)` não pesa. Por isso é comum usá-lo como sub-rotina de quicksort/mergesort: as implementações trocam para insertion sort quando a partição fica pequena.

## Compilar e executar

```bash
gcc -Wall -g InsertionSort.C -o InsertionSort.out
./InsertionSort.out
```
