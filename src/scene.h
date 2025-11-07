#ifndef SPLINES_SCENE_H
#define SPLINES_SCENE_H

#include "common.h"
#include "spline.h"

class Scene {
public:
  Scene();
  ~Scene();

  void Render();

  [[nodiscard]]
  inline const std::unique_ptr<Spline>& GetSpline() const { return spline; };

private:
  std::unique_ptr<Spline> spline;
};

#endif