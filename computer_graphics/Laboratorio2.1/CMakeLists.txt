cmake_minimum_required(VERSION 3.5)

project(Laboratorio2)

set(DEPENDENCIES $ENV{HOME}/dependencies_GL_GLFW)
set(IMGUI_PATH ${DEPENDENCIES}/ImGui)
set(INCLUDE_PATH ${DEPENDENCIES}/include)

if(NOT EXISTS ${IMGUI_PATH})
        message(FATAL_ERROR "ImGui path not found: ${IMGUI_PATH}")
endif()

find_package(OpenGL REQUIRED)

include_directories(${DEPENDENCIES} ${INCLUDE_PATH} ${IMGUI_PATH})

file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp ${IMGUI_PATH}/*.h)
file(GLOB SOURCES *.cpp *.c *.h)

file(GLOB RESOURCES res/*)

add_executable(${PROJECT_NAME} ${IMGUI_SOURCES} ${SOURCES})
file(COPY ${RESOURCES} DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${DEPENDENCIES}/lib/glfw3.lib)
else()
        target_link_libraries(${PROJECT_NAME} PUBLIC ${DEPENDENCIES}/lib/glfw3.a)
endif()
