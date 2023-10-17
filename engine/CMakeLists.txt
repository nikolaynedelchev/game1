set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

message(STATUS "Finding required packages...")
find_package(raylib CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")

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

message(STATUS "Find all cpp files...")
file(GLOB_RECURSE ENGINE_SOURCE_FILES ${CMAKE_SOURCE_DIR}/engine/*.cpp
                                      ${CMAKE_SOURCE_DIR}/engine/*.c)

add_library(engine STATIC ${ENGINE_SOURCE_FILES})
target_include_directories(engine PRIVATE ${RAYGUI_INCLUDE_DIRS} ${RAYLIB_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}  ${CMAKE_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "GNU compiler debug build detected...")
    target_compile_options(engine PRIVATE -fsanitize=address -fsanitize=undefined)
    target_link_libraries(engine PRIVATE -fsanitize=address -fsanitize=undefined)
endif()

target_link_libraries(engine PRIVATE Threads::Threads raylib fmt::fmt)



