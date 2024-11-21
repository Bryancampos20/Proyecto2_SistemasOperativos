#include "node.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LOAD 20 // Capacidad máxima de carga para cada nodo

void redistribute_if_overloaded(Node* nodes, int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i].load > MAX_LOAD) {
            printf("Nodo %d sobrecargado. Redistribuyendo procesos...\n", nodes[i].id);
            while (nodes[i].load > MAX_LOAD) {
                Process process;
                if (dequeue(&nodes[i].process_queue, &process)) {
                    Node* least_loaded = NULL;

                    // Buscar un nodo que no esté sobrecargado
                    for (int j = 0; j < num_nodes; j++) {
                        if (j != i && nodes[j].load <= MAX_LOAD) {
                            if (least_loaded == NULL || nodes[j].load < least_loaded->load) {
                                least_loaded = &nodes[j];
                            }
                        }
                    }

                    // Asignar el proceso al nodo menos cargado disponible
                    if (least_loaded != NULL) {
                        assign_process_to_node(least_loaded, process);
                        printf("Proceso %d redistribuido al Nodo %d\n", process.id, least_loaded->id);
                    } else {
                        printf("No hay nodos disponibles para redistribuir el proceso %d\n", process.id);
                        enqueue(&nodes[i].process_queue, process); // Reinsertar el proceso en la cola original
                        break;
                    }
                }
            }
        }
    }
}


int main() {
    // Inicializar nodos
    Node nodes[3];
    for (int i = 0; i < 3; i++) {
        nodes[i].id = i + 1;
        nodes[i].load = 0;
        nodes[i].active = 1;
        init_queue(&nodes[i].process_queue);
    }

    // Asignar procesos iniciales
    Process processes[] = {
        {1, 10}, {2, 12}, {3, 5}, {4, 8}, {5, 15}
    };

    for (int i = 0; i < 5; i++) {
        Node* least_loaded = find_least_loaded_node(nodes, 3);
        assign_process_to_node(least_loaded, processes[i]);
        printf("Proceso %d asignado al Nodo %d\n", processes[i].id, least_loaded->id);

        // Verificar si es necesario redistribuir
        redistribute_if_overloaded(nodes, 3);
    }

    // Mostrar estado final
    printf("\nEstado final de los nodos:\n");
    for (int i = 0; i < 3; i++) {
        printf("Nodo %d: Carga = %d, Activo = %d\n", nodes[i].id, nodes[i].load, nodes[i].active);
    }

    return 0;
}
