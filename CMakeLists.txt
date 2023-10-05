cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Game1 VERSION 1.0)

find_package(raylib CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")


add_executable(game1 main.cpp raylib_impl.cpp)

target_include_directories(game1 PRIVATE ${RAYGUI_INCLUDE_DIRS})
target_include_directories(game1 PRIVATE ${RAYLIB_INCLUDE_DIRS})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(game1 PRIVATE -fsanitize=address -fsanitize=undefined)
    target_link_libraries(game1 PRIVATE -fsanitize=address -fsanitize=undefined)
endif()

target_link_libraries(game1 PUBLIC Threads::Threads)
target_link_libraries(game1 PRIVATE raylib)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})




