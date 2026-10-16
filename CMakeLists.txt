cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(gl_lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)

CPMAddPackage("gh:vimpunk/mio#master")
CPMAddPackage("gh:glfw/glfw#3.3.10")
find_package(OpenGL REQUIRED)
add_library(glad STATIC glad.c)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad")

add_executable(target
	src/example.cpp
	src/Shader_program.hpp
	src/Vertex_array_object.hpp
	src/Shader.hpp
)
set_target_properties(target PROPERTIES
	CXX_STANDARD 26
	CXX_STANDARD_REQUIRED 26
	CXX_EXTENSIONS OFF
)
target_compile_options(target PRIVATE
	-Wall
	-freflection
	-Wextra
	-pedantic
	-Og
	-Wfatal-errors
)

target_link_libraries(target PRIVATE glfw glad OpenGL::GL mio::mio)
