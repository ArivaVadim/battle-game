#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Rendering/shader_program.h"
#include "Resources/resources_manager.h"

GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat color[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

int windowsSizeX = 640;
int windowsSizeY = 480;

void glfwWindowSizeCallBack(GLFWwindow* pWindow, int sizeX, int sizeY)
{
    windowsSizeX = sizeX;
    windowsSizeY = sizeY;
    glViewport(0,0, windowsSizeX, windowsSizeY);
}

void glfwKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(int argc, char** argv)
{
    GLFWwindow* pWindow;

    if (!glfwInit())
    {
        std::cerr << "ERROR::glfwInit() failed \n";
        return -1;
    }        

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(windowsSizeX, windowsSizeY, "Battle-game", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "Init pointer pWindow failed. glfwCreateWindow() function failed\n";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack); 
    glfwSetKeyCallback(pWindow, glfwKeyCallBack);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL())
	{
        std::cerr << "ERROR::Can't load GLAD\n";
		return -1;
	}

    std::cout << "Renderer: " << glGetString(GL_RENDERER)<<";\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << ";\n";

	glClearColor(1,1,0.5,1);

    {
        ResourcesManager resources_manager(argv[0]);
        auto p_default_shader_program = resources_manager.loadShaders("default_shaders", "resources/shaders/vertex.txt", "resources/shaders/fragment.txt");
        if (!p_default_shader_program)
        {
            std::cerr << "ERROR::main()::resources_manager.loadShaders() - Can't create shader program;\n";
            return -1;
        }

        GLuint points_buffer = 0;
        glGenBuffers(1, &points_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, points_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_buffer = 0;
        glGenBuffers(1, &colors_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

        GLuint vertex_array = 0;
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            p_default_shader_program->useShaderProgram();
            glBindVertexArray(vertex_array);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    
    glfwTerminate();
    return 0;
}