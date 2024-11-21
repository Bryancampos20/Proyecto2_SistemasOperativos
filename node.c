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

// Inicializa un recurso compartido
void init_resource(Resource* resource, int id) {
    resource->id = id;
    resource->in_use = 0;
    resource->owner_node_id = -1;
    pthread_mutex_init(&resource->lock, NULL);
}

// Solicita acceso a un recurso compartido
int request_resource(Resource* resource, int node_id) {
    pthread_mutex_lock(&resource->lock);
    if (resource->in_use) {
        pthread_mutex_unlock(&resource->lock);
        return -1; // Recurso no disponible
    }
    resource->in_use = 1;
    resource->owner_node_id = node_id;
    printf("Nodo %d adquirió el recurso %d.\n", node_id, resource->id);
    pthread_mutex_unlock(&resource->lock);
    return 0; // Recurso adquirido
}

// Libera un recurso compartido
void release_resource(Resource* resource, int node_id) {
    pthread_mutex_lock(&resource->lock);
    if (resource->owner_node_id == node_id) {
        resource->in_use = 0;
        resource->owner_node_id = -1;
        printf("Nodo %d liberó el recurso %d.\n", node_id, resource->id);
    }
    pthread_mutex_unlock(&resource->lock);
}

// Encuentra el nodo con la menor carga
Node* find_least_loaded_node(Node nodes[], int num_nodes) {
    Node* least_loaded = NULL;
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i].active && (!least_loaded || nodes[i].load < least_loaded->load)) {
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

// Maneja el fallo de un nodo
void handle_node_failure(Node nodes[], int num_nodes, int failed_node_id) {
    printf("Nodo %d ha fallado.\n", failed_node_id);
    Node* failed_node = NULL;

    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i].id == failed_node_id) {
            failed_node = &nodes[i];
            failed_node->active = 0;
            break;
        }
    }

    if (failed_node) {
        redistribute_processes(failed_node, nodes, num_nodes);
    }
}

// Redistribuye procesos de un nodo fallido
void redistribute_processes(Node* source_node, Node nodes[], int num_nodes) {
    Process process;
    while (dequeue(&source_node->process_queue, &process) == 0) {
        Node* target_node = find_least_loaded_node(nodes, num_nodes);
        if (target_node) {
            assign_process_to_node(target_node, process);
        } else {
            printf("No hay nodos disponibles para procesar el proceso %d.\n", process.id);
        }
    }
}
