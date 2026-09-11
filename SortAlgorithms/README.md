# SortAlgorithms

Implementações de algoritmos de ordenação em C, para estudo.

Cada algoritmo fica em sua própria pasta, com o código-fonte e um `README.md`
explicando o funcionamento e a complexidade.

| Algoritmo | Melhor | Médio | Pior | Espaço | Estável |
|-----------|--------|-------|------|--------|---------|
| [Bubble Sort](BubbleSort/) | O(n) | O(n²) | O(n²) | O(1) | Sim |
| [Insertion Sort](InsertionSort/) | O(n) | O(n²) | O(n²) | O(1) | Sim |
| [Merge Sort](MergeSort/) | O(n log n) | O(n log n) | O(n log n) | O(n) | Sim |
| [Selection Sort](SelectionSort/) | O(n²) | O(n²) | O(n²) | O(1) | Não |
| [Quick Sort](QuickSort/) | O(n log n) | O(n log n) | O(n²) | O(log n) | Não |
| [Shell Sort](ShellSort/) | O(n log n) | ~O(n^1,25) | O(n²) | O(1) | Não |

## Compilar

```bash
gcc -Wall -g <pasta>/<arquivo>.c -o <pasta>/<arquivo>.out
```

Os binarios `.out` sao ignorados pelo git.
