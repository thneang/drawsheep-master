cmake_minimum_required(VERSION 2.6)
project(drawsheep)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4 4.4.3 REQUIRED QtGui QtXml)

SET(HEADERS_WITH_QT include/Window.hpp)

QT4_WRAP_CPP(HEADERS_WITH_QT_MOC ${HEADERS_WITH_QT})

add_definitions(-std=c++11 -Wall)

include_directories(include ${QT4_INCLUDE_DIR})

set(ALL_LIBRARIES ${QT4_LIBRARY})

file(GLOB SRC_DIRECTORIES "src/*")

add_executable(drawsheep main.cpp ${SRC_DIRECTORIES} ${HEADERS_WITH_QT_MOC})

add_executable(server main_server.cpp src/Server.cpp )

target_link_libraries(drawsheep Qt4::QtGui Qt4::QtXml)