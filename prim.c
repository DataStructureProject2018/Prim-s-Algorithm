#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 999999
#define false 0
#define true 1

// Grafo
typedef struct adj_list {
    int vertex;
    int weight;
    struct adj_list *next;
} adj_list;

typedef struct list {
    adj_list *head;
} list;

typedef struct graph {
    list *vertex;
    short *visited;
} graph;

// Fila de prioridades
typedef struct node {
    int vertex;
    int weight;
    struct node *next;
} node;

typedef struct priority_queue{
    node *head;
} priority_queue;


graph* create_graph(int size) {

    graph *new_graph = (graph*) malloc(sizeof(graph));
    new_graph->vertex = (list*) malloc(sizeof(list) * size);
    new_graph->visited = (short*) malloc(sizeof(short) * size);

    int i;
    for (i = 0; i < size; i++) {
        new_graph->vertex[i].head = NULL;
        new_graph->visited[i] = 0;
    }

    return new_graph;
}

adj_list* create_adj_list(int vertex, int weight) {

    adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
    new_adj_list->vertex = vertex;
    new_adj_list->weight = weight;
    new_adj_list->next = NULL;

    return new_adj_list;
}

void add_vertex(graph *g, int origem, int destino, int weight) {

    adj_list *new_node = create_adj_list(destino, weight);
    new_node->next = g->vertex[origem].head;
    g->vertex[origem].head = new_node;

    new_node = create_adj_list(origem, weight);
    new_node->next = g->vertex[destino].head;
    g->vertex[destino].head = new_node;

}

priority_queue* create_queue(){

    priority_queue *new_queue = (priority_queue*) malloc(sizeof(priority_queue));
    new_queue->head = NULL;

    return new_queue;

}

void enqueue(priority_queue *q, int vertex, int weight) {
    node *new_node = (node*) malloc(sizeof(node));
    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = NULL;

    if(q->head == NULL) {
        q->head = new_node;
    }
    else
    {
        node *current = q->head, *prev = NULL;
        if(q->head->weight > weight) {
            new_node->next = q->head;
            q->head = new_node;
        } else {
            while(current->next && current->next->weight < weight) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
    }

}

node* dequeue(priority_queue *queue) {

    if(queue->head){

        node *aux = NULL;
        aux = queue->head;
        queue->head = queue->head->next;

        return aux;
    }

}

int primMST(graph *graph, int V){

    int parent[V];     // Array para guardar a MST
    int key[V];     // Valores chaves para usar as arestas de menor peso
    int i, count, cost = 0;
    for (i = 0; i < V; i++){
            key[i] = INT_MAX;
    }
    key[0] = 0;    // Faz o vértice 0 ser o primeiro escolhido
    parent[0] = 0; // Faz o vértice 0 estar sempre ligado com ele mesmo
    
    priority_queue *queue = create_queue();
    enqueue(queue, 0, 0);

    while (queue->head){
            node *u = dequeue(queue);
            adj_list *current = graph->vertex[u->vertex].head;
        
            if (graph->visited[u->vertex] == false){
                while(current){
                    if(graph->visited[current->vertex] == false && current->weight < key[current->vertex]){
                        parent[current->vertex] = u->vertex;
                        key[current->vertex] = current->weight;
                    }
                    enqueue(queue, current->vertex, current->weight);
                    current = current->next;
                }
                graph->visited[u->vertex] = true;  // Marca o vértice como visitado
                cost += u->weight;
            }
    }

    return cost;
}

void printGraph(graph *g) {
    
    int i;
    for(i=0;i<5;i++) {
        adj_list *current = g->vertex[i].head;
        printf("\n%d: ", i);
        while(current) {
            printf("%d->", current->vertex);
            current = current->next;
        }
        printf("NULL\n");
    }
    
}

int main(){

    graph *graph = create_graph(5);
    
    add_vertex(graph, 0, 1, 15);
    add_vertex(graph, 0, 2, 10);
    add_vertex(graph, 1, 2, 1);
    add_vertex(graph, 2, 3, 3);
    add_vertex(graph, 1, 3, 5);
    add_vertex(graph, 3, 4, 20);

    //printGraph(graph);
    printf("Custo MST: %d\n", primMST(graph, 4));

    return 0;
}   