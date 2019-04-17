#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODOS 20 // Numero max de nodos

typedef struct Nodo{
    char id;
    int indice;     //usado para matriz
    int qntdVizinhos;
    bool visit;
    int distancia;   //etiqueta 1
    Nodo* adj;       //etiqueta 2 nodo adjacente 
    struct Aresta* vizinhos[];
}*Nodo;

typedef struct Aresta{
    int peso;
    Nodo vizinho;
}*Aresta;

int matrizAdj[MAX_NODOS][MAX_NODOS];
int qntdNos = 0;
Nodo vetorNodos[MAX_NODOS];

Nodo criaNodo(char id){
    matrizAdj[qntdNos][qntdNos] = 0; // idxid = 0 

    Nodo novo = (Nodo) malloc(sizeof(Nodo));
    novo->distancia = MAX_NODOS;    //etiqueta 1
    novo->adj = NULL;               //etiqueta 2
    novo->id = id;
    novo->visit = false;
    novo->qntdVizinhos = 0;
    novo->indice = qntdNos;

    vetorNodos[qntdNos] = novo;     //salva novo nodo no vetor dos nodos
    qntdNos++;
return novo;
}

void ligaNodos(char id1, char id2, int peso){

    Nodo aux1 = (Nodo) malloc(sizeof(Nodo));
    Nodo aux2 = (Nodo) malloc(sizeof(Nodo));

    aux1 = buscaNodos(id1);
    aux2 = buscaNodos(id2);

    if((aux1 != NULL) && (aux2 != NULL)){
        matrizAdj[aux1->indice][aux2->indice] = peso;
        aux1->vizinhos[aux1->qntdVizinhos]->vizinho = aux2;
        aux1->vizinhos[aux1->qntdVizinhos]->peso = peso;
        aux1->qntdVizinhos++;
    }

}

Nodo buscaNodos(char id){
    Nodo n = (Nodo) malloc(sizeof(Nodo));

    for(int i=0; i<qntdNos; i++){
        if(vetorNodos[i]->id == id){
            n = vetorNodos[i];
            return n;
        }
    }
    printf("Nao existe o nodo\n");
    free(n);
    return NULL; 
}

void calculaMenorCaminho(Nodo o, Nodo d){

    if(o->qntdVizinhos == 0){
        printf("O vertice origem nao possui vizinhos\n");
        return;
    }

    Nodo aux1 = (Nodo) malloc(sizeof(Nodo));
    Nodo aux2 = (Nodo) malloc(sizeof(Nodo));

    aux1 = buscaNodos(o->id);
    aux2 = buscaNodos(d->id);

    if((aux1 == NULL) || (aux2 == NULL)){
        printf("Nodo nao existen te\n");
        return;
    }

    o->visit = true;
    o->adj = o;
    o->distancia = 0;

    //etiqueta para os vizinhos do nodo origem
    for(int i=0; i<(o->qntdVizinhos); i++){
        o->vizinhos[i]->vizinho->distancia = o->vizinhos[i]->peso;  //et 1
        o->vizinhos[i]->vizinho->adj = o;                           //et 2
        o->vizinhos[i]->vizinho->visit = true;
    }    

    do{
        

    }while(d->visit==false);
    
    

}

void buscaRecursiva(Nodo n, Nodo final){
    for(int i=0; i<n->qntdVizinhos;i++){
        n->vizinhos[i]->vizinho->visit = true;    
        if(n->vizinhos[i]->vizinho->distancia > (n->distancia + n->vizinhos[i]->peso)){
            n->vizinhos[i]->vizinho->distancia = (n->distancia + n->vizinhos[i]->peso);
            n->vizinhos[i]->vizinho->adj = n;
        }
    
    buscaRecursiva(n->vizinhos[i]->vizinho, final);
    }
}

//mostrar resultado a partir do vetor de nodos