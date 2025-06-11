#define STB_IMAGE_IMPLEMENTATION
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "renderer/camera.hpp"
#include "renderer/resourceManager.hpp"
#include "entities/player.hpp"
#include "Timer.hpp"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 30.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
	#ifdef NDEBUG
    	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Debug", nullptr, nullptr);
	#else
		GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", nullptr, nullptr);
 	#endif

	glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	ResourceManager::instance()->loadTexture("../src/res/wall.jpg", "TestTexture");
	ResourceManager::instance()->loadShader("../src/res/default", "default");

	Player player(glm::vec2(100, 100), *ResourceManager::instance()->getShader("default"), *ResourceManager::instance()->getTexture("TestTexture"));
	
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection;
	projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f ,(float)SCREEN_HEIGHT, -10.0f, 100.0f);
	glfwSwapInterval(1);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    // glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//
    while (!glfwWindowShouldClose(window))
    {
		float currentFrame = (float)(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        glfwPollEvents();

		glClearColor(0.2f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.GetViewMatrix();
		player.draw(view, projection);
        
		glfwSwapBuffers(window);
    }
	
	ResourceManager::instance()->deleteTexture("TestTexture");
	ResourceManager::instance()->deleteShader("default");

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
    }
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		camera.Zoom--;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
//
// void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
// {
// 	float xpos = (float)(xposIn);
// 	float ypos = (float)(yposIn);
//
// 	if (firstMouse) {
// 		lastX = xpos;
// 		lastY = ypos;
// 		firstMouse = false;
// 	}
//
// 	float xoffset = xpos - lastX;
// 	float yoffset = ypos - lastY;
//
// 	lastX = xpos;
// 	lastY = ypos;
//
// 	camera.ProcessMouseMovement(xoffset, yoffset);
// }
//
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
// 	camera.ProcessMouseScroll((float)(yoffset));
// }
