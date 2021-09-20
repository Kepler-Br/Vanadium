#include "Controller.h"

#include <utility>

Controller::Controller(
    vanadium::Ref<Model> model,
    vanadium::Ref<vanadium::UserEndEventProvider> eventProvider)
    : _model(std::move(model)), _eventProvider(std::move(eventProvider)) {}

void Controller::update(double deltatime) {
  this->_model->update(deltatime);
}

void Controller::onMouseMove() {}
