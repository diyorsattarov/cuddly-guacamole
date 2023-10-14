#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <string>

#ifdef _WIN32 // Windows-specific includes
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Link with the Winsock library
#else // Linux-specific includes
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif

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

#endif // SOCKET_H
