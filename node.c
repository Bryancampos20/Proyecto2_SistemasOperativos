#include "node.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 5000 // Cambiado a partir de 5000 para evitar conflictos

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

void* process_executor(void* args) {
    Node* node = (Node*)args;
    ProcessQueue* queue = &node->process_queue;
    Process process;

    while (1) {
        if (dequeue(queue, &process) == 0) {
            printf("Nodo %d ejecutando proceso %d por %d segundos.\n", 
                   node->id, process.id, process.execution_time);
            sleep(process.execution_time); // Simula la ejecución del proceso
            printf("Nodo %d completó el proceso %d.\n", node->id, process.id);
        } else {
            sleep(1); // Espera si no hay procesos
        }
    }
    return NULL;
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
    init_queue(&node.process_queue); // Inicializa la cola de procesos

    printf("Nodo %d activo en el puerto %d.\n", node.id, PORT + node.id);

    pthread_t executor_thread, connection_thread;
    pthread_create(&executor_thread, NULL, process_executor, &node);
    pthread_create(&connection_thread, NULL, handle_connections, &node);

    pthread_join(executor_thread, NULL);
    pthread_join(connection_thread, NULL);
    close(node.socket_fd);
    return 0;
}
