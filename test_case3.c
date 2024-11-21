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

    // Simular procesos
    Process process1 = {1, 5};
    Process process2 = {2, 3};
    Process process3 = {3, 7};

    // Asignar procesos a los nodos
    assign_process_to_node(&nodes[0], process1);
    assign_process_to_node(&nodes[1], process2);
    assign_process_to_node(&nodes[2], process3);

    // Simular fallo del nodo 2
    handle_node_failure(nodes, 3, 2);

    return 0;
}
