#pragma once

#include <functional>

template <class T>
class Lerpable {
 private:
  T _value;
  T _lerped;

  float _step;

  std::function<void(T &from, const T &to, float)> _lerpFunction;
  std::function<bool(const T &from, const T &to)> _shouldUpdate = nullptr;
  std::function<void(T &target, const T &value)> _setterFunction =
      [](T &target, const T &other) { target = other; };

 public:
  Lerpable(T value, float step,
           std::function<void(T &from, const T &to, float)> lerpFunction)
      : _value(value),
        _lerped(value),
        _step(step),
        _lerpFunction(lerpFunction) {}

  void setLerpFunction(
      std::function<void(T &from, const T &to, float)> lerpFunction) {
    this->_lerpFunction = lerpFunction;
  }

  void setSetterFunction(
      std::function<void(T &target, const T &value)> setter) {
    this->_setterFunction = setter;
  }

  void setShouldUpdateFunction(
      std::function<void(const T &from, const T &to)> shouldUpdate) {
    this->_shouldUpdate = shouldUpdate;
  }

  void update() {
    if (this->_shouldUpdate == nullptr) {
      this->_lerpFunction(this->_lerped, this->_value, this->_step);
    } else if (this->_shouldUpdate(this->_lerped, this->_value)) {
      this->_lerpFunction(this->_lerped, this->_value, this->_step);
    }
  }

  void update(float deltatime) {
    if (this->_shouldUpdate == nullptr) {
      this->_lerpFunction(this->_lerped, this->_value, this->_step * deltatime);
    } else if (this->_shouldUpdate(this->_lerped, this->_value)) {
      this->_lerpFunction(this->_lerped, this->_value, this->_step * deltatime);
    }
  }

  [[nodiscard]] float getStep() const { return this->_step; }
  void setStep(float step) { this->_step = step; }

  T &getValue() { return this->_value; }
  void setValue(const T &newValue) {
    this->_setterFunction(this->_value, newValue);
  }

  const T &getLerped() const { return this->_lerped; }
  void setLerped(const T &newValue) {
    this->_setterFunction(this->_lerped, newValue);
  }

  void reset() { this->_setterFunction(this->_lerped, this->_value); }
};
