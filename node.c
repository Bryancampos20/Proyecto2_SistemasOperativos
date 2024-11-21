#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Inicializa una cola de procesos
void init_queue(ProcessQueue* queue) {
    queue->front = 0;
    queue->rear = 0;
    pthread_mutex_init(&queue->lock, NULL);
}

// Encola un proceso en la cola
int enqueue(ProcessQueue* queue, Process process) {
    pthread_mutex_lock(&queue->lock);
    if ((queue->rear + 1) % 100 == queue->front) {
        pthread_mutex_unlock(&queue->lock);
        return -1; // Cola llena
    }
    queue->processes[queue->rear] = process;
    queue->rear = (queue->rear + 1) % 100;
    pthread_mutex_unlock(&queue->lock);
    return 0;
}

// Desencola un proceso de la cola
int dequeue(ProcessQueue* queue, Process* process) {
    pthread_mutex_lock(&queue->lock);
    if (queue->front == queue->rear) {
        pthread_mutex_unlock(&queue->lock);
        return -1; // Cola vacía
    }
    *process = queue->processes[queue->front];
    queue->front = (queue->front + 1) % 100;
    pthread_mutex_unlock(&queue->lock);
    return 0;
}

// Encuentra el nodo con la menor carga
Node* find_least_loaded_node(Node nodes[], int num_nodes) {
    Node* least_loaded = &nodes[0];
    for (int i = 1; i < num_nodes; i++) {
        if (nodes[i].load < least_loaded->load) {
            least_loaded = &nodes[i];
        }
    }
    return least_loaded;
}

// Asigna un proceso al nodo
void assign_process_to_node(Node* node, Process process) {
    enqueue(&node->process_queue, process);
    node->load += process.execution_time; // Incrementa la carga del nodo
    printf("Proceso %d asignado al nodo %d con tiempo de ejecución %d.\n",
           process.id, node->id, process.execution_time);
}
