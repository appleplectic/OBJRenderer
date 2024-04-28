cmake_minimum_required(VERSION 3.12)
project(objrenderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(objrenderer src/main.cpp
        src/SImg/SImg.cpp
        src/SImg/SImg.h
        src/OBJRenderer/OBJRenderer.cpp
        src/OBJRenderer/OBJRenderer.h
        src/OBJParser/OBJParser.cpp
        src/OBJParser/OBJParser.h
        src/ArgvParser/ArgvParser.cpp
        src/ArgvParser/ArgvParser.h)
