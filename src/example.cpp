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

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window=glfwCreateWindow(640, 480, "gl_library", NULL, NULL);
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
	glViewport(0, 0, 640, 480);

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

	const auto width = texture.query_width();
	const auto height = texture.query_height();
	Drawable drawable(quad_for_texture_of(width, height), std::move(texture));
	drawable.scale(0.5f);

	glm::mat4 view  = glm::mat4(1.0f);
	glm::mat4 ortho = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 100.0f);
	shader_program.use();
	const auto projection_uniform = shader_program.get_uniform_location("projection");
	shader_program.set_uniform(projection_uniform, ortho);
	const auto model_uniform = shader_program.get_uniform_location("model");
	shader_program.set_uniform(model_uniform, drawable.get_model_matrix());
	const auto view_uniform = shader_program.get_uniform_location("view");
	shader_program.set_uniform(view_uniform, view);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		drawable.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
