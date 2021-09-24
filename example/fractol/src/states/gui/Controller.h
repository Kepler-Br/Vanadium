#pragma once

#include <core/interfaces/EventProvider.h>
#include <core/Types.h>

#include "Model.h"

class Controller {
 private:
  vanadium::Ref<Model> _model = nullptr;
  vanadium::Ref<vanadium::UserEndEventProvider> _eventProvider = nullptr;

 public:
  Controller(vanadium::Ref<Model> model,
             vanadium::Ref<vanadium::UserEndEventProvider> eventProvider);

  void update(double deltatime);

  void onMouseMove();
};
