cmake_minimum_required(VERSION 3.30)

project(game LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set platform: Desktop by default
if(NOT DEFINED PLATFORM)
	set(PLATFORM Desktop)
endif()

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of the build" FORCE)
endif()

message(STATUS "Target platform: ${PLATFORM}")

# Download Raylib
include(FetchContent)
FetchContent_Declare(raylib GIT_REPOSITORY "https://github.com/raysan5/raylib.git")
FetchContent_MakeAvailable(raylib)

# Include and Link Raylib in the game
add_executable(${PROJECT_NAME}
    "game.cpp" "rutils.cpp" "gui/fonts.cpp" "gui/gui.cpp" "gui/text.cpp"
    "enemies_manager.cpp" "sprite_sheet.cpp" "button.cpp"  "flower.cpp"
)


target_link_libraries(${PROJECT_NAME} raylib)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})

if(PLATFORM STREQUAL "Web")
    # Force output to .html
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
    set(FONTS_DIR "${CMAKE_SOURCE_DIR}/fonts")

    # Emscripten flags
    set_target_properties(${PROJECT_NAME} PROPERTIES
        SUFFIX ".html"
	LINK_FLAGS "-s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=['_main'] -s EXPORTED_RUNTIME_METHODS=['cwrap'] --preload-file \"${ASSETS_DIR}@/assets\" --preload-file \"${FONTS_DIR}@/fonts\" --shell-file ${CMAKE_SOURCE_DIR}/build_web/shell_minimal.html"
    )

#     set(CMAKE_EXECUTABLE_SUFFIX ".html")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s FULL_ES3=1 --embed-file \"${ASSETS_DIR}\" --embed-file \"${FONTS_DIR}\"")
endif()
