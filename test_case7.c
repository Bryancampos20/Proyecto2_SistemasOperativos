#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Inicializar nodos iniciales
    Node nodes[3];
    for (int i = 0; i < 3; i++) {
        nodes[i].id = i + 1;
        nodes[i].load = (i + 1) * 10; // Cargas iniciales: Nodo 1 -> 10, Nodo 2 -> 20, Nodo 3 -> 30
        nodes[i].active = 1;
        init_queue(&nodes[i].process_queue);
    }

    // Mostrar estado inicial
    printf("Estado inicial de la red distribuida:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nodo %d: Carga = %d, Activo = %d\n", nodes[i].id, nodes[i].load, nodes[i].active);
    }

    // Agregar nuevos nodos dinámicamente
    printf("\nAgregando nuevos nodos a la red...\n");
    Node new_nodes[2];
    for (int i = 0; i < 2; i++) {
        new_nodes[i].id = 4 + i; // IDs de los nuevos nodos
        new_nodes[i].load = 0;   // Nuevos nodos comienzan sin carga
        new_nodes[i].active = 1;
        init_queue(&new_nodes[i].process_queue);

        printf("Nuevo Nodo %d agregado.\n", new_nodes[i].id);
    }

    // Redistribuir carga entre todos los nodos
    Process process1 = {1, 5};
    Process process2 = {2, 10};
    Process process3 = {3, 7};

    assign_process_to_node(find_least_loaded_node(new_nodes, 2), process1);
    assign_process_to_node(find_least_loaded_node(nodes, 3), process2);
    assign_process_to_node(find_least_loaded_node(nodes, 3), process3);

    // Mostrar estado final
    printf("\nEstado final de la red distribuida tras agregar nodos y redistribuir carga:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nodo %d: Carga = %d, Activo = %d\n", nodes[i].id, nodes[i].load, nodes[i].active);
    }
    for (int i = 0; i < 2; i++) {
        printf("Nodo %d: Carga = %d, Activo = %d\n", new_nodes[i].id, new_nodes[i].load, new_nodes[i].active);
    }

    return 0;
}
