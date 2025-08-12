cmake_minimum_required(VERSION 3.20)
project(GraphicsMath)
set(CMAKE_CXX_STANDARD 23)

# Which chapter to build (leave empty to build all)
set(CHAPTER "" CACHE STRING "Which chapter to build (e.g., Chapter2)")
set_property(CACHE CHAPTER PROPERTY STRINGS Chapter2)

# Base folder that contains the chapter subdirs
set(CHAPTERS_BASE "${CMAKE_CURRENT_SOURCE_DIR}/3D_Game_Programming_and_Computer_Graphics")

if(CHAPTER STREQUAL "")
    message(STATUS "Building all chapters")
    add_subdirectory("${CHAPTERS_BASE}/Chapter2")
else()
    message(STATUS "Building only ${CHAPTER}")
    add_subdirectory("${CHAPTERS_BASE}/${CHAPTER}")

    # Convenience: `cmake --build . --target run` runs the selected chapter
    add_custom_target(run
            COMMAND $<TARGET_FILE:${CHAPTER}>
            DEPENDS ${CHAPTER}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running ${CHAPTER}")
endif()
