#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_NODES 3

// Simula solicitudes de nodos a un recurso compartido
void* simulate_request(void* args) {
    Resource* resource = (Resource*)args;
    int node_id = rand() % NUM_NODES + 1;

    // Intentar adquirir el recurso
    while (request_resource(resource, node_id) != 0) {
        sleep(1); // Espera antes de reintentar
    }

    // Usar el recurso
    sleep(2); // Simula el uso del recurso
    release_resource(resource, node_id); // Libera el recurso

    return NULL;
}

int main() {
    // Inicializar recurso compartido
    Resource resource;
    init_resource(&resource, 1);

    // Crear hilos para simular nodos
    pthread_t threads[NUM_NODES];
    for (int i = 0; i < NUM_NODES; i++) {
        pthread_create(&threads[i], NULL, simulate_request, &resource);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_NODES; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
