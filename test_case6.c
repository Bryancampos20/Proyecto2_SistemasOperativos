#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Inicializar nodos
    Node nodes[3];
    for (int i = 0; i < 3; i++) {
        nodes[i].id = i + 1;
        nodes[i].load = 0;
        nodes[i].active = 1; // Todos los nodos están activos inicialmente
        init_queue(&nodes[i].process_queue);
    }

    // Asignar procesos al nodo 2
    Process process1 = {1, 5};
    Process process2 = {2, 3};
    Process process3 = {3, 7};
    assign_process_to_node(&nodes[1], process1); // Nodo 2
    assign_process_to_node(&nodes[1], process2); // Nodo 2
    assign_process_to_node(&nodes[1], process3); // Nodo 2

    // Mostrar estado inicial
    printf("Estado inicial de los nodos:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nodo %d: Carga = %d, Activo = %d\n", nodes[i].id, nodes[i].load, nodes[i].active);
    }

    // Simular fallo del nodo 2
    printf("\nSimulando fallo del Nodo 2...\n");
    handle_node_failure(nodes, 3, 2);

    // Mostrar estado final
    printf("\nEstado final de los nodos tras redistribución:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nodo %d: Carga = %d, Activo = %d\n", nodes[i].id, nodes[i].load, nodes[i].active);
    }

    return 0;
}
