#ifndef SPLINES_CONTROLWIDGET_H
#define SPLINES_CONTROLWIDGET_H

#include "common.h"
#include "imgui.h"
#include "spline.h"

class ControlWidget {
public:
  ControlWidget(GLFWwindow* _window, Spline* _spline);
  ~ControlWidget();

  void Init() const;
  void Render();
  [[nodiscard]]
  bool WantToCaptureMouse() const;

private:
  GLFWwindow* window;
  Spline* spline;
};

#endif // SPLINES_CONTROLWIDGET_H
