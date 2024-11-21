#ifndef NODE_H
#define NODE_H

#include <pthread.h>

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

// Estructura para un recurso compartido
typedef struct {
    int id;                  // ID único del recurso
    int in_use;              // 0: Libre, 1: En uso
    int owner_node_id;       // Nodo que posee el recurso
    pthread_mutex_t lock;    // Lock para sincronización
} Resource;

// Estructura para un nodo
typedef struct {
    int id;                  // ID del nodo
    int load;                // Carga actual del nodo
    int active;              // 1: Activo, 0: Inactivo
    ProcessQueue process_queue; // Cola de procesos del nodo
} Node;

// Funciones para manejar la cola de procesos
void init_queue(ProcessQueue* queue);
int enqueue(ProcessQueue* queue, Process process);
int dequeue(ProcessQueue* queue, Process* process);

// Funciones de asignación y carga
Node* find_least_loaded_node(Node nodes[], int num_nodes);
void assign_process_to_node(Node* node, Process process);

// Funciones para manejo de recursos compartidos
void init_resource(Resource* resource, int id);
int request_resource(Resource* resource, int node_id);
void release_resource(Resource* resource, int node_id);

// Funciones para manejo de fallos
void handle_node_failure(Node nodes[], int num_nodes, int failed_node_id);
void redistribute_processes(Node* source_node, Node nodes[], int num_nodes);

#endif // NODE_H
