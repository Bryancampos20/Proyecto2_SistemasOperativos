#include "node.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8080

void send_message(Node* node);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <ID del Nodo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    Node node;
    node.id = atoi(argv[1]);
    node.socket_fd = init_server_socket(PORT + node.id);
    if (node.socket_fd == -1) {
        fprintf(stderr, "No se pudo iniciar el nodo\n");
        exit(EXIT_FAILURE);
    }

    printf("Nodo %d activo en el puerto %d.\n", node.id, PORT + node.id);

    pthread_t listener_thread;
    if (pthread_create(&listener_thread, NULL, handle_connections, &node) != 0) {
        perror("Error al crear el hilo de escucha");
        close(node.socket_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        send_message(&node);
    }

    pthread_cancel(listener_thread);
    pthread_join(listener_thread, NULL);
    close(node.socket_fd);
    return 0;
}

void send_message(Node* node) {
    char buffer[1024];
    printf("Ingrese mensaje (q para salir): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    if (strcmp(buffer, "q") == 0) {
        exit(EXIT_SUCCESS);
    }

    int target_node_id;
    printf("Ingrese el ID del nodo destino: ");
    scanf("%d", &target_node_id);
    getchar();

    int target_port = PORT + target_node_id;
    if (send_message_to_node(target_port, buffer) == 0) {
        printf("[Mensaje enviado]: %s\n", buffer);
    } else {
        printf("Error al enviar el mensaje\n");
    }
}
