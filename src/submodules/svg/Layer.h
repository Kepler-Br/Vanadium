#ifndef VANADIUM_LAYER_H
#define VANADIUM_LAYER_H

#include "Path.h"

namespace Vanadium::Svg {

class Layer {
 private:
  std::vector<Path *> paths;
  std::string name;

 public:
  Layer(std::string name, std::vector<Path *> paths)
      : name(std::move(name)), paths(std::move(paths)) {}

  ~Layer() {
    for (auto *path : paths) {
      delete path;
    }
  }

  const std::string &getName() const { return this->name; }

  [[nodiscard]] Path *getPathById(size_t id) const {
    if (id >= this->paths.size()) return nullptr;
    return this->paths[id];
  }

  size_t getTotalPaths() const { return this->paths.size(); }

  const std::vector<Path *> &getPaths() const { return this->paths; }
};

}  // namespace Vanadium

#endif  // VANADIUM_LAYER_H
