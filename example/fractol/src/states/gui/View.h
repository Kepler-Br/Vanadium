#pragma once

#include <core/Types.h>

#include "Model.h"

class View {
 private:
  vanadium::Ref<Model> _model = nullptr;

 public:
  explicit View(vanadium::Ref<Model> model);

  void draw();
};