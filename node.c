#include "node.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 5000 // Puerto base
#define MAX_RESOURCES 5

void init_queue(ProcessQueue* queue) {
    queue->front = 0;
    queue->rear = 0;
    pthread_mutex_init(&queue->lock, NULL);
}

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

void init_resource(Resource* resource, int id) {
    resource->id = id;
    resource->in_use = 0;
    resource->owner_node_id = -1;
    pthread_mutex_init(&resource->lock, NULL);
}

int request_resource(Resource* resource, int node_id) {
    pthread_mutex_lock(&resource->lock);
    if (resource->in_use == 0) {
        resource->in_use = 1;
        resource->owner_node_id = node_id;
        pthread_mutex_unlock(&resource->lock);
        printf("Recurso %d asignado al nodo %d.\n", resource->id, node_id);
        return 0; // Recurso asignado
    }
    pthread_mutex_unlock(&resource->lock);
    printf("Recurso %d no disponible para el nodo %d.\n", resource->id, node_id);
    return -1; // Recurso ocupado
}

void release_resource(Resource* resource, int node_id) {
    pthread_mutex_lock(&resource->lock);
    if (resource->in_use == 1 && resource->owner_node_id == node_id) {
        resource->in_use = 0;
        resource->owner_node_id = -1;
        printf("Recurso %d liberado por el nodo %d.\n", resource->id, node_id);
    } else {
        printf("Nodo %d no posee el recurso %d.\n", node_id, resource->id);
    }
    pthread_mutex_unlock(&resource->lock);
}

void* process_executor(void* args) {
    Node* node = (Node*)args;
    ProcessQueue* queue = &node->process_queue;
    Process process;

    while (1) {
        if (dequeue(queue, &process) == 0) {
            printf("Nodo %d ejecutando proceso %d por %d segundos.\n",
                   node->id, process.id, process.execution_time);
            sleep(process.execution_time); // Simula ejecución
            printf("Nodo %d completó el proceso %d.\n", node->id, process.id);
        } else {
            sleep(1); // Espera si no hay procesos
        }
    }
    return NULL;
}

void init_resources(Resource* resources, int num_resources) {
    for (int i = 0; i < num_resources; i++) {
        init_resource(&resources[i], i);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ID del Nodo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Node node;
    node.id = atoi(argv[1]);
    node.socket_fd = init_server_socket(PORT + node.id);
    if (node.socket_fd == -1) {
        fprintf(stderr, "No se pudo iniciar el nodo\n");
        exit(EXIT_FAILURE);
    }
    init_queue(&node.process_queue);

    // Inicializa recursos compartidos
    node.num_resources = MAX_RESOURCES;
    node.resources = malloc(sizeof(Resource) * MAX_RESOURCES);
    init_resources(node.resources, MAX_RESOURCES);

    printf("Nodo %d activo en el puerto %d.\n", node.id, PORT + node.id);

    pthread_t executor_thread, connection_thread;
    pthread_create(&executor_thread, NULL, process_executor, &node);
    pthread_create(&connection_thread, NULL, handle_connections, &node);

    pthread_join(executor_thread, NULL);
    pthread_join(connection_thread, NULL);
    close(node.socket_fd);
    free(node.resources);
    return 0;
}
