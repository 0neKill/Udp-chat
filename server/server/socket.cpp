#include "socket.h"

Socket::Socket(int port)
{
    this->port = port;
}

bool Socket::equals(int port) {
    return this->port == port;
}
