#include <tcpServer.h>

TCPServer::TCPServer(std::string ip_address, unsigned short port) 
: ip_address(ip_address), port(port)
{ 
    /*
    Initializes the IPv4 socket address. 
    Function htons() converts values between host and network byte order. This is necessary because network byte order must be big-endian.
    Function inet_addr() converts a decimal IPv4 address C-string (e.g. "127.0.0.1") to an integer representation in network byte order.
    */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip_address.c_str());

    startServer();
}

TCPServer::~TCPServer() {
    // Close the sockets and exit the program when the destructor runs.
    close(sockfd);
    close(new_sockfd);
    exit(EXIT_SUCCESS);
}

int TCPServer::startServer() {
    /*  
    AF_INET - IPv4 Internet protocols
    SOCK_STREAM - Sequenced, reliable, two-way connection-based byte streams (TCP)
    0 - Streaming protocol (0 allows the OS to choose an appropriate protocol)

    Initializes an endpoint for communication and returns a file descriptor referring to that endpoint. */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        std::cerr << "ERROR: Could not create socket (" << errno << ")" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }

    // Binds sockfd to the host IP address.
    const int bindSockfd = bind(sockfd, (struct sockaddr *)&addr, addrlen);

    if (bindSockfd == -1) {
        std::cerr << "ERROR: Could not bind socket to IP " << ip_address <<  " (" << errno << ")" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }

    std::cout << "## Successfully initialized server ##" << std::endl;

    startListen();

    return 0;
}

int TCPServer::startListen() {
    // Max length for the queue of pending connections.
    const int backlog = 10;

    // Start listening on the host endpoint for incoming connections.
    const int listenSockfd = listen(sockfd, backlog);

    if (listenSockfd == -1) {
        std::cerr << "ERROR: Could not listen on host socket (" << errno << ")" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }

    std::cout << "Listening on " << ip_address << ":" << port << " ..." << "\n" << std::endl;
    
    while (true) {
        acceptConnection();
        readConnection();
        writeConnection();

        close(new_sockfd);
    }

    return 0;
}

int TCPServer::acceptConnection() {
    /* 
    Accepts a new connection on the listening socket, removing it from the queue and returning the file descriptor of a new socket.
    Here new_addr is mutated with the socket address of the peer. */
    new_sockfd = accept(sockfd, (struct sockaddr *)&new_addr, &new_addrlen);

    if (new_sockfd == -1) {
        std::cerr << "ERROR: Could not accept peer (" << errno << ")" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }

    const std::string peer_ip_address = inet_ntoa(new_addr.sin_addr);
    const unsigned short peer_port = ntohs(new_addr.sin_port);

    std::cout << "Peer connected from " << peer_ip_address << ":" << peer_port << std::endl;

    return 0;
}

int TCPServer::readConnection() {
    // Number of bytes to read into buffer
    unsigned short count = 4096;

    // Buffer to store bytes from new_sockfd
    char buf[count];

    // Reads and returns the number of bytes from new_sockfd
    ssize_t readBytes = read(new_sockfd, buf, count);

    if (readBytes == -1) {
        std::cerr << "ERROR: Could not read bytes from peer (" << errno << ")" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }

    std::cout << "Received bytes: " << readBytes << std::endl;

    return 0;
}

int TCPServer::writeConnection() {
    // Number of bytes to write into buffer
    unsigned short count = 12;

    // Buffer to write bytes to new_sockfd
    std::string buf = "Hello World!";

    // Writes the bytes from buf into new_sockfd and returns the number of bytes written
    ssize_t writeBytes = write(new_sockfd, buf.c_str(), count);

    if (writeBytes == -1) {
        std::cerr << "ERROR: Could not write bytes to peer (" << errno << ")" << std::endl;
        exit(EXIT_FAILURE);
        return 1;
    }

    std::cout << "Wrote bytes: " << writeBytes << "\n" << std::endl;

    return 0;
}