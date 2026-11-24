#include "Drawable.hpp"
#include "Mesh.hpp"
#include "Shader_program.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <filesystem>
#include <iostream>
#include <utility>
#include <vector>

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window=glfwCreateWindow(800, 600, "gl_library", NULL, NULL);
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

	struct Vertex { glm::vec3 position; glm::vec4 colour; glm::vec2 texture_coord; };

	std::vector<Vertex> vertices = {
		Vertex{.position={ 480.0f,  120.0f, 0.0f}, .colour={1.0f,1.0f,1.0f,1.0f},       .texture_coord={1.0f, 1.0f}},  // top right
		Vertex{.position={ 480.0f,  360.0f, 0.0f}, .colour={0.34f,0.402f,0.44f,1.0f},   .texture_coord={1.0f, 0.0f}},  // bottom right
		Vertex{.position={ 160.0f,  360.0f, 0.0f}, .colour={0.3423f,1.0f,1.0f,1.0f},    .texture_coord={0.0f, 0.0f}},  // bottom left
		Vertex{.position={ 160.0f,  120.0f, 0.0f}, .colour={0.234f,0.23423f,1.0f,1.0f}, .texture_coord={0.0f, 1.0f}}   // top left 
	};

	std::vector<unsigned int> indices = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	Shader_program shader_program(
		Shader<Shader_type::vertex>(std::filesystem::path{"../src/vertex_shader.glsl"}),
		Shader<Shader_type::fragment>(std::filesystem::path{"../src/fragment_shader.glsl"})
	);

	Texture texture(std::filesystem::path{"../src/example_texture.jpg"});
	texture.set_params([]
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	});

	Mesh<Vertex, With_ebo::yes, unsigned int> mesh(vertices, GL_STATIC_DRAW, indices);

	Drawable drawable(std::move(mesh), std::move(texture));

	glm::mat4 ortho=glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1000.0f);
	shader_program.use();
	const auto projection_uniform = shader_program.get_uniform_location("projection");
	shader_program.set_uniform(projection_uniform, ortho);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		drawable.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
