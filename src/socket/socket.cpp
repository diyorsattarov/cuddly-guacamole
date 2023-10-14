#include <socket/socket.h>

Socket::Socket() : socket_fd(-1) {}

Socket::~Socket() {
    close();
}

bool Socket::create() {
    socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    return socket_fd != -1;
}

bool Socket::bind(int port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    return ::bind(socket_fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == 0;
}

bool Socket::listen() {
    return ::listen(socket_fd, SOMAXCONN) == 0;
}

int Socket::accept() {
    return ::accept(socket_fd, nullptr, nullptr);
}

bool Socket::connect(const std::string& ipAddress, int port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddress.c_str(), &addr.sin_addr) <= 0) {
        std::cerr << "Invalid IP address" << std::endl;
        return false;
    }

    return ::connect(socket_fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == 0;
}

void Socket::close() {
    if (socket_fd != -1) {
        ::close(socket_fd);
        socket_fd = -1;
    }
}
