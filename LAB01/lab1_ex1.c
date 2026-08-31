typedef struct Node
{
    int info;
    struct node * prox;
}node

typedef struct Fila
{
    node * inicio;
    node * fim;
}fila

void inicializaFila (fila * f)
{
    f -> inicio = NULL;
    f -> final = NULL;
}


void Empilha_Elemen(fila * f, int v)
{
    node * novo = (node*) malloc(sizeof(node));
    novo -> info = v;
    novo -> prox = NULL;
    if (f->inicio == NULL)
    {
        f->inicio = novo;
        f->final = novo;
    }
    else
    {
        
    }
}

