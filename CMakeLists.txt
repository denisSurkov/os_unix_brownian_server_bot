cmake_minimum_required(VERSION 3.22)
project(os_unix_brownian_server_bot C)

set(CMAKE_C_STANDARD 23)

add_executable(os_unix_brownian_server_bot server/main.c)
add_executable(os_unix_brownian_client client/main.c)
