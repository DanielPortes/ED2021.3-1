cmake_minimum_required(VERSION 3.16)
project(ED2021_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(ED2021_3
        src/ArvoreB.cpp
        src/ArvoreB.h
        src/arvoreVP.cpp
        src/arvoreVP.h
        src/Leitura.cpp
        src/Leitura.h
        src/main.cpp
        src/moduloArvoreVP.h
        src/moduloTeste.cpp
        src/noVP.h
        src/ordenacao.cpp
        src/ordenacao.h
        src/Parametros.h
        src/tabelaHash.cpp
        src/tabelaHash.h
        src/Timer.cpp
        src/Timer.h
        src/Huffman.h
        src/Huffman.cpp)
