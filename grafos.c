#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODOS 20      //Numero max de nodos(vertices)

int matrizAdj[MAX_NODOS][MAX_NODOS];    //Matriz de Adjacencia
int qntdNos = 0;                       //Numero total de nodos

typedef struct No{
    char id;
    int indice;
    int qntdVizinhos;
    bool visited;
    int distancia;
    int paiAnt;
    char pai;
    struct Aresta* vizinhos[];
}*nodo;

typedef struct Aresta{
    int peso;
    nodo vizinho;
}*aresta;

//VETOR COM TODOS NODOS
nodo vetNodos[MAX_NODOS];    

//GLOBAL VARIABLES
int p, visitados, primeiro, menor;
char id, id1,id2;

// FUNCTIONS
int menu(int opt);
void option(int opt);
nodo buscaNodos(char id);
void criaNodo(char id);
void ligaNodos(nodo id1, nodo id2, int pesoAresta);
void imprimeMatriz();
void dijkstra(char id);
int procuraMenorDistancia();


int main(){
    int opt;
    do{
        opt = menu(opt);
        option(opt);
    }while(opt != 0);

    return 0;
}
int menu(int opt){

	 printf("\n--Escolha a opcao--\n");
	 printf("0. Sair\n");
	 printf("1. Adicionar Nodo\n");
	 printf("2 - Ligar Nodos\n");
     printf("3 - Dijkstra\n");

	 printf("Opcao: "); scanf("%d", &opt);

 return opt;
}

void option(int opt){
    switch (opt){
        case 1:{
            printf("Identificador do nodo:\n");
            scanf(" %c", &id);
            if(buscaNodos(id) == NULL){
                criaNodo(id);
            }else{
                printf("ID Nodo ja existente\n");
            }

            break;
        }

        case 2:{
            nodo aux1 = malloc(sizeof(nodo));
            nodo aux2 = malloc(sizeof(nodo));
            printf("Nodos a serem ligados e seu peso: \n");
            scanf(" %c %c %d", &id1, &id2, &p);
            aux1 = buscaNodos(id1);
            aux2 = buscaNodos(id2);
                if (aux1  == NULL || aux2 == NULL) {
                    printf("Não existe este Nodo\n");
                    break;
                }else{
                    ligaNodos(aux1, aux2, p);
                } 
            break;
        }

        case 3:{
            printf("Nodo Inicial:\n");
            scanf(" %c", &id);

            dijkstra(id);
        }
        default:{
            printf("Invalid option\n");
            break;
        }
    }
}
    nodo buscaNodos(char id){
        for(int i =0; i<qntdNos; i++){
            if(id == vetNodos[i]->id){
                return vetNodos[i];
            }
        }
        return NULL;
    }

    void criaNodo(char id){
        matrizAdj[qntdNos][qntdNos] = 0;
        vetNodos[qntdNos]->id = id;
        vetNodos[qntdNos]->indice = qntdNos;
        vetNodos[qntdNos]->qntdVizinhos = 0;
        vetNodos[qntdNos]->visited = false;
        vetNodos[qntdNos]->paiAnt = -1;
        qntdNos++;
    }

    void ligaNodos(nodo id1, nodo id2, int pesoAresta){
        matrizAdj[id1->indice][id2->indice] = pesoAresta;
        
        id1->vizinhos[id1->qntdVizinhos]->vizinho = id2;
        id1->vizinhos[id1->qntdVizinhos]->peso = pesoAresta;
        id1->qntdVizinhos++;
    }

    ///////////////////////////////////////////////
    void dijkstra(char id){
       if(buscaNodos(id) == NULL){
           printf("Nodo inexistente\n");
           return ;
       }
        
        visitados = qntdNos;
        nodo aux = malloc(sizeof(nodo));

        //inicializar nodos
       for(int i = 0; i<qntdNos; i++){
           //para nodo origem
           if(vetNodos[i]->id == id){
               vetNodos[i]->distancia = 0;
               vetNodos[i]->paiAnt = i;
               vetNodos[i]->pai = vetNodos[i]->id;
               vetNodos[i]->visited = false;
           //outros nodos    
           }else{
               vetNodos[i]->distancia = INT_MAX;
               vetNodos[i]->paiAnt = INT_MAX;
               vetNodos[i]->visited = false;
           }
       } 

       while(visitados > 0){

        p = procuraMenorDistancia(); 
            if(p == INT_MAX){
                printf("Grafo Desconexo\n");
                break;
            }
        //seta noodo como visitado 
        vetNodos[p]->visited = true; 
        visitados--;
        //vai em todos vizinhos do nodo
        for(int i=0; i < (vetNodos[p]->qntdVizinhos); i++){
            aux = vetNodos[p]->vizinhos[i]->vizinho;

            if(aux->distancia = INT_MAX){
              aux->distancia = (vetNodos[p]->vizinhos[i]->peso) + (vetNodos[p]->distancia); 
              aux->pai = vetNodos[p]->id;
              aux->paiAnt = p;

            }else{
                if(aux->distancia > ((vetNodos[p]->vizinhos[i]->peso) + (vetNodos[p]->distancia))){
                    aux->distancia = ((vetNodos[p]->vizinhos[i]->peso) + (vetNodos[p]->distancia));
                    aux->pai = vetNodos[p]->id;
                    aux->paiAnt = p;
                }
            }
        }
       }     
        printf("Menor caminho partindo de %c : \n" , id);
            for(int i=0; i<qntdNos; i++){
                printf("Nodo %c, (%c,%d)\n", vetNodos[i]->id, vetNodos[i]->pai, vetNodos[i]->distancia);
            }
            
        free(aux);    
    } 
    //Procura vertice com menor distancia e que nao tenha sido visitado
    int procuraMenorDistancia(){
        menor = INT_MAX; 
        primeiro = 1;

        for(int i=0; i<qntdNos; i++){
             if((vetNodos[i]->distancia != INT_MAX) && (vetNodos[i]->visited == false)){
                 if(primeiro){
                     menor = i;
                     primeiro = 0;
                 }else{
                     if(vetNodos[menor]->distancia > vetNodos[i]->distancia){
                         menor = i;
                     }
                 }  
             }
        }
        return menor;
}