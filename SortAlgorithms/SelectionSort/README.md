# Selection Sort

Ordenação por seleção: a cada passagem, procura o menor elemento da parte ainda não
ordenada do vetor e o troca com a primeira posição dessa parte. O vetor vai ficando
ordenado da esquerda para a direita, uma posição definitiva por passagem.

## Como funciona

1. Percorre o vetor da posição `0` até `tamanho - 1`; a posição `i` é onde o próximo menor vai ficar.
2. Assume `menorIndicie = i` e varre o resto do vetor (`j = i + 1` até o fim) procurando algo menor.
3. Sempre que `v[j] < v[menorIndicie]`, guarda o novo índice do menor.
4. Terminada a varredura, troca `v[i]` com `v[menorIndicie]` usando a variável `copia`.
5. Quando `i` chega ao fim, todas as posições já receberam seu valor definitivo.

Diferente do bubble sort, aqui não existe parada antecipada: a busca pelo menor sempre
varre toda a parte não ordenada, mesmo que o vetor já esteja ordenado. Em compensação,
faz no máximo `n - 1` trocas — bem menos que os `O(n²)` do bubble sort.

O `if(v[menorIndicie] != v[i])` só evita a troca quando os valores são iguais; é uma
economia pequena, já que a comparação em si custa o mesmo que a troca evitada.

### Exemplo

```
Entrada: 5 3 1 2 4 7 2 6

Passagem 1: 1 3 5 2 4 7 2 6   <- menor é o 1, troca com o 5
Passagem 2: 1 2 5 3 4 7 2 6   <- menor do resto é o 2, troca com o 3
Passagem 3: 1 2 2 3 4 7 5 6   <- menor do resto é o outro 2, troca com o 5
Passagem 4: 1 2 2 3 4 7 5 6   <- o 3 já está no lugar, sem troca
...
Saída:   1 2 2 3 4 5 6 7
```

## Complexidade

| Caso | Comparações | Tempo |
|------|-------------|-------|
| Melhor (já ordenado) | ~`n²/2` | **O(n²)** |
| Médio | ~`n²/2` | **O(n²)** |
| Pior (ordem inversa) | ~`n²/2` | **O(n²)** |

- **Espaço:** `O(1)` — ordena no próprio vetor (*in-place*), usando só `copia` e `menorIndicie`.
- **Estável:** não — a troca joga o elemento de `v[i]` para longe, podendo passá-lo por cima de um valor igual. Em `2a 2b 1`, o `1` troca com o `2a`, que vai parar depois do `2b`.
- **Trocas:** no máximo `n - 1`, em qualquer caso.

O número de comparações é sempre o mesmo (`n(n-1)/2`), independente da entrada: não há
melhor caso `O(n)` como no bubble e no insertion sort.

## Quando usar

Quando a troca é a operação cara e a comparação é barata — por exemplo, registros grandes
em memória ou escritas custosas — já que faz no máximo `n - 1` trocas. Fora disso, o
insertion sort costuma ser melhor para vetores pequenos, e para vetores grandes o `O(n²)`
inviabiliza os dois.

## Compilar e executar

```bash
gcc -Wall -g selectionsort.c -o selectionsort.out
./selectionsort.out
```
