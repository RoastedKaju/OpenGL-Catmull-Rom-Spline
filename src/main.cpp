#include <GLFW/glfw3.h>
#include <iostream>

void ProcessInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int main() {

  if (glfwInit() != GLFW_TRUE) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // Window
  GLFWwindow* window = glfwCreateWindow(800, 600, "Catmull-Rom Splines", nullptr, nullptr);
  if (!window) {
    std::cout << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  glOrtho(0, 800, 0, 600, -1, 1);

  while (!glfwWindowShouldClose(window)) {
    ProcessInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(400.0f, 300.0f);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  std::cout << "Shutting down..." << std::endl;
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}