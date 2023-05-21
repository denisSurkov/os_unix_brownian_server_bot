cmake_minimum_required(VERSION 3.22)
project(os_unix_brownian_server_bot C)

set(CMAKE_C_STANDARD 23)

add_executable(os_unix_brownian_server_bot server/main.c common/logger.h common/logger.c common/config_reading.c common/config_reading.h)
add_executable(os_unix_brownian_client client/main.c common/logger.h common/logger.c common/config_reading.c common/config_reading.h)
