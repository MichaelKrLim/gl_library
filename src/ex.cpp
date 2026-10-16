#include <glad/glad.h>

#include <array>
#include <cmath>
#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	const GLchar* const vertex_shader_source=
R"(
#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;

out vec3 v_color;

void main()
{
	gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
	v_color=a_color;
}
)";

	const unsigned vertex_shader=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);

	glCompileShader(vertex_shader);
	int success;
	std::string err_message;
	err_message.resize(512);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex_shader, err_message.size(), NULL, err_message.data());
		std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<err_message<<"\n";
		return EXIT_FAILURE;
	}

	const GLchar* const fragment_shader_source =
R"(
#version 330 core

in vec3 v_color;

out vec4 FragColor;

void main()
{
	FragColor = vec4(v_color,1.0f);
}
)";

	const unsigned fragment_shader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment_shader, err_message.size(), NULL, err_message.data());
		std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<err_message<<"\n";
		return EXIT_FAILURE;
	}

	const unsigned shader_program=glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(shader_program, err_message.size(), NULL, err_message.data());
		std::cout<<"ERROR::SHADER::LINK::COMPILATION_FAILED\n"<<err_message<<"\n";
		return EXIT_FAILURE;
	}

	std::array<float,18> vertices = {
		 // position  //color
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned vbo, vao;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, reinterpret_cast<void*>(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shader_program);

	glfwTerminate();
}
