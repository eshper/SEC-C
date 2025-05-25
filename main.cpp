#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Model.h"

const int WIDTH = 1200;
const int HEIGHT = 1200;
const int FPS = 60;
const std::chrono::duration<double, std::milli> FRAME_DURATION(1000.0 / FPS);

struct PointLight {
  glm::vec3 position;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float constant;
  float linear;
  float quadratic;
};

const char *getError();
GLFWwindow *initializeOpenGL();
void setupShaderUniforms(Shader &shader,
                         const std::vector<PointLight> &pointlights);
void setupGlassShader(Shader &glassShader, const glm::vec4 &lightColor,
                      const glm::vec3 &lightPos, Camera &camera);

int main() {
  GLFWwindow *window;
  try {
    window = initializeOpenGL();
  } catch (const char *error) {
    std::cerr << "Initialization error: " << error << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  Shader shader("vertexShader.glsl", "fragmentShader.glsl");
  Shader simpleDepthShader("simpleVertexDepthShader.glsl",
                           "simpleFragmentDepthShader.glsl");
  Shader glassShader("vertexShader.glsl", "glassFragmentShader.glsl");

  Model walls("./Models/walls/walls.obj");
  Model glass("./Models/glass/glass.obj");
  Model table("./Models/table/round_table.obj");
  Model floor("./Models/floor/floor.obj");

  std::vector<PointLight> pointlights;

  PointLight pointLight1;
  pointLight1.position = glm::vec3(49.156f, 3.4302f, 13.753f);
  pointLight1.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight1.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight1.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight1.constant = 1.0f;
  pointLight1.linear = 0.014f;
  pointLight1.quadratic = 0.032f;
  pointlights.push_back(pointLight1);

  PointLight pointLight2;
  pointLight2.position = glm::vec3(45.783f, 3.4302f, -24.184f);
  pointLight2.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight2.diffuse = glm::vec3(2.6f, 2.8f, 2.0f);
  pointLight2.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight2.constant = 1.0f;
  pointLight2.linear = 0.014f;
  pointLight2.quadratic = 0.032f;
  pointlights.push_back(pointLight2);

  PointLight pointLight3;
  pointLight3.position = glm::vec3(35.887f, 3.4302f, -24.184f);
  pointLight3.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight3.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight3.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight3.constant = 1.0f;
  pointLight3.linear = 0.014f;
  pointLight3.quadratic = 0.032f;
  pointlights.push_back(pointLight3);

  PointLight pointLight4;
  pointLight4.position = glm::vec3(24.71f, 3.4302f, -24.184f);
  pointLight4.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight4.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight4.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight4.constant = 1.0f;
  pointLight4.linear = 0.014f;
  pointLight4.quadratic = 0.032f;
  pointlights.push_back(pointLight4);

  PointLight pointLight5;
  pointLight5.position = glm::vec3(14.732f, 3.4302f, -24.184f);
  pointLight5.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight5.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight5.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight5.constant = 1.0f;
  pointLight5.linear = 0.014f;
  pointLight5.quadratic = 0.032f;
  pointlights.push_back(pointLight5);

  PointLight pointLight6;
  pointLight6.position = glm::vec3(3.6975f, 3.4302f, -24.184f);
  pointLight6.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight6.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight6.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight6.constant = 1.0f;
  pointLight6.linear = 0.014f;
  pointLight6.quadratic = 0.032f;
  pointlights.push_back(pointLight6);

  PointLight pointLight7;
  pointLight7.position = glm::vec3(-6.0746f, 3.4302f, -24.184f);
  pointLight7.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight7.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight7.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight7.constant = 1.0f;
  pointLight7.linear = 0.014f;
  pointLight7.quadratic = 0.032f;
  pointlights.push_back(pointLight7);

  PointLight pointLight8;
  pointLight8.position = glm::vec3(-17.342f, 3.4302f, -24.184f);
  pointLight8.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight8.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight8.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight8.constant = 1.0f;
  pointLight8.linear = 0.014f;
  pointLight8.quadratic = 0.032f;
  pointlights.push_back(pointLight8);

  PointLight pointLight9;
  pointLight9.position = glm::vec3(-27.143f, 3.4302f, -24.184f);
  pointLight9.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight9.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight9.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight9.constant = 1.0f;
  pointLight9.linear = 0.014f;
  pointLight9.quadratic = 0.032f;
  pointlights.push_back(pointLight9);

  PointLight pointLight10;
  pointLight10.position = glm::vec3(-38.407f, 3.4302f, -24.184f);
  pointLight10.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight10.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight10.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight10.constant = 1.0f;
  pointLight10.linear = 0.014f;
  pointLight10.quadratic = 0.032f;
  pointlights.push_back(pointLight10);

  PointLight pointLight11;
  pointLight11.position = glm::vec3(-48.057f, 3.4302f, -24.184f);
  pointLight11.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight11.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight11.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight11.constant = 1.0f;
  pointLight11.linear = 0.014f;
  pointLight11.quadratic = 0.032f;
  pointlights.push_back(pointLight11);

  PointLight pointLight12;
  pointLight12.position = glm::vec3(39.539f, 3.4302f, 13.753f);
  pointLight12.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight12.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight12.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight12.constant = 1.0f;
  pointLight12.linear = 0.014f;
  pointLight12.quadratic = 0.032f;
  pointlights.push_back(pointLight12);

  PointLight pointLight13;
  pointLight13.position = glm::vec3(28.277f, 3.4302f, 13.753f);
  pointLight13.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight13.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight13.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight13.constant = 1.0f;
  pointLight13.linear = 0.014f;
  pointLight13.quadratic = 0.032f;
  pointlights.push_back(pointLight13);

  PointLight pointLight14;
  pointLight14.position = glm::vec3(18.542f, 3.4302f, 13.753f);
  pointLight14.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight14.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight14.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight14.constant = 1.0f;
  pointLight14.linear = 0.014f;
  pointLight14.quadratic = 0.032f;
  pointlights.push_back(pointLight14);

  PointLight pointLight15;
  pointLight15.position = glm::vec3(7.2412f, 3.4302f, 13.753f);
  pointLight15.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight15.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight15.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight15.constant = 1.0f;
  pointLight15.linear = 0.014f;
  pointLight15.quadratic = 0.032f;
  pointlights.push_back(pointLight15);

  PointLight pointLight16;
  pointLight16.position = glm::vec3(-2.586f, 3.4302f, 13.753f);
  pointLight16.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight16.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight16.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight16.constant = 1.0f;
  pointLight16.linear = 0.014f;
  pointLight16.quadratic = 0.032f;
  pointlights.push_back(pointLight16);

  PointLight pointLight17;
  pointLight17.position = glm::vec3(-13.619f, 3.4302f, 13.753f);
  pointLight17.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight17.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight17.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight17.constant = 1.0f;
  pointLight17.linear = 0.014f;
  pointLight17.quadratic = 0.032f;
  pointlights.push_back(pointLight17);

  PointLight pointLight18;
  pointLight18.position = glm::vec3(-23.528f, 3.4302f, 13.753f);
  pointLight18.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight18.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight18.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight18.constant = 1.0f;
  pointLight18.linear = 0.014f;
  pointLight18.quadratic = 0.032f;
  pointlights.push_back(pointLight18);

  PointLight pointLight19;
  pointLight19.position = glm::vec3(-34.792f, 3.4302f, 13.753f);
  pointLight19.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight19.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight19.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight19.constant = 1.0f;
  pointLight19.linear = 0.014f;
  pointLight19.quadratic = 0.032f;
  pointlights.push_back(pointLight19);

  PointLight pointLight20;
  pointLight20.position = glm::vec3(-44.688f, 3.4302f, 13.753f);
  pointLight20.ambient = glm::vec3(3.8f, 3.8f, 3.8f);
  pointLight20.diffuse = glm::vec3(4.0006f, 4.0006f, 4.0006f);
  pointLight20.specular = glm::vec3(8.0f, 8.0f, 8.0f);
  pointLight20.constant = 1.0f;
  pointLight20.linear = 0.014f;
  pointLight20.quadratic = 0.032f;
  pointlights.push_back(pointLight20);

  const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
  unsigned int depthMapFBO;
  glGenFramebuffers(1, &depthMapFBO);

  unsigned int depthMap;
  glGenTextures(1, &depthMap);
  glBindTexture(GL_TEXTURE_2D, depthMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH,
               SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float borderColor[] = {1.0, 1.0, 1.0, 1.0};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                         depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  setupShaderUniforms(shader, pointlights);
  glm::vec3 directionalLightDirection(-0.2f, -1.0f, -0.3f);
  // glm::vec3 directionalLightDirection(0.2f, -1.0f, -0.3f);
  // glm::vec3 directionalLightDirection(0.2f, 1.0f, -0.3f);

  Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

  // Glass specific code
  glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
  glm::vec3 objectPos(0.0f, 0.0f, 0.0f);
  glm::vec3 lightPos(0.0f, 0.0f, 3.0f);
  setupGlassShader(glassShader, lightColor, lightPos, camera);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!glfwWindowShouldClose(window)) {
    auto frameStart = std::chrono::high_resolution_clock::now();

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.Inputs(window);
    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 7.5f;

    glm::vec3 lightPosition = -directionalLightDirection * 5.0f;
    lightProjection =
        glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView =
        glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    simpleDepthShader.Activate();
    glUniformMatrix4fv(
        glGetUniformLocation(simpleDepthShader.ID, "lightSpaceMatrix"), 1,
        GL_FALSE, glm::value_ptr(lightSpaceMatrix));

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    glm::mat4 wallsModel = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.ID, "model"), 1,
                       GL_FALSE, glm::value_ptr(wallsModel));
    walls.Draw(simpleDepthShader, camera);
    table.Draw(simpleDepthShader, camera);
    floor.Draw(simpleDepthShader, camera);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.Activate();

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1,
                       GL_FALSE, glm::value_ptr(camera.camMatrix));

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE,
                       glm::value_ptr(wallsModel));

    glUniform3f(glGetUniformLocation(shader.ID, "directionalLight.direction"),
                directionalLightDirection.x, directionalLightDirection.y,
                directionalLightDirection.z);
    glUniform3f(glGetUniformLocation(shader.ID, "directionalLight.ambient"),
                0.1f, 0.1f, 0.1f);

    // glUniform3f(glGetUniformLocation(shader.ID, "directionalLight.diffuse"),
    //             7.5f, 7.5f, 7.5f);
    glUniform3f(glGetUniformLocation(shader.ID, "directionalLight.diffuse"),
                1.5f, 1.5f, 1.5f);

    // glUniform3f(glGetUniformLocation(shader.ID, "directionalLight.specular"),
    //             1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shader.ID, "directionalLight.specular"),
                1.0f, 1.0f, 1.0f);

    glUniform1i(glGetUniformLocation(shader.ID, "numberOfPointLights"),
                static_cast<int>(pointlights.size()));

    for (size_t i = 0; i < pointlights.size(); ++i) {
      std::string base = "pointlights[" + std::to_string(i) + "]";
      glUniform3f(glGetUniformLocation(shader.ID, (base + ".position").c_str()),
                  pointlights[i].position.x, pointlights[i].position.y,
                  pointlights[i].position.z);
      glUniform3f(glGetUniformLocation(shader.ID, (base + ".ambient").c_str()),
                  pointlights[i].ambient.x, pointlights[i].ambient.y,
                  pointlights[i].ambient.z);
      glUniform3f(glGetUniformLocation(shader.ID, (base + ".diffuse").c_str()),
                  pointlights[i].diffuse.x, pointlights[i].diffuse.y,
                  pointlights[i].diffuse.z);
      glUniform3f(glGetUniformLocation(shader.ID, (base + ".specular").c_str()),
                  pointlights[i].specular.x, pointlights[i].specular.y,
                  pointlights[i].specular.z);
      glUniform1f(glGetUniformLocation(shader.ID, (base + ".constant").c_str()),
                  pointlights[i].constant);
      glUniform1f(glGetUniformLocation(shader.ID, (base + ".linear").c_str()),
                  pointlights[i].linear);
      glUniform1f(
          glGetUniformLocation(shader.ID, (base + ".quadratic").c_str()),
          pointlights[i].quadratic);
    }

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x,
                camera.Position.y, camera.Position.z);
    glUniform1f(glGetUniformLocation(shader.ID, "shine"), 32.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "lightSpaceMatrix"), 1,
                       GL_FALSE, glm::value_ptr(lightSpaceMatrix));

    glActiveTexture(GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    walls.Draw(shader, camera);
    table.Draw(shader, camera);
    floor.Draw(shader, camera);

    glDepthMask(GL_FALSE);
    glass.Draw(glassShader, camera);
    glDepthMask(GL_TRUE);

    glfwSwapBuffers(window);
    glfwPollEvents();

    auto frameEnd = std::chrono::high_resolution_clock::now();
    auto frameTime = frameEnd - frameStart;
    if (frameTime < FRAME_DURATION) {
      std::this_thread::sleep_for(FRAME_DURATION - frameTime);
    }
  }

  shader.Delete();
  simpleDepthShader.Delete();
  glassShader.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

