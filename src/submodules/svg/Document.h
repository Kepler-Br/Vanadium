#ifndef VANADIUM_DOCUMENT_H
#define VANADIUM_DOCUMENT_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Layer.h"
#include "Path.h"

namespace vanadium::svg {

class Document {
 private:
  std::string name;
  glm::vec2 dimensions;
  std::vector<Layer *> layers;
  std::vector<Path *> paths;
  std::vector<commands::Command *> commands;

  std::unordered_map<std::string, Layer *> layersByName;

  void mapLayersByName() {
    for (const auto layer : this->layers) {
      layersByName[layer->getName()] = layer;
    }
  }

  void indexAllPaths() {
    for (const auto layer : this->layers) {
      const std::vector<Path *> &paths = layer->getPaths();
      this->paths.insert(this->paths.end(), paths.begin(), paths.end());
    }
  }

  void indexAllCommands() {
    for (const auto layer : this->layers) {
      for (const auto path : layer->getPaths()) {
        this->commands.insert(this->commands.end(), path->getCommands().begin(),
                              path->getCommands().end());
      }
    }
  }

 public:
  Document(std::string name, glm::vec2 dimensions, std::vector<Layer *> layers)
      : name(std::move(name)),
        dimensions(dimensions),
        layers(std::move(layers)) {
    this->mapLayersByName();
    this->indexAllPaths();
    this->indexAllCommands();
  }

  [[nodiscard]] const glm::vec2 &getDimensions() const noexcept {
    return this->dimensions;
  }

  [[nodiscard]] std::string getName() const noexcept { return this->name; }

  [[nodiscard]] const Layer *getLayerByName(
      const std::string &layerName) const {
    auto layer = this->layersByName.find(layerName);

    if (layer == this->layersByName.end()) return {};
    return layer->second;
  }

  [[nodiscard]] const std::vector<Layer *> &getLayers() const {
    return this->layers;
  }

  [[nodiscard]] const std::vector<Path *> &getPaths() const {
    return this->paths;
  }

  [[nodiscard]] const std::vector<commands::Command *> &getCommands() const {
    return this->commands;
  }

  [[nodiscard]] size_t getTotalLayers() const { return this->layers.size(); }

  [[nodiscard]] size_t getTotalPaths() const { return this->paths.size(); }

  [[nodiscard]] size_t getTotalCommands() const {
    return this->commands.size();
  }
};

}  // namespace Vanadium::Svg

#endif  // VANADIUM_DOCUMENT_H
