#include <tcpServer.h>

int main() {
    const char* SERVER_IP_ADDRESS = std::getenv("SERVER_IP_ADDRESS");

    if (SERVER_IP_ADDRESS == nullptr) {
        std::cerr << "ERROR: Environment variable 'SERVER_IP_ADDRESS' is not set" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }
    std::string ip_address(SERVER_IP_ADDRESS);

    const char* SERVER_PORT = std::getenv("SERVER_PORT");

    if (SERVER_PORT == nullptr) {
        std::cerr << "ERROR: Environment variable 'SERVER_PORT' is not set" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }
    unsigned short port = (unsigned short)std::stoi(std::string(SERVER_PORT));

    TCPServer server = TCPServer(ip_address, port);

    return 0;
}