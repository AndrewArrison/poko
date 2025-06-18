#define STB_IMAGE_IMPLEMENTATION
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "game.hpp"
#include "core/resourceManager.hpp"
#include "entities/player.hpp"
#include "Timer.hpp"
#include "debug.hpp"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Game TestGame(SCREEN_WIDTH, SCREEN_HEIGHT);

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	

	INFO_LOG("OPENGL VERSION : " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
	INFO_LOG("GLFW VERSION : " + std::string(glfwGetVersionString()));
	
	TestGame.Init();

	glfwSwapInterval(1);
    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float currentFrame = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	
	while (!glfwWindowShouldClose(window))
    {
		currentFrame = (float)(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        glfwPollEvents();

		TestGame.ProcessInput(deltaTime);
		TestGame.Update(deltaTime);
		
		glClearColor(0.2f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
		TestGame.Render();

		glfwSwapBuffers(window);
    }
	
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
	if (key >= 0 && key <= 1024) {
		if (action == GLFW_PRESS) {
			TestGame.Keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			TestGame.Keys[key] = false;
		}
	}
	// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
	// // 	camera.ProcessKeyboard(FORWARD, deltaTime);
	// 	// r1.y += 5;
	// }
	// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
	// 	// camera.ProcessKeyboard(BACKWARD, deltaTime);
	// 	// r1.y -= 5;
	// }
	// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
	// // 	camera.ProcessKeyboard(LEFT, deltaTime);
	// 	// r1.x -= 5;
	// }
	// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
	// 	// camera.ProcessKeyboard(RIGHT, deltaTime);
	// 	// r1.x += 5;
	// }
	// if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
	// 	// camera.Zoom--;
	// }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/*
*
* 		NOTES
*
*
* -> dont try put that RDII thing in this project? please
* -> imean DSA hehe ;) RDII thing is already there...
*
*
*/
