#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


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

int main(void)
{
    GLFWwindow* pWindow;

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit() failed \n";
        return -1;
    }        

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(windowsSizeX, windowsSizeY, "Battle-game", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "Init pointer pWindow failed. glfwCreateWindow() function failed\n";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack); /// what?????
    glfwSetKeyCallback(pWindow, glfwKeyCallBack);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL())
	{
		std::cout<<"Can't load GLAD\n";
		return -1;
	}

    std::cout << "Renderer: " << glGetString(GL_RENDERER)<<";\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << ";\n";

	glClearColor(1,1,0,1);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}