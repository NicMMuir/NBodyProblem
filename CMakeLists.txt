cmake_minimum_required(VERSION 3.19)
project(NBody_Alt C)

set(CMAKE_C_STANDARD 99)

add_executable(NBody_Alt main.c Node.h header.h Node.c Body.c Body.h NBody.c NBody.h)

target_link_libraries(NBody_Alt m)