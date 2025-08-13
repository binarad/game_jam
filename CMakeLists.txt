cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
project(game CXX)

# Download Raylib
include(FetchContent)
FetchContent_Declare(raylib GIT_REPOSITORY "https://github.com/raysan5/raylib.git")
FetchContent_MakeAvailable(raylib)

# Include and Link Raylib in the game
add_executable(${PROJECT_NAME}
    "game.cpp" "rutils.cpp" "gui/fonts.cpp" "gui/gui.cpp" "gui/text.cpp"
    "enemies.cpp" "sprite_sheet.cpp" "button.cpp"
)
target_link_libraries(${PROJECT_NAME} raylib)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
