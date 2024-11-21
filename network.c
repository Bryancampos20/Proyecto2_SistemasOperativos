#include "node.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

int init_server_socket(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error al crear el socket");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Escuchar en todas las interfaces
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al vincular el socket");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("Error al escuchar en el socket");
        close(server_fd);
        return -1;
    }

    return server_fd;
}

void* handle_connections(void* args) {
    Node* node = (Node*)args;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        int client_socket = accept(node->socket_fd, (struct sockaddr*)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("Error al aceptar conexión");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        if (read(client_socket, buffer, BUFFER_SIZE) > 0) {
            int process_id, execution_time;
            sscanf(buffer, "%d %d", &process_id, &execution_time);

            Process process = {process_id, execution_time};
            if (enqueue(&node->process_queue, process) == 0) {
                printf("Nodo %d recibió el proceso %d con tiempo de ejecución %d.\n", 
                       node->id, process.id, process.execution_time);
            } else {
                printf("Nodo %d tiene la cola llena. No se pudo añadir el proceso.\n", node->id);
            }
        }

        close(client_socket);
    }
    return NULL;
}
