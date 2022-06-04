// JOHN ALEXANDER LE ROUX

// User-Defined Headers
// --------------------
#include "config/config.hpp"
#include "shader/shader.hpp"

// 3rd Party Library Headers
// -------------------------
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;
// stb
#define STB_IMAGE_IMPLEMENTATION
#include "../contrib/stb/stb_image.hpp"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Library Headers
// ------------------------
#include <iostream>



// Shaders
// -------
// Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // The position variable has attribute position 0
"layout(location = 1) in vec3 aColor;\n" // The color variable has attribute position 1
"out vec3 ourColor;\n" // Output a color to the fragment shader
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // See how we directly give a vec3 to vec4's constructor
"   ourColor = aColor;\n"
"}\0";

// Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\0";



// Settings
// --------
// Screen
const unsigned int SCR_WIDTH = 800; // Default 800 or 1024
const unsigned int SCR_HEIGHT = 600; // Default 600 or 768

// Timing
float deltaTime = 0.0f;	// deltaTime is the time between current frame and last frame
float lastFrame = 0.0f;

// Keyboard
bool KeysProcessed[1024];



// Callback functions
// ------------------
// Whenever the window size changes (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
}

// Process all input
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Check if the ESC key was pressed
		glfwSetWindowShouldClose(window, true);            // If so, close the window

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // Check if the Q key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    // If so, change draw mode to GL_FILL

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // Check if the E key was pressed
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    // If so, change draw mode to GL_LINE / wireframe

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) // Check if the C key was pressed
		glfwSetClipboardString(NULL, "Hello this is a clipboard test");


	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS))
		glfwSetWindowShouldClose(window, true); // If so, close the window          

	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char* argv[]) {
	// Initialize GLFW
	// ---------------
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Configure GLFW
	glfwWindowHint(GLFW_SAMPLES, 4);                               // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
#endif

	// Create a window with glfw
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3.ShaderClass!", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window. If you have an Intel GPU, they are not 3.3 compatible." << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set the context to be the window and setup any callback functions
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	// Initialize GLAD; Load all OpenGL pointers
	// -----------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Configure global OpenGL state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB); // Use sRGB
	glEnable(GL_MULTISAMPLE); // Enable MSAA multisampling
	glfwSwapInterval(1); // Turn on vsync for smoother rendering and so OpenGL doesn't draw faster than the monitor refresh rate so the program uses 100% CPU and GPU

	// Build and compile our shader program
	Shader ourShader(vertexShaderSource, fragmentShaderSource);
	//Shader ourShader("data/shaders/triangle.vert", "data/shaders/triangle.frag");

	// Setup vertex data
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};



	// Setup VAO and VBO
	// -----------------
	// Vertex Array Object // Vertex Buffer Object
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the Vertex Array Object first, then set vertex buffer(s), and then configure vertex attributes(s)
	glBindVertexArray(VAO);

	// Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// GL_STATIC_DRAW: Data will be modified once and used many times
	// GL_DYNAMIC_DRAW: Data will be modified repeatedly and used many times
	// GL_STREAM_DRAW: Data will be modified once and used at most a few times

	// Then set our vertex attributes pointers
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Please note that we put 6 * sizeof(float) here because we have 3 floats for position and 3 for color
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VAO (It's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);



	// Render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// Per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;



		// Input
		// -----
		processInput(window);



		// Render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // a=x/255 where x is the RGB value and a is your desired result from 0 to 1
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffer

		// Activate shader
		ourShader.use();

		// Bind the triangle VAO
		glBindVertexArray(VAO);

		// Draw the triangle after one second, then after one more second don't draw it, repeat
		static float delay = 0.0f;
		static bool drawTriangle = true;
		if (delay >= 1.0f) { // Wait for ~1.0 second 
			if (drawTriangle == true) {
				drawTriangle = false;
			}
			else {
				drawTriangle = true;
			}
			
			delay = 0.0f; // Reset delay
		}
		delay += deltaTime; // Increase the 'delay' variable each frame
		
		if (drawTriangle == true) {
			glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		}
		
		// Unbind VAO (It's always a good thing to unbind any buffer/array to prevent strange bugs)
		glBindVertexArray(0);



		// Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Clean up
	// --------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW
	glfwTerminate();
	return 0;
}

#ifdef _WIN32 // _WIN32 = Windows32,  _WIN64 = Windows64,  __APPLE__ = MacOS,  __linux__ = Linux,  __ANDROID__ = Android. https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html
#ifndef _DEBUG // Project properties > Linker > System > Subsystem to "Windows" (only for all Release builds) will use WinMain as the start of program and hide the console
#define nominmax
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR szCmdLine, _In_ int iCmdShow) {
	main(__argc, __argv); // __argc, __argv, __wargv: https://docs.microsoft.com/en-us/cpp/c-runtime-library/argc-argv-wargv?view=msvc-170
	//MessageBox(NULL, TEXT("Body Text"), TEXT("Title"), 0);
	return 0;
}
#endif
#endif // Another option to hide window without WinMain: https://stackoverflow.com/questions/18260508/c-how-do-i-hide-a-console-window-on-startup