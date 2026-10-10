#include <stdio.h>

int get_left(int i)
{
    return (2 * i) + 1;
}

int get_right(int i)
{
    return (2 * i) + 2;
}

int get_parent(int i)
{
    return (int)((i - 1) / 2);
}

void swap(int *x, int *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}

void max_heapify(int arr[], int i, int heap_size)
{
    if(i >= heap_size)
    {
        return;
    }

    int left = get_left(i);
    int right = get_right(i);
    int largest = i;

    if(left < heap_size && arr[left] > arr[largest])
    {
        largest = left;
    }

    if(right < heap_size && arr[right] > arr[largest])
    {
        largest = right;
    }

    if(largest != i)
    {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, largest, heap_size);
    }
}

void build_max_heap(int arr[], int heap_size)
{
    for(int i = (int)(heap_size / 2); i >= 0; i--)
    {
        max_heapify(arr, i, heap_size);
    }
}

void heap_sort(int arr[], int heap_size)
{
    if(heap_size <= 1)
    {
        return;
    }

    build_max_heap(arr, heap_size);
    for(int i = heap_size - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, 0, i);
    }
}
void print_array(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int is_sorted(int arr[], int size)
{
    for(int i = 1; i < size; i++)
    {
        if(arr[i - 1] > arr[i])
        {
            return 0;
        }
    }
    return 1;
}

int run_test(const char *name, int arr[], int size)
{
    printf("%s\n", name);
    print_array(arr, size);
    heap_sort(arr, size);
    print_array(arr, size);

    int ok = is_sorted(arr, size);
    printf("%s\n\n", ok ? "OK" : "FAIL");
    return ok;
}

int main()
{
    int random[] = {6, 2, 4, 6, 7, 1, 3, 5};
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int reversed[] = {8, 7, 6, 5, 4, 3, 2, 1};
    int duplicates[] = {3, 3, 1, 3, 1, 1, 3};
    int negatives[] = {-2, 5, 0, -7, 3, -1};
    int two[] = {2, 1};
    int one[] = {42};

    int failed = 0;

    failed += !run_test("random", random, 8);
    failed += !run_test("already sorted", sorted, 8);
    failed += !run_test("reversed", reversed, 8);
    failed += !run_test("duplicates", duplicates, 7);
    failed += !run_test("negatives", negatives, 6);
    failed += !run_test("two elements", two, 2);
    failed += !run_test("one element", one, 1);
    failed += !run_test("empty", one, 0);

    printf("%d test(s) failed\n", failed);

    return failed != 0;
}