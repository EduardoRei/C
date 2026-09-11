# Shell Sort

Insertion sort com passo variável: em vez de comparar apenas vizinhos, compara elementos
separados por uma distância `gap` que vai diminuindo a cada rodada, até chegar a `1`. As
primeiras rodadas jogam valores muito fora do lugar para perto do destino com poucos
deslocamentos; a última rodada é um insertion sort comum, mas sobre um vetor já quase
ordenado — que é justamente o caso em que ele é rápido.

## Como funciona

1. O laço externo começa com `gap = tam / 2` e reduz pela metade (`gap /= 2`) até `gap = 1`.
2. Para cada `gap`, o laço do meio percorre `i` de `gap` até `tam - 1`, tratando `v[i]` como a chave a inserir.
3. O laço interno é o insertion sort, só que andando de `gap` em `gap`: enquanto `v[j - gap] > copia`, desloca esse valor para a frente (`v[j] = v[j - gap]`) e recua `j -= gap`.
4. Quando o laço para, `j` é a posição onde a chave pertence dentro da sua subsequência, e `v[j] = copia` a coloca ali.
5. Com `gap = 1` a passagem final é um insertion sort completo, o que garante o vetor ordenado no fim.

A ideia é que, com `gap = 4`, o vetor é visto como 4 subsequências independentes
(`v[0],v[4]`, `v[1],v[5]`, ...), cada uma ordenada por insertion sort. Um elemento que
precisaria de 7 deslocamentos de uma casa pode chegar perto do lugar com um único salto.

O `gap = 1` no fim não é opcional: é ele que garante a ordenação. As rodadas anteriores
existem só para deixar o serviço mais barato para ele.

### Exemplo

```
Entrada: 5 3 1 2 4 7 2 6

gap = 4: 4 3 1 2 5 7 2 6   <- pares (0,4) (1,5) (2,6) (3,7); só o 5/4 trocou
gap = 2: 1 2 2 3 4 6 5 7   <- pares de 2 em 2; o vetor já ficou quase ordenado
gap = 1: 1 2 2 3 4 5 6 7   <- insertion sort comum, só o 6/5 fora do lugar

Saída:   1 2 2 3 4 5 6 7
```

## Complexidade

| Caso | Tempo |
|------|-------|
| Melhor (já ordenado) | **O(n log n)** |
| Médio | depende da sequência de gaps (~**O(n^1,25)** na prática) |
| Pior (com gaps `n/2, n/4, ...`) | **O(n²)** |

- **Espaço:** `O(1)` — ordena no próprio vetor (*in-place*), usando só `copia`, `gap` e os índices.
- **Estável:** não — comparações a distância movem elementos por cima de valores iguais em outra subsequência.
- **Sem recursão:** ao contrário do merge e do quicksort, não consome pilha.

A complexidade do shell sort é o ponto curioso do algoritmo: **depende inteiramente da
sequência de gaps escolhida**, e para várias delas nem se conhece o limite exato. A usada
aqui (`n/2`, `n/4`, ... — sequência de Shell) é a mais simples e tem pior caso `O(n²)`.
Sequências melhores, como a de Ciura (`1, 4, 10, 23, 57, 132, 301, 701`) ou a de Sedgewick,
levam o desempenho real bem abaixo disso.

## Quando usar

Boa opção para vetores de tamanho médio quando não se pode alocar memória extra e a
recursão é indesejada — sistemas embarcados, por exemplo. É bem mais rápido que os `O(n²)`
puros e muito mais simples de escrever que quicksort ou merge sort, mas perde para eles em
vetores grandes.

## Compilar e executar

```bash
gcc -Wall -g shellsort.c -o shellsort.out
./shellsort.out
```
