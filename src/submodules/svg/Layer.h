#ifndef VANADIUM_LAYER_H
#define VANADIUM_LAYER_H

#include "Path.h"

namespace vanadium::svg {

class Layer {
 private:
  std::vector<Path *> _paths;
  std::string _name;

 public:
  Layer(std::string name, std::vector<Path *> paths)
      : _name(std::move(name)), _paths(std::move(paths)) {}

  ~Layer() {
    for (auto *path : _paths) {
      delete path;
    }
  }

  const std::string &getName() const { return this->_name; }

  [[nodiscard]] Path *getPathById(size_t id) const {
    if (id >= this->_paths.size()) return nullptr;
    return this->_paths[id];
  }

  size_t getTotalPaths() const { return this->_paths.size(); }

  const std::vector<Path *> &getPaths() const { return this->_paths; }
};

}  // namespace vanadium::svg

#endif  // VANADIUM_LAYER_H
