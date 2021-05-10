#ifndef VANADIUM_RESOURCEMANAGER_H
#define VANADIUM_RESOURCEMANAGER_H

#include <fmt/format.h>

#include <future>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "Assert.h"
#include "Types.h"

namespace Vanadium {

class ResourceLoader;

class ResourceManagerException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

class Resource {
 protected:
  Resource(std::string newName, std::size_t newId, std::size_t newTypeId)
      : name(std::move(newName)), id(newId), typeId(newTypeId) {}

 public:


  [[nodiscard]] const std::string &getName() const { return this->name; }

  [[nodiscard]] std::size_t getId() const { return this->id; }

  [[nodiscard]] std::size_t getTypeId() const { return this->typeId; }

  [[nodiscard]] virtual bool isNull() const { return false; }

 protected:
  std::string name;
  std::size_t id;
  std::size_t typeId;

};

class NullResource : public Resource {
 public:
  NullResource(const std::string &newName, std::size_t newId,
               std::size_t newTypeId)
      : Resource(newName, newId, newTypeId) {}

  [[nodiscard]] bool isNull() const override { return true; }
};

//class ResourceRequest {
// public:
//  enum class Status { NOT_LOADED = 0, LOADING, READY };
//
//  ResourceRequest(Status newStatus,
//                  ResourceContainer::iterator resourceIterator)
//      : status(newStatus), resourceIterator(resourceIterator){};
//
//  Status getStatus() { return this->status; }
//
//  Ref<Resource> get() {
//    while (this->resourceIterator->second->isNull()) {
//      VAN_ENGINE_INFO("Resource is being loading");
//    }
//    return this->resourceIterator->second;
//  }
//
// private:
//  Status status;
//  ResourceContainer::iterator resourceIterator;
//
//};

class ResourceBuilder {
 public:
  virtual ~ResourceBuilder() = default;

  virtual void prepare(Ref<Resource> resource) = 0;
  virtual Ref<Resource> build() = 0;
};

using ResourceContainer = std::unordered_map<std::size_t, Ref<Resource>>;
using ResourceContainerIter = ResourceContainer::iterator;
using ResourceFuture = std::future<Ref<Resource>>;
using ResourceBuilderFuture = std::future<Ref<ResourceBuilder>>;

class ResourceRequest {
 public:
  explicit ResourceRequest(ResourceBuilderFuture newResourceBuilderFuture)
      : resourceBuilderFuture(std::move(newResourceBuilderFuture)) {}

  bool isReady() {
    using namespace std;

    std::future_status status = this->resourceBuilderFuture.wait_for(0s);
    if (status == std::future_status::deferred ||
        status == std::future_status::ready) {
      return true;
    }
    return false;
  }

  Ref<Resource> get() {
    Ref<ResourceBuilder> resourceBuilder = this->resourceBuilderFuture.get();

  }

 protected:
  ResourceBuilderFuture resourceBuilderFuture;

};

class ResourceLoader {
 public:
  virtual ~ResourceLoader() = default;

  // Step 1. Async. DO NOT CALL RENDER HERE. Load from disk.
  virtual UniqueRef<ResourceBuilder> prepare(
      ResourceContainerIter resourceIterator) = 0;
  // Step 2. Sync. Upload stuff to GPU.
  virtual Ref<Resource> load(ResourceContainerIter resourceIterator) = 0;

};

class ResourceGroup {
 public:
  explicit ResourceGroup(std::string newName) : name(std::move(newName)) {}

  std::size_t getTotalResources() const { return this->resources.size(); }

  void addResource(std::size_t resourceId) {
    this->resources.emplace(resourceId);
  }

  void removeResource(std::size_t resourceId) {
    this->resources.erase(resourceId);
  }

  const std::unordered_set<std::size_t> &getResourceList() const {
    return this->resources;
  }

 protected:
  std::string name;
  std::unordered_set<std::size_t> resources;

};

class ResourceManager {
 protected:
  const std::string defaultGroup = "General";

  ResourceContainer resources;
  std::unordered_map<std::string, std::size_t> typeMap;
  std::unordered_map<std::size_t, UniqueRef<ResourceLoader>> loaders;
  std::unordered_map<std::string, ResourceGroup> groups;

  std::hash<std::string> stringHasher = std::hash<std::string>{};

 public:
  ResourceManager() {
    this->createGroup(this->defaultGroup);
  }

  void createGroup(const std::string &groupName) {
    if (this->groups.find(groupName) != this->groups.end()) {
      throw ResourceManagerException(fmt::format(
          "Group with name \"{}\" already exists.", groupName));
    }
    this->groups.emplace(groupName, ResourceGroup(groupName));
  }
//  void loadGroup(const std::string &groupName,
//                 const std::function<void()> &callback = nullptr) {
//    if (groups.find(groupName) == groups.end()) {
//      VAN_ASSERT(false, "Cannot load group that does not exists.");
//      VAN_ENGINE_ERROR("Cannot load group that does not exists.");
//      return;
//    }
//  }

//  void destroyGroup(const std::string &groupName);

  void registerLoader(const std::string &typeName, UniqueRef<ResourceLoader> loader) {
    const std::size_t typeHash = this->stringHasher(typeName);

    this->loaders.emplace(typeHash, std::move(loader));
    this->typeMap.emplace(typeName, typeHash);
  }

  ResourceFuture getResource(std::size_t resourceId) {
    auto resourceIterator = this->resources.find(resourceId);

    if (resourceIterator == this->resources.end()) {
      throw ResourceManagerException(fmt::format(
          "Cannot find resource with id \"{}\".", resourceId));
    }

    std::size_t typeId = resourceIterator->second->getTypeId();
    auto loaderIterator = this->loaders.find(typeId);
    if (loaderIterator == this->loaders.end()) {
      throw ResourceManagerException(fmt::format(
          "Type with id \"{}\" is not registered.", typeId));
    }

    return std::async(std::launch::deferred, &ResourceLoader::load,
                      loaderIterator->second.get(), resourceIterator);
  }

  std::size_t addResource(const std::string &name, const std::string &groupName,
                   const std::string &typeName) {
    std::size_t resourceId = this->stringHasher(name);
    std::size_t typeId = this->stringHasher(typeName);

    if (this->groups.find(groupName) == this->groups.end()) {
      throw ResourceManagerException(fmt::format(
          "Cannot find resource group with name \"{}\".", groupName));
    }
    if (this->loaders.find(typeId) == this->loaders.end()) {
      throw ResourceManagerException(fmt::format(
          "Type with name \"{}\" is not registered.", typeName));
    }
    if (this->resources.find(resourceId) != this->resources.end()) {
      throw ResourceManagerException(fmt::format(
          "Resource with name \"{}\" already exists.", name));
    }

    Ref<Resource> nullResource = MakeRef<NullResource>(name, resourceId, typeId);
    this->resources.emplace(resourceId, nullResource);
    return resourceId;
  }
//  void addManualResource(Ref<Resource> resource, const std::string &groupName);

};
}  // namespace Vanadium

#endif  // VANADIUM_RESOURCEMANAGER_H
