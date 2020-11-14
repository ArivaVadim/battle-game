#include "shader_program.h"

ShaderProgram::ShaderProgram(const GLchar* vertex_shader_program, const GLchar* fragment_shader_program)
{
    if (!initShader(vertex_shader, GL_VERTEX_SHADER, vertex_shader_program))
        return;

    if (!initShader(fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_program))
    {
        glDeleteShader(vertex_shader);
        return;
    }

    if (!linkProgram(program, vertex_shader, fragment_shader))
    {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

ShaderProgram ::~ShaderProgram()
{
    glDeleteProgram(program);
}


bool ShaderProgram::initShader(GLuint& shader,const GLenum type, const GLchar* shader_program)
{
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_program, nullptr);
    glCompileShader(shader);
    
    GLint isCompile;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompile);

    if (isCompile == NULL)
    {
        GLchar logInfo[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, logInfo);
        std::cerr << "ERROR::ShaderProgramm::initShader();\n";
        return false;
    }
    return true;
}

bool ShaderProgram::linkProgram(GLuint& program, const GLuint& shader1, const GLuint& shader2)
{
    program = glCreateProgram();
    glAttachShader(program, shader1);
    glAttachShader(program, shader2);
    glLinkProgram(program);

    GLint isLink;
    glGetShaderiv(program, GL_LINK_STATUS, &isLink);

    if (isLink == NULL)
    {
        GLchar logInfo[1024];
        glGetShaderInfoLog(program, 1024, nullptr, logInfo);
        std::cerr << "ERROR::ShaderProgramm::linkProgram();\n";
        return false;
    }
    return true;
}

void ShaderProgram::use() const
{
    glUseProgram(program);
}
