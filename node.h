#ifndef NODE_H
#define NODE_H

#include <pthread.h> // Para los hilos

// Estructura para representar un proceso
typedef struct {
    int id;                  // ID único del proceso
    int execution_time;      // Tiempo simulado de ejecución en segundos
} Process;

// Estructura para manejar la cola de procesos
typedef struct {
    Process processes[100];  // Cola de procesos
    int front;               // Índice del inicio de la cola
    int rear;                // Índice del final de la cola
    pthread_mutex_t lock;    // Lock para acceso seguro a la cola
} ProcessQueue;

// Estructura para un nodo
typedef struct {
    int id;                  // ID del nodo
    int load;                // Carga actual del nodo
    ProcessQueue process_queue; // Cola de procesos del nodo
} Node;

// Funciones para manejar la cola de procesos
void init_queue(ProcessQueue* queue);
int enqueue(ProcessQueue* queue, Process process);
int dequeue(ProcessQueue* queue, Process* process);

// Funciones de asignación y carga
Node* find_least_loaded_node(Node nodes[], int num_nodes);
void assign_process_to_node(Node* node, Process process);

#endif // NODE_H
