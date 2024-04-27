cmake_minimum_required(VERSION 3.19)
project(trabalho)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories("POO - 2223 - Biblioteca Consola")

add_executable(trabalho
        Alimento.cpp
        Alimento.h
        Animal.cpp
        Animal.h
        Comandos.cpp
        Comandos.h
        curses.h
        main.cpp
        Reserva.cpp
        Reserva.h
        Zona.cpp
        Zona.h)

target_link_libraries(${PROJECT_NAME} C:/Users/biama/Desktop/PDCurses-3.9/wincon/pdcurses.a)