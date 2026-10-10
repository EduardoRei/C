# Heap Sort

Ordena usando um *max-heap*: uma árvore binária guardada dentro do próprio vetor em que
todo pai é maior ou igual aos seus filhos. Nessa estrutura o maior elemento está sempre na
raiz (`arr[0]`), então basta tirá-lo de lá, colocá-lo no fim do vetor e consertar o heap
com o que sobrou — repetindo até não restar nada. É um selection sort que acha o máximo em
`O(log n)` em vez de `O(n)`.

## O heap dentro do vetor

Não há ponteiros: a árvore é só uma forma de ler os índices. Para o nó na posição `i`:

| Relação | Índice | Função |
|---------|--------|--------|
| Filho esquerdo | `2i + 1` | `get_left` |
| Filho direito | `2i + 2` | `get_right` |
| Pai | `(i - 1) / 2` | `get_parent` |

```
vetor: 7 6 4 6 2 1 3 5

              7            <- arr[0]
          6       4        <- arr[1], arr[2]
        6   2   1   3      <- arr[3] .. arr[6]
      5                    <- arr[7]
```

## Como funciona

1. **`max_heapify(arr, i, heap_size)`** conserta um único nó: compara `arr[i]` com os dois
   filhos (ignorando os que caem fora de `heap_size`) e, se algum for maior, troca com o
   maior deles e chama a si mesma na posição para onde o valor desceu. Pressupõe que as
   duas subárvores de `i` já são heaps.
2. **`build_max_heap`** transforma o vetor inteiro em heap chamando `max_heapify` do meio
   para o início (`i = heap_size / 2` até `0`). Da metade em diante só há folhas, que já são
   heaps de um elemento; indo de trás para a frente, quando um nó é tratado seus filhos já
   estão prontos.
3. **`heap_sort`** constrói o heap e depois percorre `i` de `heap_size - 1` até `1`:
   - troca `arr[0]` (o maior) com `arr[i]`, que passa a estar na posição final;
   - chama `max_heapify(arr, 0, i)` para consertar a raiz, agora com o heap **encolhido**
     para `i` elementos — o trecho `arr[i..]` já está ordenado e não pode mais ser tocado.

O tamanho passado no passo 3 é o detalhe que mais derruba a implementação: se o heap não
encolher, o elemento recém-colocado no fim é puxado de volta para dentro dele.

### Exemplo

```
Entrada:        6 2 4 6 7 1 3 5

build_max_heap: 7 6 4 6 2 1 3 5     <- o 7 subiu para a raiz

i = 7:          6 6 4 5 2 1 3 | 7   <- à direita da barra: já ordenado
i = 6:          6 5 4 3 2 1 | 6 7
i = 5:          5 3 4 1 2 | 6 6 7
i = 4:          4 3 2 1 | 5 6 6 7
i = 3:          3 1 2 | 4 5 6 6 7
i = 2:          2 1 | 3 4 5 6 6 7
i = 1:          1 | 2 3 4 5 6 6 7

Saída:          1 2 3 4 5 6 6 7
```

## Complexidade

| Caso | Tempo |
|------|-------|
| Melhor | **O(n log n)** |
| Médio | **O(n log n)** |
| Pior | **O(n log n)** |

- **Construção do heap:** `O(n)`, não `O(n log n)` — a maioria dos nós está perto das folhas e desce pouco.
- **Extrações:** `n - 1` chamadas de `max_heapify`, cada uma `O(log n)` (a altura da árvore). É daqui que vem o `O(n log n)`.
- **Espaço:** ordena no próprio vetor (*in-place*). Como `max_heapify` aqui é recursiva, a pilha chega a `O(log n)`; trocando a recursão por um laço o algoritmo fica `O(1)`.
- **Estável:** não — as trocas entre a raiz e o fim do vetor saltam por cima de elementos iguais.

Ao contrário do quicksort, não existe entrada ruim: o pior caso também é `O(n log n)`.

## Quando usar

Quando é preciso garantia de `O(n log n)` no pior caso sem gastar memória extra — o
quicksort não dá a primeira, o merge sort não dá a segunda. Na prática costuma ser mais
lento que o quicksort, porque salta pelo vetor (pai e filhos ficam longe um do outro) e
aproveita mal o cache. Por isso aparece mais como plano B: o *introsort* começa com
quicksort e muda para heap sort se a recursão ficar funda demais.

## Compilar e executar

```bash
gcc -Wall -g heapsort.c -o heapsort.out
./heapsort.out
```

O `main` roda o algoritmo sobre vários vetores (aleatório, já ordenado, invertido, com
repetidos, com negativos, de 2, 1 e 0 elementos), imprime antes e depois e marca `OK` ou
`FAIL` em cada um. O programa retorna diferente de zero se algum falhar.
