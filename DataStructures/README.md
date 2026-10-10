# DataStructures

Implementações de estruturas de dados em C, para estudo.

As estruturas ficam agrupadas por categoria (`Linear/`, ...), cada uma em seu próprio
arquivo `.c` com os testes dentro do `main`.

| Estrutura | Arquivo | Acesso | Busca | Inserção | Remoção | Espaço |
|-----------|---------|--------|-------|----------|---------|--------|
| [Pilha sequencial](Linear/SequentialStack.c) | `Linear/SequentialStack.c` | O(1) topo | O(n) | **O(1)** topo | **O(1)** topo | O(n) fixo |
| [Lista duplamente encadeada](Linear/DoubleLinkedListVoid.c) | `Linear/DoubleLinkedListVoid.c` | O(n) | O(n) | **O(1)** pontas / O(n) índice | **O(1)** pontas / O(n) índice | O(n) |

Todo `O(1)` acima é tempo real constante, não amortizado: nenhuma das duas estruturas
redimensiona.

---

## Pilha sequencial (LIFO)

Vetor de tamanho fixo mais um índice `top`. Último a entrar é o primeiro a sair.
A capacidade é definida no `stack_init` e **não cresce** — `stack_push` numa pilha cheia
falha com `ErrorCode` em vez de realocar.

| Operação | Melhor | Pior | Por quê |
|----------|--------|------|---------|
| `stack_push` | O(1) | **O(1)** | escreve em `data[top]` e incrementa; nenhum deslocamento |
| `stack_pop` | O(1) | **O(1)** | lê `data[top-1]` e decrementa |
| `stack_top` / `stack_is_empty` / `stack_size` | O(1) | O(1) | só leem `top` |
| `stack_init` | O(1) | O(1) | dois `malloc`, sem inicializar o vetor |
| `stack_destroy` | O(1) | O(1) | dois `free`; os `int` não têm dono próprio |
| busca por valor | O(1) | O(n) | não implementada; exigiria varrer o vetor |

- **Espaço:** `O(n)` onde `n` é a capacidade — alocado inteiro de uma vez, ocupado ou não.
- **Melhor = pior** em todas as operações da API. Não há caso degenerado: nenhuma operação
  depende de quantos elementos já existem.
- O `pop` não apaga o valor removido, só recua o `top`. O dado antigo fica no vetor até ser
  sobrescrito por um `push` — o que é correto aqui, mas significa que a pilha não serve para
  guardar dado sensível.

Comparada a uma pilha encadeada: ganha em localidade de cache (vetor contíguo) e não
paga `malloc` por elemento, mas perde em flexibilidade por causa do limite fixo.

---

## Lista duplamente encadeada genérica

Nós com `next` e `prev`, mais ponteiros para `head` e `tail` na estrutura da lista.
Genérica por `void *`: a lista guarda `data_size` e **copia o dado por valor** com `memcpy`
em memória própria, então o chamador pode descartar o original — vale para qualquer tipo
de tamanho fixo (`int`, `struct`, ...).

| Operação | Melhor | Pior | Por quê |
|----------|--------|------|---------|
| `list_insert_front` | O(1) | **O(1)** | `head` conhecido; religa 2 ponteiros |
| `list_insert_back` | O(1) | **O(1)** | `tail` conhecido; sem varrer a lista |
| `list_insert_index` | O(1) | **O(n)** | O(1) em `0` e `size` (delega às pontas); senão caminha até o índice |
| `list_rm_front` | O(1) | **O(1)** | `head` conhecido |
| `list_rm_back` | O(1) | **O(1)** | `prev` do `tail` dá o novo fim de graça |
| `list_rm_index` | O(1) | **O(n)** | O(1) em `0` e `size-1`; senão caminha até o índice |
| `list_size` | O(1) | O(1) | contador mantido na estrutura, não recontado |
| acesso / busca por índice | O(1) | O(n) | sem acesso aleatório: só dá para caminhar |
| `list_destroy` | O(n) | O(n) | percorre liberando `data` e nó de cada elemento |

- **Espaço:** `O(n)`, com dois ponteiros de overhead por elemento (16 bytes em 64 bits) mais
  a cópia do dado e dois `malloc` por nó.
- **Melhor caso das operações por índice:** as pontas. `list_insert_index(l, 0, ...)` e
  `list_insert_index(l, size, ...)` são O(1) porque delegam para `insert_front`/`insert_back`.
  O pior caso é um índice no meio, que custa a caminhada.
- **O `tail` é o que torna a inserção no fim O(1).** Sem ele, `insert_back` precisaria varrer
  a lista toda para achar o último nó — O(n).
- **O `prev` é o que torna a remoção no fim O(1).** Numa lista *simplesmente* encadeada,
  remover o último elemento é O(n) mesmo com `tail`, porque é preciso achar o penúltimo nó
  para zerar o `next` dele. É o principal ganho da lista dupla.
- A caminhada é O(n) e não O(n/2): a implementação sempre parte do `head`. Como há `prev`,
  daria para começar pelo `tail` quando `index > size/2` e cortar o percurso pela metade —
  continua O(n), mas com metade das iterações na média.

### Pilha sequencial vs. lista encadeada

| | Pilha sequencial | Lista duplamente encadeada |
|---|---|---|
| Acesso por índice | O(1) | O(n) |
| Inserir/remover no fim | O(1) | O(1) |
| Inserir/remover no começo | não se aplica | O(1) |
| Inserir/remover no meio | não se aplica | O(n) para achar, O(1) para religar |
| Tamanho | fixo, definido na criação | cresce conforme a memória permitir |
| Memória por elemento | só o dado | dado + 2 ponteiros + overhead do `malloc` |
| Localidade de cache | boa (contígua) | ruim (nós espalhados) |

Vale lembrar que o `O(n)` da lista para achar uma posição e o `O(1)` dela para religar os
ponteiros costumam se inverter na prática em relação ao vetor: num vetor, achar é O(1) mas
inserir no meio é O(n) por causa do deslocamento. A lista paga na busca, o vetor paga no
deslocamento.

---

## Compilar

```bash
gcc -Wall -Wextra -g Linear/<arquivo>.c -o Linear/<arquivo>.out
./Linear/<arquivo>.out
```

Cada arquivo tem um `main` com os casos de teste no formato `esperado / obtido`.
Os binários `.out` são ignorados pelo git.

Para checar vazamento e acesso inválido de memória:

```bash
gcc -Wall -Wextra -g -fsanitize=address,undefined Linear/<arquivo>.c -o Linear/<arquivo>.out
./Linear/<arquivo>.out
leaks --atExit -- ./Linear/<arquivo>.out   # macOS
```
