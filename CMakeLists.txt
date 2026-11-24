cmake_minimum_required(VERSION 4.0 FATAL_ERROR)
project(gl_lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)

CPMAddPackage(URI "gh:vimpunk/mio#master" SYSTEM YES)
CPMAddPackage("gh:glfw/glfw#3.3.10")
CPMAddPackage("gh:g-truc/glm#1.0.3")
find_package(OpenGL REQUIRED)
add_library(glad STATIC glad.c)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/glad")

add_library(lib STATIC
	src/Shader_program.hpp
	src/Mesh.hpp
	src/Shader.hpp
	src/stb_image.cpp
	src/Texture.cpp src/Texture.hpp
	src/Drawable.hpp
)

add_executable(target src/example.cpp)

set_target_properties(lib target PROPERTIES
	CXX_STANDARD 26
	CXX_STANDARD_REQUIRED 26
)

set_target_properties(target PROPERTIES
	CXX_EXTENSIONS OFF
)

target_compile_options(target PRIVATE
	-Wall
	-freflection
	-Wextra
	-pedantic
	-Og
	-fmax-errors=1
)

target_link_libraries(lib
	PUBLIC OpenGL::GL glad glfw glm::glm
	mio::mio # mio should be private but in a .tpp
)

target_link_libraries(target PRIVATE lib)
