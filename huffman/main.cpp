#include <iostream>

using namespace std;

typedef struct sArvore
{
    char elemento;
    struct sArvore *esquerda;
    struct sArvore *direita;
} Arvore;

typedef struct lista
{
    int freq;
    char elem;
    struct lista *prox;
} Lista;

int existeElemento(Lista *listaE, char elem)
{
    Lista *aux = listaE;
    if(aux != NULL)
    {
        while(aux->prox != NULL && aux->elem != elem)
        {
            aux = aux->prox;
        }
        if(aux->elem == elem)
            return 1;
    }
    return 0;
}

void imprime(Lista *lista)
{
    Lista *aux = lista;
    while(aux != NULL)
    {
        cout<<aux->elem<<" - "<<aux->freq<<endl;
        aux = aux->prox;
    }
}

Lista* ordenarLista(Lista *lista)
{
    Lista *aux, *p, *ant, *aj;

    if(lista != NULL)
    {
        p = lista;
        ant = p;
        while(p->prox != NULL)
        {
            aux = p->prox;
            while(aux->prox != NULL && p->freq <= aux->freq)
            {
                aj = aux;
                aux = aux->prox;
            }
            if(p->freq > aux->freq)
            {
                if(p->prox == aux)
                {
                    if(p == ant)
                    {
                        lista = aux;
                        p->prox = aux->prox;
                        aux->prox = p;
                    }
                    else
                    {
                        ant->prox = aux;
                        p->prox = aux->prox;
                        aux->prox = p;
                    }
                }
                else
                {
                    if(p == ant)
                    {
                        Lista *troca;
                        troca = aux->prox;
                        lista = aux;
                        aj->prox = p;
                        aux->prox = p->prox;
                        p->prox = troca;
                    }
                    else
                    {
                        Lista *troca;
                        troca = aux->prox;
                        ant->prox = aux;
                        aux->prox = p->prox;
                        p->prox = troca;
                        aj->prox = p;
                    }
                }
                p = aux;
            }
            ant = p;
            p = p->prox;
        }
    }
    return lista;
}

Lista* buscaElemento(Lista *lista, char elem)
{
    Lista *aux;
    if(lista != NULL)
    {
        aux = lista;
        while(aux->prox != NULL && aux->elem != elem)
        {
            aux = aux->prox;
        }
        if(aux->elem == elem)
            return aux;
    }
    return NULL;
}

Lista* insere(Lista *lista, char elem)
{
    Lista *novo, *nodo;
    novo = (Lista*)malloc(sizeof(Lista));

    if(existeElemento(lista, elem))
    {
        nodo = buscaElemento(lista, elem);
        nodo->freq += 1;
        return ordenarLista(lista);
    }

    novo->elem = elem;
    novo->freq = 1;
    if(lista == NULL)
    {
        novo->prox = NULL;
        lista = novo;
    }
    else
    {
        novo->prox = lista;
        lista = novo;
    }
    return ordenarLista(lista);
}

Lista* retiraLista(Lista *lista, char elem)
{
    Lista *elim, *ant;

    if(lista != NULL)
    {
        elim = lista;
        ant = elim;
        while(elim->prox != NULL && elim->elem != elem)
        {
            ant = elim;
            elim = elim->prox;
        }
        if(elim->elem == elem && elim == ant)
        {
            lista = elim->prox;
            free(elim);
        }
        else if(elim->elem == elem && elim->prox == NULL)
        {
            ant->prox = elim->prox;
            free(elim);
        }
        else if(elim->elem == elem)
        {
            ant->prox = elim->prox;
            free(elim);
            lista = ant;
        }
        else
            cout<<"Elemento nao existe"<<endl;
    }
    return lista;
}

Lista* frequencia(Lista *lista, string texto)
{
    for (int i = 0; i < texto.length(); i++)
    {
            lista = insere(lista, texto[i]);
    }
    return lista;
}


int main()
{
    Arvore *arv;
    Lista *lista;
    lista = NULL;
    string texto = "teste banana";

    lista = frequencia(lista, texto);
    cout<<"hhhh\n";
    imprime(lista);
    lista = retiraLista(lista, 'a');
    cout<<"\n";
    imprime(lista);


    return 0;
}

