#include "hgpch.h"
#include "Shader.h"

#include <glad/glad.h>

hg::Shader::Shader(const std::string& vertexSrc, const std::string& faagmentSrc)
{

	// 创建着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 发送顶点数据到GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// 编译顶点数据
	glCompileShader(vertexShader);

	// 检查编译是否成功
	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		// 返回错误信息
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// GL自己的日志
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// 出错了我们就不需要它了
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave
		HG_CORE_ERROR("{0}", infoLog.data());
		HG_CORE_ASSERT(false, "Vertex shader compilation failure!");

		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 将片段着色器发送到GL
	// Note that std::string's .c_str is NULL character terminated.
	source = faagmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// 编译片段着色器
	glCompileShader(fragmentShader);

	// 检查着色器是否出错
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave

		HG_CORE_ERROR("{0}", infoLog.data());
		HG_CORE_ASSERT(false,"fragment shader compilation failure!")
		return;
	}

	//	顶点着色器和片段着色器都有效，我们可以生成程序了
	// Now time to link them together into a program.
	// Get a program object.
	m_RendererID = glCreateProgram();
	GLint program = m_RendererID;

	//	将着色器附加进程序
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// 链接到程序
	glLinkProgram(program);

	// 检查程序是否成功
	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave
		return;
	}

	// 分离已经成功链接到的着色器
	// Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
}

hg::Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void hg::Shader::bind()
{
	glUseProgram(m_RendererID);
}

void hg::Shader::unbind()
{
	glUseProgram(0);
}
