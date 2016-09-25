#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

typedef struct sArvore
{
    char elemento[5];
    struct sArvore *esquerda;
    struct sArvore *direita;
} Arvore;

typedef struct lista
{
    int freq;
    char elem;
    Arvore *raiz;
    struct lista *prox;
} Lista;

typedef struct cod
{
    char elem[5];
    char codigo[10];
    struct cod *prox;
}LCodigo;

void imprimeA(Arvore *arv, int nivel)
{
    Arvore *aux = arv;
    if(arv != NULL)
    {
        imprimeA(aux->direita, nivel+1);
        for(int i = 0; i < nivel; i++)
            printf("      ");
        printf("%6s\n\n", arv->elemento);
        imprimeA(aux->esquerda, nivel+1);
    }
}

Arvore* insereA(Arvore *arv, char elem[], int lado)
{
    if(arv == NULL)
    {
        arv = (Arvore*) malloc(sizeof(Arvore));
        arv->esquerda = NULL;
        arv->direita = NULL;
        strcpy(arv->elemento, elem);
    }
    else if(arv->direita == NULL)
        arv->direita = insereA(arv->direita, elem, lado);
    else if(arv->esquerda == NULL)
        arv->esquerda = insereA(arv->esquerda, elem, lado);
    else if(lado == 1)
    {
        Arvore *aux;
        aux = (Arvore*) malloc(sizeof(Arvore));
        strcpy(aux->elemento, elem);
        aux->esquerda = NULL;
        aux->direita = arv;
        arv = aux;
    }
    else
    {
        Arvore *aux;
        aux = (Arvore*) malloc(sizeof(Arvore));
        strcpy(aux->elemento, elem);
        aux->esquerda = arv;
        aux->direita = NULL;
        arv = aux;
    }
    return arv;
}

void mostraLCodigo(LCodigo *lCod)
{
    LCodigo *p;
    p = lCod;
    while(p != NULL)
    {
		cout<<"Elem: "<<p->elem<<"  Cod: "<<p->codigo<<endl;
        p = p->prox;
    }
}

LCodigo* insereLCodigo(LCodigo *lCod, char elem[], char cod[])
{
    LCodigo *aux;
    aux = (LCodigo*) malloc(sizeof(LCodigo));
    if(aux != NULL)
    {
        strcpy(aux->elem, elem);
        strcpy(aux->codigo, cod);
        aux->prox = lCod;
        lCod = aux;
    }
    else
        cout<<"Sem Memoria"<<endl;
    return lCod;
}


LCodigo* geraCodigoArvore(Arvore *arv, LCodigo *lCod, char cod[])
{
    Arvore *aux;
    aux = arv;
    char c[10] = "";
    if(aux != NULL)
    {
        if(aux->esquerda == NULL && aux->direita == NULL)
        {
            lCod = insereLCodigo(lCod, aux->elemento, cod);
        }
        if(aux->esquerda != NULL)
        {
            strcpy(c, cod);
            strcat(cod, "0");
            lCod = geraCodigoArvore(aux->esquerda, lCod, cod);
        }
        strcpy(cod, c);
        if(aux->direita != NULL)
        {
            strcat(cod, "1");
            lCod = geraCodigoArvore(aux->direita, lCod, cod);
        }
    }
    return lCod;
}


Arvore* juntarArvore(Arvore *a1, Arvore *a2)
{
    a1->direita = a2;
    return a1;
}

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

Lista* insereLista(Lista *lista, char elem, int freq, Arvore *arv)
{
    Lista *novo, *nodo;
    novo = (Lista*)malloc(sizeof(Lista));

    if(elem != NULL && existeElemento(lista, elem))
    {
        nodo = buscaElemento(lista, elem);
        nodo->freq += 1;
        return ordenarLista(lista);
    }

    novo->elem = elem;
    novo->raiz = arv;
    novo->freq = freq;
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
    Lista *elim, *ant, *ptr;

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
        lista = insereLista(lista, texto[i], 1, NULL);
    }
    return lista;
}