const char *getError() {
  const char *errorDescription;
  glfwGetError(&errorDescription);
  return errorDescription;
}

void setupShaderUniforms(Shader &shader,
                         const std::vector<PointLight> &pointlights) {
  shader.Activate();

  glUniform1i(glGetUniformLocation(shader.ID, "diffuse0"), 0);
  glUniform1i(glGetUniformLocation(shader.ID, "specular0"), 0);
  glUniform1i(glGetUniformLocation(shader.ID, "shadowMap"), 1);
}

void setupGlassShader(Shader &glassShader, const glm::vec4 &lightColor,
                      const glm::vec3 &lightPos, Camera &camera) {
  glassShader.Activate();
  glUniformMatrix4fv(glGetUniformLocation(glassShader.ID, "camMatrix"), 1,
                     GL_FALSE, glm::value_ptr(camera.camMatrix));
  glUniform3f(glGetUniformLocation(glassShader.ID, "lightPos"), lightPos.x,
              lightPos.y, lightPos.z);
  glUniform4f(glGetUniformLocation(glassShader.ID, "lightColor"), lightColor.r,
              lightColor.g, lightColor.b, lightColor.a);
  glUniform3f(glGetUniformLocation(glassShader.ID, "glassColor"), 0.8f, 0.9f,
              1.0f);
  glUniform1f(glGetUniformLocation(glassShader.ID, "transparency"), 0.4f);

  glm::mat4 glassModel =
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(glGetUniformLocation(glassShader.ID, "model"), 1, GL_FALSE,
                     glm::value_ptr(glassModel));
}

GLFWwindow *initializeOpenGL() {
  if (!glfwInit()) {
    throw getError();
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "SEC-C", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    throw "Failed to create GLFW window. Your GPU may not support OpenGL 3.3.";
  }

  glfwMakeContextCurrent(window);

  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    glfwDestroyWindow(window);
    glfwTerminate();
    throw "Failed to initialize GLEW.";
  }

  return window;
}
