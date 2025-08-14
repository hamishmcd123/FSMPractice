cmake_minimum_required(VERSION 3.31)

project(FSM)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES src/*.cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/libraylib.a)

