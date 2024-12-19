cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(Game1 VERSION 1.0)
message(STATUS "Setup c++ standard...")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

function(add_game GAME_NAME)
    find_package(fmt CONFIG REQUIRED)
    find_package(nlohmann_json REQUIRED)
    find_package(CURL REQUIRED)
    find_package(cpr REQUIRED)
    find_package(flecs CONFIG REQUIRED)

    file(GLOB_RECURSE GAME1_SOURCE_FILES  ${CMAKE_SOURCE_DIR}/${GAME_NAME}/*.cpp
                                          ${CMAKE_SOURCE_DIR}/${GAME_NAME}/*.c)

    add_executable(${GAME_NAME} ${GAME1_SOURCE_FILES})

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_definitions(${GAME_NAME} PRIVATE DD_RSS_FOLDER="./resources/${GAME_NAME}")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            # hide the windows console
            #set_target_properties(${GAME_NAME} PROPERTIES
            #                      WIN32_EXECUTABLE YES
            #                      LINK_FLAGS "/ENTRY:mainCRTStartup")
        endif()
        target_compile_definitions(${GAME_NAME} PRIVATE DD_RSS_FOLDER="./resources/${GAME_NAME}")
    else()
        message(FATAL_ERROR "Unknown compiler")
    endif()

    target_link_libraries(${GAME_NAME} PRIVATE dd fmt::fmt cpr::cpr nlohmann_json::nlohmann_json ${CURL_LIBRARIES} flecs::flecs tiny_dnn)

    target_include_directories(${GAME_NAME} PRIVATE dd)

    message(STATUS "Copy resource files...")
endfunction()

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(dd)
add_subdirectory(thirdparty/tiny-dnn)
include_directories(thirdparty/tiny-dnn)
add_game(checkers)
#add_game(test_game)
add_game(frogger)
#add_game(sprite_mgr)
#add_game(hello_world)
#add_game(misc_tests)

message(STATUS "User CMake config done!")


