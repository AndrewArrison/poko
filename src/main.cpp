#define STB_IMAGE_IMPLEMENTATION
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <stb_image.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/ext/vector_float2.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "core/camera.hpp"
#include "core/resourceManager.hpp"
#include "core/renderer.hpp"
#include "physics/phy.hpp"
#include "entities/player.hpp"
#include "Timer.hpp"
#include "debug.hpp"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
// void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec4 r1 = {200, 200, 50, 50};
glm::vec4 r2 = {190, 200, 50, 50};

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
	

	INFO_LOG("OPENGL VERSION : " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
	INFO_LOG("GLFW VERSION : " + std::string(glfwGetVersionString()));
	
	ResourceManager::instance()->loadTexture("../src/res/wall.jpg", "TestTexture");
	ResourceManager::instance()->loadShader("../src/res/default", "default");
	ResourceManager::instance()->loadShader("../src/res/quad", "quad");

	Player player(glm::vec2(300, 150), *ResourceManager::instance()->getShader("default"), *ResourceManager::instance()->getTexture("TestTexture"));

	glm::mat4 projection;
	projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f ,(float)SCREEN_HEIGHT, -1.0f, 1.0f);
	Renderer renderer(projection);
	glm::mat4 view = camera.GetViewMatrix();
	glfwSwapInterval(1);
	float currentFrame = 0.0f;
    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//
    while (!glfwWindowShouldClose(window))
    {
		currentFrame = (float)(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        glfwPollEvents();

		glClearColor(0.2f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		view = camera.GetViewMatrix();
		// Physics::isRectColliding(r1.x, r2.x, r1.y, r2.y, r1.z, r2.z, r1.z, r2.z);
		// player.draw(view, projection);
		// renderer.drawQuad(glm::vec2(200.0f, 200.0f), glm::vec3(0.3f, 0.432f, 0.1f), view, glm::vec2(50.0f, 50.0f));
		// renderer.drawSprite("TestTexture", glm::vec2(251.0f, 251.0f), view, glm::vec2(50.0f, 50.0f));
		
		renderer.drawQuad(glm::vec2(r1.x, r1.y), glm::vec3(0.3f, 0.432f, 0.1f), view, glm::vec2(50.0f, 50.0f));
		renderer.drawSprite("TestTexture", glm::vec2(r2.x, r2.y), view, glm::vec2(50.0f, 50.0f));
		Physics::isRectColliding(r1, r2);

		glfwSwapBuffers(window);
    }
	
	ResourceManager::instance()->deleteTexture("TestTexture");
	ResourceManager::instance()->deleteShader("default");
	ResourceManager::instance()->deleteShader("quad");

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
	// 	camera.ProcessKeyboard(FORWARD, deltaTime);
		r1.y += 5;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		// camera.ProcessKeyboard(BACKWARD, deltaTime);
		r1.y -= 5;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
	// 	camera.ProcessKeyboard(LEFT, deltaTime);
		r1.x -= 5;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		// camera.ProcessKeyboard(RIGHT, deltaTime);
		r1.x += 5;
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
//


/*
*
* 		NOTES
*
*
* -> dont try put that RDII thing in this project? please
*
*
*
*/
