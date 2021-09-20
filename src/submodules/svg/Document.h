#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Layer.h"
#include "Path.h"

namespace vanadium::svg {

class Document {
 private:
  std::string _name;
  glm::vec2 _dimensions;
  std::vector<Layer *> _layers;
  std::vector<Path *> _paths;
  std::vector<commands::Command *> _commands;

  std::unordered_map<std::string, Layer *> _layersByName;

  void mapLayersByName() {
    for (const auto layer : this->_layers) {
      _layersByName[layer->getName()] = layer;
    }
  }

  void indexAllPaths() {
    for (const auto layer : this->_layers) {
      const std::vector<Path *> &paths = layer->getPaths();
      this->_paths.insert(this->_paths.end(), paths.begin(), paths.end());
    }
  }

  void indexAllCommands() {
    for (const auto layer : this->_layers) {
      for (const auto path : layer->getPaths()) {
        this->_commands.insert(this->_commands.end(),
                               path->getCommands().begin(),
                               path->getCommands().end());
      }
    }
  }

 public:
  Document(std::string name, glm::vec2 dimensions, std::vector<Layer *> layers)
      : _name(std::move(name)),
        _dimensions(dimensions),
        _layers(std::move(layers)) {
    this->mapLayersByName();
    this->indexAllPaths();
    this->indexAllCommands();
  }

  [[nodiscard]] const glm::vec2 &getDimensions() const noexcept {
    return this->_dimensions;
  }

  [[nodiscard]] std::string getName() const noexcept { return this->_name; }

  [[nodiscard]] const Layer *getLayerByName(
      const std::string &layerName) const {
    auto layer = this->_layersByName.find(layerName);

    if (layer == this->_layersByName.end()) return {};
    return layer->second;
  }

  [[nodiscard]] const std::vector<Layer *> &getLayers() const {
    return this->_layers;
  }

  [[nodiscard]] const std::vector<Path *> &getPaths() const {
    return this->_paths;
  }

  [[nodiscard]] const std::vector<commands::Command *> &getCommands() const {
    return this->_commands;
  }

  [[nodiscard]] size_t getTotalLayers() const { return this->_layers.size(); }

  [[nodiscard]] size_t getTotalPaths() const { return this->_paths.size(); }

  [[nodiscard]] size_t getTotalCommands() const {
    return this->_commands.size();
  }
};

}  // namespace vanadium::svg
