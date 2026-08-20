# SortAlgorithms

Implementações de algoritmos de ordenação em C, para estudo.

Cada algoritmo fica em sua própria pasta, com o código-fonte e um `README.md`
explicando o funcionamento e a complexidade.

| Algoritmo | Melhor | Médio | Pior | Espaço | Estável |
|-----------|--------|-------|------|--------|---------|
| [Bubble Sort](BubbleSort/) | O(n) | O(n²) | O(n²) | O(1) | Sim |

## Compilar

```bash
gcc -Wall -g <pasta>/<arquivo>.c -o <pasta>/<arquivo>.out
```

Os binarios `.out` sao ignorados pelo git.
