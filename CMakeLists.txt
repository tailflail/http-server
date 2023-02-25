cmake_minimum_required(VERSION 3.5)
project(http-server)
add_executable(http-server main.cpp tcpServer.cpp)
target_include_directories(http-server PRIVATE .)