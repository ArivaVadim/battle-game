#include "shader_program.h"


ShaderProgram::ShaderProgram()
{

}

ShaderProgram ::~ShaderProgram()
{
}

GLuint ShaderProgram::getShader()
{
    return shader;
}

bool ShaderProgram::initShader(const GLenum type, const GLchar* shader_program)
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
        std::cerr << "ERROR::RENDERING::ShaderProgramm::initShader\n";
        return false;
    }
    return true;
}
