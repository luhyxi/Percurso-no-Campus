cmake_minimum_required(VERSION 3.10)

project(Percurso-no-Campus)

set(CMAKE_C_STANDARD 11)

add_executable(Percurso-no-Campus main.c
        src/DataStructs/grafo.c
        src/DataStructs/locaisReader.c
        src/DataStructs/caminhosReader.c)