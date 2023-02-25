# Get the base Alpine image from Docker Hub
FROM alpine:3.17.0 AS build

RUN apk update && \
    apk add --no-cache \
    build-base \
    libstdc++ \
    cmake

# Specify the working directory
WORKDIR /http-server

# Copy the source files to the working directory
COPY . .

# Set the environment variables
ENV SERVER_IP_ADDRESS=0.0.0.0
ENV SERVER_PORT=8080

# Expose the port 8080 for accessing the server on the host machine
EXPOSE 8080

# Compile and run the code
CMD ["sh", "-c", "cmake . && make && ./http-server"]