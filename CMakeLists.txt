cmake_minimum_required(VERSION 3.0.0)
project(HFMCompress VERSION 0.1.0)

include_directories(./include)
aux_source_directory(./src SRC)

enable_testing()

add_executable(HFMCompress main.cpp ${SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)