# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.28)

# Set the project name
project(vk-task)

set(CMAKE_CXX_STANDARD 17)

# Set the directories that should be included in the build command for this project
file(GLOB SOURCES src/*.cpp)

# Add an executable with the above sources
add_executable(vk-task ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(vk-task
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

