cmake_minimum_required(VERSION 3.24)
project(boids)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp src/boids.cpp src/simulation.cpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} -lm)
