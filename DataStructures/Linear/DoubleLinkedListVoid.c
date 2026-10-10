#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node_s {
    void *data;
    struct list_node_s *next, *prev;
} list_node_t;

typedef struct list_s {
    list_node_t *head, *tail;
    size_t data_size;
    size_t size;
} list_t;

list_t* list_init(size_t data_size)
{
    if(data_size <= 0)
    {
        return NULL;
    }

    list_t *l = malloc(sizeof(list_t));
    if(l == NULL)
    {
        return NULL;
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    l->data_size = data_size;
    return l;
}

int list_insert_front(list_t *l, const void *data)
{
    if(l == NULL || data == NULL)
    {
        return -1;
    }

    list_node_t *node = malloc(sizeof(list_node_t));
    if(node == NULL)
    {
        return -1;
    }

    node->data = malloc(l->data_size);
    if(node->data == NULL)
    {
        free(node);
        return -1;
    }
    memcpy(node->data, data, l->data_size);
    node->prev = NULL;
    node->next = l->head; //funciona mesmo se a lista estiver vazia, se vazia aponta pra null
    if(l->tail == NULL)
    {
        l->tail = node;
    } 
    else 
    {
        l->head->prev = node;
    }

    l->head = node;    
    l->size++;

    return 0;
}

int list_insert_back(list_t *l, const void *data)
{
    if(l == NULL || data == NULL)
    {
        return -1;
    }

    list_node_t *node = malloc(sizeof(list_node_t));
    if(node == NULL)
    {
        return -1;
    }

    node->data = malloc(l->data_size);
    if(node->data == NULL)
    {
        free(node);
        return -1;
    }
    memcpy(node->data, data, l->data_size);
    node->next = NULL;
    node->prev = l->tail;
    if(l->head == NULL)
    {
        l->head = node;
    } 
    else 
    {
        l->tail->next = node;
    }

    l->tail = node;
    l->size++;

    return 0;
}

int list_insert_index (list_t *l, int index, const void *data)
{
    if(l == NULL || data == NULL)
    {
        return -1;
    }

    if(index < 0 || index > (int) l->size)
    {
        return -1;
    }

    if(index == 0)
    {
        return list_insert_front(l, data);
    }

    if(index == (int)l->size)
    {
        return list_insert_back(l, data);
    }

    list_node_t *node = malloc(sizeof(list_node_t));
    if(node == NULL)
    {
        return -1;
    }

    node->data = malloc(l->data_size);
    if(node->data == NULL)
    {
        free(node);
        return -1;
    }

    memcpy(node->data, data, l->data_size);
    
    list_node_t *c = l->head;
    for(int i = 0; i < index; i++)
    {
        c = c->next;
    }

    node->prev = c->prev;
    node->next = c;
    c->prev->next = node;
    c->prev = node;
    l->size++;

    return 0;
}

int list_rm_front(list_t *l, void *data)
{
    if(l == NULL || data == NULL || l->head == NULL)
    {
        return -1;
    }

    list_node_t *node = l->head;
    memcpy(data, node->data, l->data_size);
    l->head = node->next;
    if(l->head != NULL)
    {
        l->head->prev = NULL;
    }
    else
    {
        l->tail = NULL;
    }
    free(node->data);
    free(node);
    l->size--;

    return 0;
}

int list_rm_back(list_t *l, void *data)
{
    if(l == NULL || data == NULL || l->head == NULL)
    {
        return -1;
    }

    list_node_t *node = l->tail;
    memcpy(data, node->data, l->data_size);
    l->tail = node->prev;
    if(l->tail != NULL)
    {
        l->tail->next = NULL;
    }
    else
    {
        l->head = NULL;
    }
    free(node->data);
    free(node);
    l->size--;

    return 0;
}

int list_rm_index(list_t *l, int index, void *data)
{
    if(l == NULL || data == NULL || l->head == NULL)
    {
        return -1;
    }

    if(index < 0 || index >= (int) l->size)
    {
        return -1;
    }

    if(index == 0)
    {
        return list_rm_front(l, data);
    }

    if(index == (int) l->size -1)
    {
        return list_rm_back(l, data);
    }
    
    list_node_t *c = l->head;
    for(int i = 0; i < index; i++)
    {
        c = c->next;
    }

    list_node_t *prev = c->prev;
    list_node_t *next = c->next;
    
    prev->next = next;
    next->prev = prev;
    memcpy(data, c->data, l->data_size);
    free(c->data);
    free(c);

    l->size--;

    return 0;
}

int list_size(list_t *l)
{
    if(l == NULL)
    {
        return 0;
    }

    return l->size;
}

void list_destroy(list_t *l)
{
    if(l == NULL)
    {
        return;
    }

    list_node_t *n = l->head;
    for(int i = 0; i < (int)l->size; i++)
    {
        n = n->next;
        free(l->head->data);
        free(l->head);
        l->head = n;
    }

    free(l);
    return;
}



void printListInt(list_t *l)
{
    if(l == NULL)
    {
        printf("lista nula\n");
        return;
    }

    printf("[ ");
    for(list_node_t *c = l->head; c != NULL; c = c->next)
    {
        printf("%d ", *(int*)c->data);
    }
    printf("] size=%d\n", list_size(l));
}

void printListIntReverse(list_t *l)
{
    if(l == NULL)
    {
        printf("lista nula\n");
        return;
    }

    printf("[ ");
    for(list_node_t *c = l->tail; c != NULL; c = c->prev)
    {
        printf("%d ", *(int*)c->data);
    }
    printf("] (tras pra frente)\n");
}

typedef struct {
    char name[16];
    int age;
} person_t;

int main()
{
    int out;

    //00 - Init invalido
    printf("list_init(0) e NULL? got %d, expected 1\n", list_init(0) == NULL);

    list_t *l = list_init(sizeof(int));
    if(l == NULL)
    {
        return 1;
    }

    //01 - Lista vazia
    printf("size expected 0, got %d\n", list_size(l));
    printf("rm_front em lista vazia expected -1, got %d\n", list_rm_front(l, &out));
    printf("rm_back em lista vazia expected -1, got %d\n", list_rm_back(l, &out));
    printf("rm_index em lista vazia expected -1, got %d\n", list_rm_index(l, 0, &out));

    //02 - Argumentos invalidos
    int tmp = 1;
    printf("insert_front(NULL) expected -1, got %d\n", list_insert_front(NULL, &tmp));
    printf("insert_front(data NULL) expected -1, got %d\n", list_insert_front(l, NULL));

    //03 - insert_front 3 vezes -> espera 30 20 10
    int a = 10, b = 20, c = 30;
    list_insert_front(l, &a);
    list_insert_front(l, &b);
    list_insert_front(l, &c);
    printf("expected [ 30 20 10 ] size=3, got ");
    printListInt(l);

    //04 - prev esta certo? mesma lista ao contrario -> 10 20 30
    printf("expected [ 10 20 30 ], got ");
    printListIntReverse(l);

    //05 - insert_back 2 vezes -> 30 20 10 40 50
    int d = 40, e = 50;
    list_insert_back(l, &d);
    list_insert_back(l, &e);
    printf("expected [ 30 20 10 40 50 ] size=5, got ");
    printListInt(l);
    printf("expected [ 50 40 10 20 30 ], got ");
    printListIntReverse(l);

    //06 - insert_index no meio (indice 2) -> 30 20 99 10 40 50
    int f = 99;
    printf("insert_index(2) expected 0, got %d\n", list_insert_index(l, 2, &f));
    printf("expected [ 30 20 99 10 40 50 ] size=6, got ");
    printListInt(l);
    printf("expected [ 50 40 10 99 20 30 ], got ");
    printListIntReverse(l);

    //07 - insert_index nas bordas: 0 vira front, size vira back
    int g = 1, h = 7;
    printf("insert_index(0) expected 0, got %d\n", list_insert_index(l, 0, &g));
    printf("insert_index(size) expected 0, got %d\n", list_insert_index(l, list_size(l), &h));
    printf("expected [ 1 30 20 99 10 40 50 7 ] size=8, got ");
    printListInt(l);

    //08 - insert_index fora de faixa (size+1 e negativo)
    printf("insert_index(-1) expected -1, got %d\n", list_insert_index(l, -1, &g));
    printf("insert_index(size+1) expected -1, got %d\n", list_insert_index(l, list_size(l) + 1, &g));
    printf("size continua 8? got %d\n", list_size(l));

    //09 - rm_front e rm_back devolvem o dado certo
    printf("rm_front expected 0/1, got %d/", list_rm_front(l, &out));
    printf("%d\n", out);
    printf("rm_back expected 0/7, got %d/", list_rm_back(l, &out));
    printf("%d\n", out);
    printf("expected [ 30 20 99 10 40 50 ] size=6, got ");
    printListInt(l);

    //10 - rm_index no meio devolve o dado (indice 2 == 99)
    printf("rm_index(2) expected 0/99, got %d/", list_rm_index(l, 2, &out));
    printf("%d\n", out);
    printf("expected [ 30 20 10 40 50 ] size=5, got ");
    printListInt(l);

    //11 - rm_index no ultimo indice valido (size-1 == 50), o que segfaultava
    printf("rm_index(size-1) expected 0/50, got %d/", list_rm_index(l, list_size(l) - 1, &out));
    printf("%d\n", out);
    printf("expected [ 30 20 10 40 ] size=4, got ");
    printListInt(l);
    printf("expected [ 40 10 20 30 ], got ");
    printListIntReverse(l);

    //12 - rm_index fora de faixa: size e negativo nao removem nada
    printf("rm_index(size) expected -1, got %d\n", list_rm_index(l, list_size(l), &out));
    printf("rm_index(-1) expected -1, got %d\n", list_rm_index(l, -1, &out));
    printf("size continua 4? got %d\n", list_size(l));

    //13 - esvaziar tudo e inserir de novo (head/tail precisam estar NULL)
    while(list_size(l) > 0)
    {
        list_rm_front(l, &out);
    }
    printf("size expected 0, got %d\n", list_size(l));
    printf("head NULL? got %d, tail NULL? got %d, expected 1/1\n", l->head == NULL, l->tail == NULL);
    list_insert_front(l, &a);
    printf("reinsert depois de esvaziar: expected [ 10 ] size=1, got ");
    printListInt(l);

    //14 - mesmo teste esvaziando por tras
    while(list_size(l) > 0)
    {
        list_rm_back(l, &out);
    }
    printf("head NULL? got %d, tail NULL? got %d, expected 1/1\n", l->head == NULL, l->tail == NULL);
    list_insert_back(l, &b);
    printf("reinsert depois de esvaziar por tras: expected [ 20 ] size=1, got ");
    printListInt(l);

    list_destroy(l);
    printf("lista de int destruida\n");

    //15 - generico: funciona com struct, nao so com int
    list_t *p = list_init(sizeof(person_t));
    if(p == NULL)
    {
        return 1;
    }

    person_t p1 = {"Eduardo", 25};
    person_t p2 = {"Maria", 30};
    person_t pout;

    list_insert_back(p, &p1);
    list_insert_back(p, &p2);
    printf("size expected 2, got %d\n", list_size(p));

    list_rm_front(p, &pout);
    printf("expected Eduardo/25, got %s/%d\n", pout.name, pout.age);
    list_rm_front(p, &pout);
    printf("expected Maria/30, got %s/%d\n", pout.name, pout.age);
    printf("size expected 0, got %d\n", list_size(p));

    //16 - copia por valor: mexer no original nao muda a lista
    person_t p3 = {"Joao", 40};
    list_insert_back(p, &p3);
    strcpy(p3.name, "ALTERADO");
    p3.age = 999;
    list_rm_front(p, &pout);
    printf("expected Joao/40, got %s/%d\n", pout.name, pout.age);

    list_destroy(p);
    printf("lista de person destruida\n");

    //17 - destroy aceita NULL sem quebrar
    list_destroy(NULL);
    printf("list_destroy(NULL) ok\n");

    return 0;
}
