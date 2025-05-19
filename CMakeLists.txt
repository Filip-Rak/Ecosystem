# ------------------ Project Wide Settings ------------------
cmake_minimum_required(VERSION 3.16)
project(Ecosystem LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------ Variables ------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/external)
set(SOURCE_DIR src)

# ------------------ Dependencies ------------------
include(FetchContent)

FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.2
)

FetchContent_Declare(
	TGUI
	GIT_REPOSITORY https://github.com/texus/TGUI.git
	GIT_TAG v1.6.1
)

# Explicitly declare TGUI's backend 
set(TGUI_BACKEND SFML_GRAPHICS CACHE STRING "" FORCE)

FetchContent_MakeAvailable(
	SFML 
	TGUI
)

# ------------------ Executable ------------------
add_executable(ecosystem)

target_sources(ecosystem PRIVATE
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Automaton.cpp
    ${SOURCE_DIR}/Controller.cpp
    ${SOURCE_DIR}/UI.cpp
    ${SOURCE_DIR}/Utils.cpp
    ${SOURCE_DIR}/Visualization.cpp
)

target_include_directories(ecosystem PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${tgui_SOURCE_DIR}/include
)

target_link_libraries(ecosystem PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    tgui
)
