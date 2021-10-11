#pragma once

#include <vanadium/core/interfaces/EventProvider.h>
#include <vanadium/core/types/Reference.h>

#include "Model.h"

class Controller {
 private:
  vanadium::Ref<Model> _model = nullptr;
  vanadium::Ref<vanadium::EventProvider> _eventProvider = nullptr;

 public:
  Controller(vanadium::Ref<Model> model,
             vanadium::Ref<vanadium::EventProvider> eventProvider);

  void update(double deltatime);

  void onMouseMove();
};
