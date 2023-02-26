#ifndef TCPSERVER
#define TCPSERVER

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <sstream>

// A basic single-threaded TCP server for Linux

class TCPServer {
    public:
    std::string ip_address;
    unsigned short port;

    TCPServer(std::string ip_address, unsigned short port);
    ~TCPServer();

    private:
    // Return value of socket()
    int sockfd;

    // Return value of accept()
    int new_sockfd;

    // Host IPv4 socket address and size in bytes for bind()
    struct sockaddr_in addr;
    const unsigned int addrlen = sizeof(addr);

    // Peer IPv4 socket address and size in bytes for accept()
    struct sockaddr_in new_addr;
    unsigned int new_addrlen = sizeof(new_addr);

    enum LogLevel {
        INFO, // Server initialization, new peers, etc.
        FATAL // Exits the program
    };

    void log(const LogLevel level, const std::string &msg);

    int startServer();
    int startListen();
    int acceptConnection();
    int readConnection();
    int writeConnection();
};

#endif