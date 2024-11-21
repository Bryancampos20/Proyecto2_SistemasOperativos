#ifndef NODE_H
#define NODE_H

#include <netinet/in.h>

typedef struct {
    int id;
    int socket_fd;
    struct sockaddr_in addr;
} Node;

#endif
