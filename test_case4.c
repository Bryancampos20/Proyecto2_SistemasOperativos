#include "node.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Inicializar nodos con cargas variables
    Node nodes[3];
    for (int i = 0; i < 3; i++) {
        nodes[i].id = i + 1;
        nodes[i].load = (i + 1) * 10; // Cargas iniciales: Nodo 1 -> 10, Nodo 2 -> 20, Nodo 3 -> 30
        nodes[i].active = 1;
        init_queue(&nodes[i].process_queue);
    }

    // Mostrar cargas iniciales
    printf("Cargas iniciales:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nodo %d: Carga = %d\n", nodes[i].id, nodes[i].load);
    }

    // Crear un nuevo proceso
    Process new_process = {4, 5}; // ID = 4, tiempo de ejecución = 5

    // Asignar proceso al nodo menos cargado
    Node* least_loaded_node = find_least_loaded_node(nodes, 3);
    assign_process_to_node(least_loaded_node, new_process);

    // Mostrar cargas después de la asignación
    printf("\nCargas después de asignar el nuevo proceso:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nodo %d: Carga = %d\n", nodes[i].id, nodes[i].load);
    }

    return 0;
}
