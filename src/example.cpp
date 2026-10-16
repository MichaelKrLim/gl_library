#include "Shader.hpp"
#include "Shader_program.hpp"
#include "Vertex_array_object.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <vector>

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window=glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if(window==NULL)
	{
		std::cout<<"Failed to create GLFW window"<<std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr<<"Failed to initialize GLAD\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glViewport(0, 0, 800, 600);

	std::vector<Vertex> vertices = {
		Vertex{.position={ 0.5f,  0.5f, 0.0f}, .colour={1.0f,1.0f,1.0f,1.0f}},  // top right
		Vertex{.position={ 0.5f, -0.5f, 0.0f}, .colour={0.34f,0.402f,0.44f,1.0f}},  // bottom right
		Vertex{.position={-0.5f, -0.5f, 0.0f}, .colour={0.3423f,1.0f,1.0f,1.0f}},  // bottom left
		Vertex{.position={-0.5f,  0.5f, 0.0f}, .colour={0.234f,0.23423f,1.0f,1.0f}}   // top left 
	};

	std::vector<unsigned int> indices = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	Shader_program shader_program(
		Shader<GL_VERTEX_SHADER>(std::filesystem::path{"/home/michael/coding/projects/gl_lib/src/vertex_shader.glsl"}),
		Shader<GL_FRAGMENT_SHADER>(std::filesystem::path{"/home/michael/coding/projects/gl_lib/src/fragment_shader.glsl"})
	);

	Vertex_array_object<Vertex, With_ebo::yes, unsigned int> vao(vertices, GL_STATIC_DRAW, indices);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_program.use();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
