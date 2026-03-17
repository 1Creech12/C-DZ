cmake_minimum_required(VERSION 3.16)

project(prnod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prnod main.cpp
    Nod.h
    Nod.cpp)

include(GNUInstallDirs)
install(TARGETS prnod
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
