#include <tcpServer.h>

int main() {
    std::string ip_address = "127.0.0.1";
    unsigned short port = 8080;

    TCPServer server = TCPServer(ip_address, port);

    return 0;
}