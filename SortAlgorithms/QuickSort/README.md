# Quick Sort

Ordenação por particionamento: escolhe um elemento como **pivô**, rearranja o vetor de modo
que tudo menor ou igual ao pivô fique à esquerda dele e tudo maior à direita, e então repete
o processo recursivamente nas duas partes. Também é *dividir para conquistar*, mas ao
contrário do merge sort o trabalho pesado está na divisão — depois que as partições estão
prontas, não há nada para juntar.

## Como funciona

1. `quickSort` recebe `inicio` e `fim`. Se `inicio >= fim`, o trecho tem 0 ou 1 elemento e já está ordenado.
2. `particionar` toma o último elemento como pivô (`v[fim]`) e mantém `i` como a fronteira dos "menores ou iguais".
3. O laço percorre `j` de `inicio` até `fim - 1`. Sempre que `v[j] <= pivo`, troca `v[i]` com `v[j]` e avança `i` — ou seja, empurra esse valor para dentro da zona dos menores.
4. Ao fim do laço, tudo antes de `i` é `<= pivo` e tudo entre `i` e `fim - 1` é `> pivo`. A troca final `trocar(&v[i], &v[fim])` coloca o pivô exatamente em `i`.
5. `particionar` devolve `i`: essa é a **posição definitiva** do pivô, e por isso ele fica de fora das duas chamadas recursivas (`inicio..meio - 1` e `meio + 1..fim`).

Esse esquema é a partição de **Lomuto**: um só índice de escrita (`i`) varrendo o vetor da
esquerda para a direita. É a versão mais simples de escrever; a alternativa clássica é a
partição de Hoare, com dois índices que caminham um em direção ao outro e faz menos trocas.

### Exemplo

```
Entrada: 6 2 4 6 7 1 3 5     pivô = 5 (último)

j=1 (2<=5): 2 6 4 6 7 1 3 5
j=2 (4<=5): 2 4 6 6 7 1 3 5
j=5 (1<=5): 2 4 1 6 7 6 3 5
j=6 (3<=5): 2 4 1 3 7 6 6 5
pivô entra: 2 4 1 3 [5] 6 6 7   <- o 5 está no lugar definitivo
            \______/     \___/
            recursão     recursão

Saída:   1 2 3 4 5 6 6 7
```

## Complexidade

| Caso | Partições | Tempo |
|------|-----------|-------|
| Melhor (pivô sempre no meio) | `log n` níveis | **O(n log n)** |
| Médio | ~`1,39·log n` níveis | **O(n log n)** |
| Pior (pivô sempre no extremo) | `n` níveis | **O(n²)** |

- **Espaço:** `O(log n)` no caso médio — ordena *in-place*, mas a recursão consome pilha; no pior caso a pilha vai a `O(n)`.
- **Estável:** não — as trocas movem elementos para posições distantes, cruzando valores iguais.
- **Pior caso:** acontece quando o pivô é sempre o menor ou o maior da partição. Com pivô fixo no fim, isso é exatamente o vetor **já ordenado** (ou em ordem inversa): cada partição separa 1 elemento dos outros `n - 1`.

Na prática o quicksort costuma ser mais rápido que o merge sort mesmo tendo o mesmo
`O(n log n)` médio, porque trabalha no próprio vetor — sem alocação e com bom aproveitamento
de cache. O preço é o pior caso `O(n²)`.

Implementações reais fogem dele escolhendo o pivô com mais cuidado: mediana de três
(primeiro, meio e último), pivô aleatório, ou trocando para heapsort quando a recursão fica
funda demais (*introsort*).

## Quando usar

É a escolha padrão para ordenação em memória quando não se precisa de estabilidade: rápido,
*in-place* e com pouca sobrecarga por elemento. Evite a versão com pivô fixo se a entrada
puder chegar já ordenada. Quando o pior caso não pode acontecer, prefira merge sort
(`O(n log n)` garantido) ou heapsort.

## Compilar e executar

```bash
gcc -Wall -g quicksort.c -o quicksort.out
./quicksort.out
```
