// Grafos por Lista de Adjac�ncia.

#include<stdio.h>  // printf();
#include<conio.h>  // getch();
#include<stdlib.h> // malloc();

struct adjacente {
    struct adjacente *prox;
    int a;
}; // Lista de adjacentes.

struct vertice {
    struct vertice *prox_v;
    int v;
    struct adjacente *prox_a;
}; // Lista de v�rtices.

struct vertice *grafo;

// Aloca um nodo do tipo v�rtice.
struct vertice * aloca_vertice(int v) {
    struct vertice * novo;

    novo = (struct vertice *) malloc(sizeof(struct vertice));

    // Atribui o v�rtice origem para "v".
    novo->v = v;
    novo->prox_v = NULL;
    novo->prox_a = NULL;

    return novo;
}

// Aloca um nodo do tipo adjacente.
struct adjacente * aloca_adjacente(int a) {
    struct adjacente *novo;

    novo = (struct adjacente *) malloc(sizeof(struct adjacente));

    // Atribui o v�rtice adjacente para "a".
    novo->a = a;
    novo->prox = NULL;

    return novo;
}

void conecta(struct vertice **grafo, int v1, int v2) {
    struct vertice *aux, *novo_v, *ant;

    struct adjacente *aux_a, *novo_a, *ant_a;
    
    if (*grafo == NULL) {
        // Se grafo esta vazio.
        
        // Cria um nodo do tipo v�rtice e atribui o endere�o do nodo criado para o grafo.
        *grafo = aloca_vertice(v1);
        
        // Cria um nodo do tipo adjacente e atribui o endere�o do nodo criado para "novo_a".
        novo_a = aloca_adjacente(v2);
    
        // Conecta o nodo adjacente ao nodo v�rtice.
        (*grafo)->prox_a = novo_a;
    } else {
        aux = *grafo;

        // Pesquisa na lista de v�rtices at� encontrar o v�rtice "v1".
        while (aux && (aux->v != v1)) {
            ant = aux;
            aux = aux->prox_v;
        }

        if (aux == NULL) {
            // Se n�o encontrou o v�rtice na lista de v�rtices.

            novo_v = aloca_vertice(v1); // Aloca v�rtice.
            novo_a = aloca_adjacente(v2); // Aloca adjacente.

            // Conecta o v�rtice criado ao final da lista de v�rtices.            
            ant->prox_v = novo_v;

            // Conecta o v�rtice adjacente ao v�rtice v1.
            novo_v->prox_a = novo_a;
        } else {
            // Se encontrou o v�rtice na lista de v�rtices.

            if (aux->prox_a == NULL) {
                // Se o v�rtice n�o possui nenhum adjacente.

                novo_a = aloca_adjacente(v2); // Aloca adjacente.

                // Conecta o nodo criado ao v�rtice v1.
                aux->prox_a = novo_a;
            } else {
                // Se o v�rtice j� possui algum adjacente.
                
                aux_a = aux->prox_a;
                
                // Verifica se v2 j� existe na lista de adjacentes de v1.
                while (aux_a && (aux_a->a != v2)) {
                    ant_a = aux_a;
                    aux_a = aux_a->prox;
                }
                // Se v2 n�o aparece na lista de adjacentes de v1.
                if (aux_a == NULL) {
                    novo_a = aloca_adjacente(v2); // Aloca nodo adjacente.

                    // "ant_a" aponta para o �ltimo nodo da lista de adjacentes.
                    // Conecta o nodo adjacente no final da lista de adjacentes de v1.                  
                    ant_a->prox = novo_a;
                }
            }
        }
    }
}

void desconecta(struct vertice *grafo, int v1, int v2) {
    struct vertice *aux;
    struct adjacente *aux_a, *ant_a;

    if (grafo != NULL) {
        // Se o grafo n�o estiver vazio. 
        aux = grafo;
        while ((aux != NULL) && (aux->v != v1)) {
            // Procura v1 na lista de v�rtices.
            aux = aux->prox_v; // "aux" aponta para o pr�ximo nodo na lista de v�rtices.
        }
        if (aux != NULL) {
            // Se encontro v1 na lista de v�rtices.
            aux_a = aux->prox_a;
            while (aux_a && (aux_a->a != v2)) {
                ant_a = aux_a;
                aux_a = aux_a->prox;
                // "aux_a" aponta para o pr�ximo nodo na lista de adjacentes.
            }
            if (aux_a != NULL) {
                // Se encontrou v2 na lista de adjacentes.
                if (aux->prox_a == aux_a) {
                    // Se v2 � o primeiro elemento da lista de adjacentes.
                    aux->prox_a = aux_a->prox;
                    // Atualiza o campo prox_a para o endere�o do pr�ximo nodo da lista de adjacentes.
                } else {
                    ant_a->prox = aux_a->prox;
                    // O campo prox do nodo anterior a v2 aponta para o pr�ximo nodo.
                }
                free(aux_a);
            }
        }
    }
}
