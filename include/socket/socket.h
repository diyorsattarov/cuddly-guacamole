#ifndef SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <ostream>
#include <thread>
#include <chrono>

class Socket {
public:
    Socket();
    ~Socket();

    bool create();
    bool bind(int port);
    bool listen();
    
    int accept();
    int socket_fd;
    bool connect(const std::string& ipAddress, int port);

    void close();
};
#endif //SOCKET_H