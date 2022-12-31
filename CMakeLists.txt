cmake_minimum_required(VERSION 3.24)
project(cfd_physics)
set(CMAKE_CXX_STANDARD 20)

# SFML Dependency Pull
include(FetchContent)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Project Build
include_directories(src/cfd_lib/headers)
add_library(cfd_lib src/cfd_lib/container.cpp src/cfd_lib/physics.cpp)

add_executable(cfd_physics src/main.cpp)
target_link_libraries(cfd_physics PRIVATE cfd_lib)

# Link SFML Dependency
target_link_libraries(cfd_physics PRIVATE sfml-graphics)
target_link_libraries(cfd_lib PRIVATE sfml-graphics)

# Set Compiler up
target_compile_features(cfd_physics PRIVATE cxx_std_20)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(
            TARGET cfd_physics POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:cfd_physics> $<TARGET_FILE_DIR:cfd_physics> COMMAND_EXPAND_LISTS
    )
endif()