Arvore* montarArvoreTexto(Lista *lista)
{
    Arvore *arv = NULL;
    Lista *aux = lista;
    if(aux->prox != NULL)
    {
        int soma;
        char res[5];
        soma = aux->freq + aux->prox->freq;
        itoa(soma, res, 10);
        if(aux->raiz != NULL || aux->prox->raiz != NULL)
        {
            if(aux->elem == NULL && aux->prox->elem == NULL)
            {
                arv = insereA(aux->raiz, res, 0);
                arv = juntarArvore(arv, aux->prox->raiz);
            }
            else if(aux->elem != NULL)
            {
                arv = insereA(aux->prox->raiz, res, 0);
                char el[2];
                el[0] = aux->elem;
                el[1] = '\0';
                arv = insereA(arv, el, 0);
            }
            else
            {
                arv = insereA(aux->raiz, res, 1);
                char el[2];
                el[0] = aux->prox->elem;
                el[1] = '\0';
                arv = insereA(arv, el, 0);
            }
        }
        else
        {
            arv = insereA(arv, res, 1);
            char el[2];
            el[0] = aux->elem;
            el[1] = '\0';
            arv = insereA(arv, el, 1);
            el[0] = aux->prox->elem;
            el[1] = '\0';
            arv = insereA(arv, el, 1);
        }

        lista = retiraLista(lista, aux->elem);///////
        lista = retiraLista(lista, aux->prox->elem);
        lista = insereLista(lista, NULL, soma, arv);

        //cout<<"\n\n";
        //imprime(lista);

        return montarArvoreTexto(lista);
    }
    return lista->raiz;
}


char* pesquisaElemCodigo(LCodigo *lCod, char ch)
{
    LCodigo *lC;
    lC = lCod;
    char elem[2];
    elem[0] = ch;
    elem[1] = '\0';
    while(lC != NULL && strcmp(lC->elem, elem) != 0)
    {
        lC = lC->prox;
    }
    if(strcmp(lC->elem, elem) == 0)
    {
        char *ret;
        ret = lC->codigo;
        return ret;
    }
    return NULL;
}

void percorreParaComprimir(string texto, LCodigo *lCod)
{
    char ch, palavra;
    char *cod;
    int deslocamento;
    palavra = 0x00;
    deslocamento = 0;
    int v[8];
    for (int i = 0; i < texto.length(); i++)
    {
        ch = texto[i];

        cod = pesquisaElemCodigo(lCod, ch);

        if(cod != NULL)
        {
            for(int i = 0; cod[i] != '\0'; i++)
            {
                if(deslocamento < 8)
                {
                    palavra <<= 1;
                    if(cod[i] == '1')
						palavra += 1;

                    deslocamento++;
                }
                else
                {
                    cout<<palavra;
                    deslocamento = 0;
                    palavra = 0x00;

                    palavra <<= 1;
                    if(cod[i] == '1')
                        palavra += 1;
                    deslocamento++;
                }
            }
        }
    }
    if(deslocamento < 8)
    {
        while(deslocamento < 8)
        {
            palavra <<= 1;
            deslocamento++;
        }
        cout<<palavra;
    }
}


int main()
{
    Arvore *arv = NULL;
    Lista *lista;
    LCodigo *lCod = NULL;
    lista = NULL;
    string texto = "teste banana";
	
	
    lista = frequencia(lista, texto);
    cout<<"hhhh\n";
    imprime(lista);

    arv = montarArvoreTexto(lista);
    cout<<"-0000\n";
    imprimeA(arv, 0);

    cout<<"\n----------------\n";
    char cod[10] = "";
    lCod = geraCodigoArvore(arv, lCod, cod);
    mostraLCodigo(lCod);

    cout<<"\nTexto Comprimido"<<endl;
    percorreParaComprimir(texto, lCod);
    cout<<endl;


    return 0;
}
