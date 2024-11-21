#ifndef NETWORK_H
#define NETWORK_H

#include "node.h"

// Inicializa el socket del servidor
int init_server_socket(int port);

// Maneja conexiones entrantes y mensajes
void* handle_connections(void* args);

// Enviar mensaje a otro nodo
int send_message_to_node(int target_port, const char* message);

// Monitorea el estado de los nodos
void check_node_status(Node* node);

// Notifica fallos a otros nodos
void notify_failure(Node* node, int failed_node_id);

#endif // NETWORK_H
