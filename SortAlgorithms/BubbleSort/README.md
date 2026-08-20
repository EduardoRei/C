# Bubble Sort

Ordenação por "borbulhamento": percorre o vetor comparando pares vizinhos e trocando-os
quando estão fora de ordem. A cada passagem completa, o maior elemento ainda não posicionado
"borbulha" até o final do vetor.

## Como funciona

1. Percorre o vetor da posição `0` até `tamanho - 2`.
2. Se `vetor[i] > vetor[i + 1]`, troca os dois valores e marca que houve troca.
3. Repete a passagem enquanto alguma troca tiver acontecido.
4. Quando uma passagem inteira ocorre sem trocas, o vetor está ordenado.

A flag `trocou` é o que dá a parada antecipada: sem ela, o algoritmo sempre faria
`n - 1` passagens, mesmo com o vetor já ordenado.

### Exemplo

```
Entrada: 5 2 6 3 4 2 8 9 10 1

Passagem 1: 2 5 3 4 2 6 8 9 1 10   <- o 10 chegou ao fim
Passagem 2: 2 3 4 2 5 6 8 1 9 10   <- o 9 chegou ao lugar
...
Saída:   1 2 2 3 4 5 6 8 9 10
```

## Complexidade

| Caso | Comparações | Tempo |
|------|-------------|-------|
| Melhor (já ordenado) | `n - 1` | **O(n)** |
| Médio | ~`n²/2` | **O(n²)** |
| Pior (ordem inversa) | ~`n²/2` | **O(n²)** |

- **Espaço:** `O(1)` — ordena no próprio vetor (*in-place*), usando só a variável auxiliar da troca.
- **Estável:** sim — elementos iguais não trocam de posição relativa, pois a troca só ocorre em `>` estrito.
- **Trocas no pior caso:** `O(n²)`.

O melhor caso `O(n)` só existe por causa da parada antecipada da flag.

## Compilar e executar

```bash
gcc -Wall -g bubblesort.c -o bubblesort.out
./bubblesort.out
```

## Quando usar

Praticamente nunca em produção: para vetores grandes, `O(n²)` é proibitivo. Vale para
vetores muito pequenos, para dados quase ordenados (onde se aproxima de `O(n)`) e,
principalmente, como primeiro contato didático com algoritmos de ordenação.
