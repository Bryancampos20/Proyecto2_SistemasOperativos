#include "node.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Inicializar nodos
    Node nodes[3];
    for (int i = 0; i < 3; i++) {
        nodes[i].id = i + 1;
        nodes[i].load = 0;
        init_queue(&nodes[i].process_queue);
    }

    // Simular procesos
    Process process1 = {1, 5};
    Process process2 = {2, 3};
    Process process3 = {3, 7};

    // Asignar procesos a los nodos
    assign_process_to_node(find_least_loaded_node(nodes, 3), process1);
    assign_process_to_node(find_least_loaded_node(nodes, 3), process2);
    assign_process_to_node(find_least_loaded_node(nodes, 3), process3);

    // Simular comunicación entre nodos
    simulate_communication(nodes, 3);

    return 0;
}
