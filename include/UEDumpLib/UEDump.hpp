#pragma once

#include <optional>
#include <vector>
#include <map>

#include "callbacks.hpp"
#include "detail.hpp"
#include "detail/objects.hpp"

namespace UEDump {
  

  class ObjectManager {
  public:
    ObjectManager(uintptr_t obj_objects, uintptr_t name_pool);
    ~ObjectManager() = default;
    ObjectManager(ObjectManager&) = delete;
    ObjectManager(ObjectManager&&) = delete;
    ObjectManager& operator=(ObjectManager) = delete;
    ObjectManager& operator=(ObjectManager&&) = delete;

    [[nodiscard]] std::optional<detail::Object> Get(uint32_t id) const;
    [[nodiscard]] std::vector<detail::Object> GetAll() const;
    [[nodiscard]] std::optional<detail::Object> Find(const std::string& name) const;
    //std::optional<detail::Object> Find(const detail::ObjectClass& cls) const;
    [[nodiscard]] std::vector<detail::Object> FindAll(const std::string& name) const;
    [[nodiscard]] std::vector<detail::Object> FindAllOfClass(const detail::Object& cls) const;

    const detail::FNamePool& GetNamePool() const { return name_pool_; }
    [[nodiscard]] std::string GetPoolEntry(uint32_t id) const;

  private:
    detail::FNamePool name_pool_;
    detail::TUObjectArray objects_array_;
  };

  class PropertyManager {
  public:
    PropertyManager(const ObjectManager& object_manager);

    std::unordered_map<std::string, std::unordered_map<std::string, unsigned>> classes_;

  private:
    void GeneratePropertyMap();

    const ObjectManager& object_manager_;
  };
}
