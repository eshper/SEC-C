#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Model.h"

// Constants
const int WIDTH = 1200;
const int HEIGHT = 1200;
const int FPS = 60;
const std::chrono::duration<double, std::milli> FRAME_DURATION(1000.0 / FPS);

// Function prototypes
const char *getError();
inline void startUpGLFW();
inline void startUpGLEW();
inline GLFWwindow *setUp();

int main()
{
  GLFWwindow *window;
  try
  {
    window = setUp();
  }
  catch (const char *error)
  {
    std::cout << error << std::endl;
    std::cout << "The error is over here!" << std::endl;
    throw;
  }

  Shader shader("vertexShader.glsl", "fragmentShader.glsl");
  // Model backpack("./Models/backpack/backpack.obj");
  // Model glass("./Models/glass/glass.glb");
  // Model table("./Models/table/round_table.obj");
  Model walls("./Models/walls/walls.obj");

  glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
  glm::vec3 lightPos(3.0f, 3.0f, 3.0f);
  glm::mat4 lightModel(1.0f);
  lightModel = glm::translate(lightModel, lightPos);

  glm::vec3 objectPos(0.0f, 0.0f, 0.0f);
  glm::mat4 objectModel(1.0f);
  objectModel = glm::translate(objectModel, objectPos);

  shader.Activate();
  glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
  glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));

  glEnable(GL_DEPTH_TEST);

  Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

  while (!glfwWindowShouldClose(window))
  {
    // start the frame timer
    auto frameStart = std::chrono::high_resolution_clock::now();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.Inputs(window); // Handle camera inputs
    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    // backpack.Draw(shader, camera);
    // glass.Draw(shader, camera);
    // table.Draw(shader, camera);
    walls.Draw(shader, camera);

    glfwSwapBuffers(window); // Swap the front and back buffers
    glfwPollEvents();        // Poll for and process events

    /* Input Handling */
    /* -------------- */

    // Wait for the next frame
    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto frameTime = frameEnd - frameStart;
    if (frameTime < FRAME_DURATION)
    {
      std::this_thread::sleep_for(FRAME_DURATION - frameTime);
    }
  }

  // Cleanup
  shader.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

const char *getError()
{
  const char *errorDescription;
  glfwGetError(&errorDescription);
  return errorDescription;
}

inline void startUpGLFW()
{
  glewExperimental = true; // Needed for core profile
  if (!glfwInit())
  {
    throw getError();
  }
}

inline void startUpGLEW()
{
  glewExperimental = true; // Needed in core profile
  if (glewInit() != GLEW_OK)
  {
    glfwTerminate();
    throw getError();
  }
}

inline GLFWwindow *setUp()
{
  startUpGLFW();
  glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
  GLFWwindow *window;                                            // (In the accompanying source code, this variable is global for simplicity)
  window = glfwCreateWindow(WIDTH, HEIGHT, "SEC-C", NULL, NULL);
  if (window == NULL)
  {
    std::cout << getError() << std::endl;
    glfwTerminate();
    throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
  }
  glfwMakeContextCurrent(window); // Initialize GLEW
  startUpGLEW();
  return window;
}
