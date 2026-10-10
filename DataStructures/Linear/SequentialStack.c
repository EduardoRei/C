#include <stdio.h>
#include <stdlib.h>

#define ErrorCode 99 // generic error code, 0 is success
#define SucessCode 0 

typedef struct 
{
    int *data;
    int capacity;
    size_t top;
} sequential_stack_t;


sequential_stack_t* stack_init(int capacity)
{
    if (capacity <= 0 )
    {
        return NULL;
    }

    sequential_stack_t *s = malloc(sizeof(sequential_stack_t));
    if(s == NULL) 
    {
        return NULL;
    }

    s->data = malloc(capacity * sizeof(int));
    if(s->data == NULL)
    {
        free(s);
        return NULL;
    }

    s->capacity = capacity;
    s->top = 0;
    return s;
}

int stack_push(sequential_stack_t *s, int value) //O(1)
{
    if(s == NULL)
    {
        return ErrorCode; 
    }

    if (s->top == s->capacity)
    {
        return ErrorCode;
    }

    s->data[s->top] = value;
    s->top++;
    return SucessCode;
}

int stack_pop(sequential_stack_t *s, int *value) // O(1)
{
    if(s == NULL || value == NULL)
    {
        return ErrorCode;
    }

    if(s->top == 0)
    {
        return ErrorCode;
    }
    *value = s->data[s->top - 1];
    //we don't need to erase the top value, we can just diminish by 1 and when added a new value the old one will be overwritten
    s->top--;
    return SucessCode;
}

int stack_is_empty(sequential_stack_t *s) // O (1)
{
    if(s == NULL)
    {
        return ErrorCode;
    }

    return s->top != 0;
}

int stack_size(sequential_stack_t *s) // O(1)
{
    if(s == NULL)
    {
        return ErrorCode;
    }

    return s->top;
}

void stack_destroy(sequential_stack_t **sp) //O(1)
{
    if(sp == NULL || *sp == NULL)
    {
        return;
    }

    free((*sp)->data);
    free(*sp);
    *sp = NULL;
}

//print logic will be the same as push (LiFo) 
void printStack(sequential_stack_t *s) //O(N)
{
    if(s == NULL)
    {
        return;
    }

    if(s->top == 0)
    {
        return;
    }

    int i;
    printf("\n");
    
    for(i = s->top - 1; i >= 0; i--)
    {
        printf("%d ", s->data[i]);
    }
    
    printf("\n");
}

int main()
{
    sequential_stack_t *s = stack_init(6);

    if(s == NULL)
    {
        return ErrorCode;
    }
    //01 - IsEmpty Test
    printf("Stack is empty? got %d, expected 0. \n", stack_is_empty(s));
    
    //02 - Push 3 times
    int a = 10, b = 20, c = 30;
    stack_push(s, a);
    stack_push(s, b);
    stack_push(s, c);
    printStack(s);
    printf("Size expected 3, got %d \n",stack_size(s));
    printf("Stack is empty? got %d, expected 1. \n", stack_is_empty(s));

    //03 - Pop 2 times in right order
    int out;
    stack_pop(s, &out);
    printf("removido %d, esperado %d\n", out, c);
    stack_pop(s, &out);
    printf("removido %d, esperado %d\n", out, b);
    printStack(s);

    //04 - Destoy stack
    printf("stack destroy\n");
    printf("before:  %p\n", (void*)s);
    stack_destroy(&s);
    printf("after: %p\n", (void*)s);
    printStack(s);

    return 0;
}