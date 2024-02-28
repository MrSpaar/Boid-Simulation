cmake_minimum_required(VERSION 3.24)
project(boids C)

set(CMAKE_C_STANDARD 23)
find_package(SDL2 REQUIRED)
include_directories(SDL2 ${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        src/main.c src/boids.c src/vectors.c
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} -lm)