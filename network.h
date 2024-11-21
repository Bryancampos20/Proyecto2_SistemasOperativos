#ifndef NETWORK_H
#define NETWORK_H

#include "node.h"

// Inicializa el socket del servidor
int init_server_socket(int port);

// Maneja conexiones entrantes y mensajes
void* handle_connections(void* args);

// Enviar mensaje a otro nodo
int send_message_to_node(int target_port, const char* message);

#endif
