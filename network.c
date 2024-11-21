#include "node.h"
#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

// Inicializar nodo como servidor
int init_server_socket(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error al crear el socket");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
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

// Aceptar conexiones y procesar mensajes entrantes
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
            printf("\n[Mensaje recibido]: %s\n", buffer);
            fflush(stdout); // Asegúrate de que el mensaje se imprime de inmediato
        }

        close(client_socket);
    }
    return NULL;
}

// Conectar a otro nodo y enviar mensaje
int send_message_to_node(int target_port, const char* message) {
    struct sockaddr_in target_addr;
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(target_port);
    if (inet_pton(AF_INET, "127.0.0.1", &target_addr.sin_addr) <= 0) {
        perror("Dirección no válida o no soportada");
        return -1;
    }

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error al crear el socket cliente");
        return -1;
    }

    if (connect(client_socket, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0) {
        perror("Error al conectar con el nodo destino");
        close(client_socket);
        return -1;
    }

    if (send(client_socket, message, strlen(message), 0) < 0) {
        perror("Error al enviar mensaje");
        close(client_socket);
        return -1;
    }

    close(client_socket);
    return 0;
}
