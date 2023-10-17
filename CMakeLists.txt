cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Game1 VERSION 1.0)
message(STATUS "Setup c++ standard...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

function(add_game)
    foreach(GAME_FOLDER ${ARGN})
        find_package(fmt CONFIG REQUIRED)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            add_definitions(-DDD_RSS_FOLDER="./resources")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            add_definitions(-DDD_RSS_FOLDER="../resources")
        else()
            message(FATAL_ERROR "Unknown compiler")
        endif()

        file(GLOB_RECURSE GAME1_SOURCE_FILES  ${CMAKE_SOURCE_DIR}/$(GAME_FOLDER)/*.cpp
                                            ${CMAKE_SOURCE_DIR}/$(GAME_FOLDER)/*.c)

        add_executable($(GAME_FOLDER) ${GAME1_SOURCE_FILES})
        target_link_libraries($(GAME_FOLDER) PRIVATE engine fmt::fmt)
        target_include_directories($(GAME_FOLDER) PRIVATE engine)

        message(STATUS "Copy resource files...")
        file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
    endforeach(GAME_FOLDER ${ARGN})
endfunction()

add_subdirectory(engine)
add_game(test_game)

message(STATUS "User CMake config done!")


