#include "../include/UEDumpLib/UEDump.hpp"

namespace UEDump {
  ObjectManager::ObjectManager(uintptr_t obj_objects, uintptr_t name_pool) {
    objects_array_ = detail::TUObjectArray{};
    name_pool_ = detail::FNamePool{};

    if (!read(obj_objects, &objects_array_, sizeof(objects_array_))) {
      throw std::exception();
    }

    // First part of the name pool gives us the total size of it.
    // So we split the read into 2 parts:
    // One for the header, a second for the blocks

    if (!read(name_pool, &name_pool_, 0x10)) {
      throw std::exception();
    }

    name_pool_.blocks = std::make_unique<detail::FNameEntry[]>(name_pool_.current_block);

    if (!read(name_pool, name_pool_.blocks.get(),
      name_pool_.current_block * sizeof(void*))) {
      throw std::exception();
    }

    // First entry is _always_ "None" so we test it to ensure everything is working.

    auto entry = name_pool_.GetEntry(0);

    if (std::string(entry) != "None") {
      throw std::exception();
    }
  }

  std::optional<detail::Object> ObjectManager::Find(const std::string& name) const {
    for(auto i = 0; i < objects_array_.num_elements; i++) {
      const auto obj = objects_array_.GetObject(i);

      if (obj && obj->Name(name_pool_) == name) {
        return obj;
      }
    }

    return {};
  }

  std::vector<detail::Object> ObjectManager::FindAll(const std::string& name) const {
    std::vector<detail::Object> objects;

    for (auto i = 0; i < objects_array_.num_elements; i++) {
      const auto obj = objects_array_.GetObject(i);

      if (obj && obj->Name(name_pool_) == name) {
        objects.push_back(*obj);
      }
    }

    return objects;
  }
}
