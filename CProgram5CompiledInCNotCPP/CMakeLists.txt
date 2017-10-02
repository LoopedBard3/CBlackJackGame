cmake_minimum_required(VERSION 3.8)
project(CProgram5CompiledInCNotCPP)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(CProgram5CompiledInCNotCPP ${SOURCE_FILES})