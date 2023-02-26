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

# Compile and run the code
CMD ["sh", "-c", "cmake . && make && ./http-server"]