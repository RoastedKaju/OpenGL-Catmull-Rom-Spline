#include "scene.h"

Scene::Scene() {
  std::cout << "Initializing scene..." << std::endl;
  spline = std::make_unique<Spline>();
}

Scene::~Scene() { std::cout << "Destroying scene..." << std::endl; }

void Scene::Render() {
  // Set point size and color
  glPointSize(8.0f);
  glColor3f(1.0f, 0.0f, 0.0f);

  glBegin(GL_POINTS);
  for (const auto &point : spline->GetPoints()) {
    glVertex2f(point.x, point.y);
  }
  glEnd();

  // Curve
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= spline->GetSampleCount(); ++i) {
    float t = static_cast<float>(i) / spline->GetSampleCount();
    Point p = spline->GetPointOnSpline(t, false);
    glVertex2f(p.x, p.y);
  }
  glEnd();
}
