cmake_minimum_required(VERSION 3.12)

project(DrunkenCompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(game
        project/main.cpp
        project/game_state.cpp
        project/ui.cpp
        project/questions.cpp
        project/events.cpp
)

if(MSVC)
    target_compile_options(game PRIVATE /W4)
else()
    target_compile_options(game PRIVATE -Wall -Wextra -pedantic)
endif()
