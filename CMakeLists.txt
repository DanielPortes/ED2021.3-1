cmake_minimum_required(VERSION 3.10)
project(ED2021)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(ED2021
        "src/main.cpp"
        "src/Timer.cpp"
        "src/ArvoreB.cpp"
        "src/ArvoreB.h"
        "src/ArvoreVP.cpp"
        "src/ArvoreVP.h"
        "src/noVP.h"
        "src/Timer.h" "src/Leitura.h" "src/Leitura.cpp" "src/Parametros.h" "src/ordenacao.cpp" "src/ordenacao.h" "src/tabelaHash.h" "src/tabelaHash.cpp" "src/moduloTeste.cpp")