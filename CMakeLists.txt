cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Game1 VERSION 1.0)

message(STATUS "Setup c++ standard...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

message(STATUS "Finding required packages...")
find_package(raylib CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")

message(STATUS "Find all cpp files...")
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/engine/*.cpp
                               ${CMAKE_SOURCE_DIR}/engine/*.c
                               ${CMAKE_SOURCE_DIR}/game/*.cpp
                               ${CMAKE_SOURCE_DIR}/game/*.c)

#
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "GNU compiler detected...")
    add_compile_options(-Wall -Wextra -Werror)
    add_compile_options(-Werror) # all warinings as errors
    add_definitions(-DDD_RSS_FOLDER="./resources")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    #add_compile_options(/W4 /WX)
    #add_compile_options(/WX) # all warinings as errors
    add_definitions(-DDD_RSS_FOLDER="../resources")
    message(STATUS "Windows compiler")
else()
    message(FATAL_ERROR "Unknown compiler")
endif()

message(STATUS "Create executable terget...")
add_executable(game1 ${SOURCE_FILES})

message(STATUS "Find all include folders...")
target_include_directories(game1 PRIVATE ${RAYGUI_INCLUDE_DIRS})
target_include_directories(game1 PRIVATE ${RAYLIB_INCLUDE_DIRS})
target_include_directories(game1 PRIVATE ${CMAKE_SOURCE_DIR})

message(STATUS "Setup sanitizers...")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "GNU compiler debug build detected...")
    target_compile_options(game1 PRIVATE -fsanitize=address -fsanitize=undefined)
    target_link_libraries(game1 PRIVATE -fsanitize=address -fsanitize=undefined)
endif()

message(STATUS "Create target link libraries...")
target_link_libraries(game1 PUBLIC Threads::Threads)
target_link_libraries(game1 PRIVATE raylib)
target_link_libraries(game1 PRIVATE fmt::fmt)

message(STATUS "Copy resource files...")
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

message(STATUS "User CMake config done!")


