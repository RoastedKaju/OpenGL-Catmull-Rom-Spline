#include "common.h"
#include "point.h"
#include "scene.h"

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void OnMouseButton(GLFWwindow *window, int button, int action, int mods) {
  const auto *scene = static_cast<Scene *>(glfwGetWindowUserPointer(window));
  if (!scene)
    return;

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Convert GLFW to OpenGL coordinates
    const auto x = static_cast<float>(xpos);
    const auto y = static_cast<float>(height - ypos);

    // Check if hovering over a point
    std::vector<Point>& points = scene->GetSpline()->GetPoints();
    for (auto itr = points.begin(); itr != points.end(); ++itr) {
      const float dx = itr->x - x;
      const float dy = itr->y - y;

      if (dx * dx + dy * dy <= 250.0f) {
        std::cout << "Point removed" << std::endl;
        scene->GetSpline()->RemovePoint(itr);
        scene->GetSpline()->CalculateUnitsPerSample();
        return;
      }
    }

    // Else add the point at location
    scene->GetSpline()->AddPoint({x, y});
    scene->GetSpline()->CalculateUnitsPerSample();
    std::cout << "Point added At x: " << x << " y: " << y << std::endl;
  }
}

int main() {

  if (glfwInit() != GLFW_TRUE) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // Window
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Catmull-Rom Splines", nullptr, nullptr);
  if (!window) {
    std::cout << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  glOrtho(0, 800, 0, 600, -1, 1);

  // Create scene for placing points
  auto *scene = new Scene();

  // GLFW mouse button callback
  glfwSetMouseButtonCallback(window, &OnMouseButton);
  // Set the scene pointer to our main window
  glfwSetWindowUserPointer(window, scene);

  while (!glfwWindowShouldClose(window)) {
    ProcessInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    scene->Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete scene;

  std::cout << "Shutting down..." << std::endl;
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}