# http-server
## Introduction

This project was an exercise in creating a single-threaded TCP server in C++. The implementation uses the <sys/socket.h> header file from C,
which includes functions for creating and manipulating sockets using the POSIX standard. A brief description of the steps involved are as follows:

1. Initialize and bind a host TCP socket using the IPv4 internet protocols. The socket address is determined by the IPv4 address and port passed to the 
constructor of the TCPServer object.

2. Start listening on the host TCP socket and add incoming connections (peers) to a fixed-size queue. The queue is given a fixed size, causing it to
reject additional peers until a space is available on the queue.

3. Accept the peer at the top of the queue and create a new connected socket. The address of the new socket is populated using the IPv4 address and port 
of the peer.

4. Read the bytes transmitted by the peer on the new socket.

5. Write the bytes of a simple "Hello World!" char array to the new socket for demonstration purposes. Typically a server would reply with an 
appropriate HTTP response and any requested files (e.g. HTML, CSS, JavaScript).

6. Close the new socket and repeat again from step 3.

## How to Run

These instructions are intended for Linux machines running Docker and Docker Compose.

1. Clone the repository to your local machine

`https://github.com/tailflail/http-server.git`

2. Create a .env file in the root directory of the project and populate it with the following environment variables. These placeholders should be replaced
with values of your choice (e.g. SERVER_IP_ADDRESS=0.0.0.0)

```
SERVER_IP_ADDRESS=placeholder
SERVER_PORT=placeholder
```

3. Build and run the Docker image

`sudo docker compose up --build`

4. Open your browser at the IP and port of your choice (e.g. http://localhost:3000)

## Technologies Used

- C++
- TCP
- IPv4
- Docker
- CMake
- POSIX
