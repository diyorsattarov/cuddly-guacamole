#ifndef SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class Socket {
private:
    int socket_fd;
public:
    Socket();
    ~Socket();

    bool create();
    bool bind(int port);
    bool listen();
    
    int accept();
    bool connect(const std::string& ipAddress, int port);

    void close();
};
#endif //SOCKET_H