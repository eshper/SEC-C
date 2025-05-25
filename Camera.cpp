#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
  this->Position = position;
  this->width = width;
  this->height = height;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
  glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up);
  glm::mat4 projection = glm::perspective(
      glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

  camMatrix = projection * view;
}

void Camera::Matrix(Shader &shader, const char *uniform) {
  glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE,
                     glm::value_ptr(camMatrix));
}

void Camera::Inputs(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    Position += speed * Orientation;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    Position -= speed * Orientation;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    Position += glm::normalize(glm::cross(Orientation, Up)) * speed;
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    Position += Up * speed;
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    Position -= Up * speed;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    speed = 0.4f;
  else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    speed = 0.1f;

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (firstClick) {
      glfwSetCursorPos(window, width / 2, height / 2);
      firstClick = false;
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    float rotX = (float)(ypos - width / 2) / (float)width * sensitivity;
    float rotY = (float)(xpos - height / 2) / (float)height * sensitivity;

    glm::vec3 newOrientation =
        glm::rotate(Orientation, glm::radians(-rotX),
                    glm::normalize(glm::cross(Orientation, Up)));
    if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f) ||
          glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))
      Orientation = newOrientation;

    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    glfwSetCursorPos(window, width / 2, height / 2);
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstClick = true;
  }
}
