#ifndef VANADIUM_RESOURCEMANAGER_H
#define VANADIUM_RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "Types.h"
#include "Assert.h"

namespace Vanadium
{

class ResourceLoader;

class Resource
{
public:
    enum class Status
    {
        NOT_LOADED = 0,
        LOADING,
        READY
    };

    Resource(std::string newName, std::size_t newId) :
            name(std::move(newName)),
            id(newId)
    {}

    const std::string &getName() {
        return this->name;
    }

    std::size_t getId() {
        return this->id;
    }

    std::size_t getLoaderId() {
        return this->loaderId;
    }

    Status getStatus() {
        return this->status;
    }

protected:
    std::string name;
    std::size_t id;
    std::size_t loaderId;
    Status status = Status::NOT_LOADED;

    friend ResourceLoader;
};

class ResourceLoader
{
public:
    virtual void load(Ref<Resource> resource) = 0;
    virtual Ref<Resource> createEmpty(const std::string &name, std::size_t id) = 0;

};

class ResourceGroup
{
protected:
    std::string name;
    std::unordered_set<std::size_t> resources;

};

class ResourceManager
{
protected:
    const std::string defaultGroup = "General";

    std::unordered_map<std::size_t, Ref<Resource>> resources;
    std::unordered_map<std::size_t, ResourceLoader*> loaders;
    std::unordered_map<std::string, ResourceGroup> groups;

public:
    ResourceManager() = default;

    void createGroup(const std::string &groupName) {
        this->groups.emplace(groupName, ResourceGroup());
    }
    void loadGroup(const std::string &groupName) {
        if (groups.find(groupName) == groups.end()) {
            VAN_ASSERT(false, "Cannot load group that does not exists.");
            VAN_ENGINE_ERROR("Cannot load group that does not exists.");
            return;
        }
    }
    void destroyGroup(const std::string &groupName);

    void registerLoader(const std::string &typeName, ResourceLoader *loader);

    Ref<Resource> getResource(const std::string &resourceName);
    Ref<Resource> getResource(std::size_t id);

    Ref<Resource> addResource(const std::string &name, const std::string &groupName, const std::string &typeName);
    void addManualResource(Ref<Resource> resource, const std::string &groupName);

};
}  // namespace Vanadium

#endif  // VANADIUM_RESOURCEMANAGER_H
