#include "network.h"
#include <stdio.h>

// Simula la comunicación entre nodos
void simulate_communication(Node nodes[], int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        printf("Nodo %d tiene carga %d.\n", nodes[i].id, nodes[i].load);
    }
}
