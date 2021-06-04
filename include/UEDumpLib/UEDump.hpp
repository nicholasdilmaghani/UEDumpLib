#pragma once

#include <optional>
#include <vector>

#include "detail.hpp"
#include "detail/objects.hpp"

namespace UEDump {
  // TODO: Move user-defined functions into object-manager class.
  
  // User defined memory read function.
  extern detail::read_t fn_read;

  // User defined FName decryption function
  extern detail::name_decrypt_t fn_decrypt;

  inline bool read(uintptr_t address, void* buffer, size_t size) {
    return fn_read(address, buffer, size);
  }

  template<typename T>
  T read(uintptr_t address) {
    T buffer{};
    read(address, &buffer, sizeof(T));
    return buffer;
  }

  class ObjectManager {
  public:
    ObjectManager(uintptr_t obj_objects, uintptr_t name_pool);
    ~ObjectManager() = default;
    ObjectManager(ObjectManager&) = delete;
    ObjectManager(ObjectManager&&) = delete;
    ObjectManager& operator=(ObjectManager) = delete;
    ObjectManager& operator=(ObjectManager&&) = delete;

    std::optional<detail::Object> Find(const std::string& name) const;
    //std::optional<detail::Object> Find(const detail::ObjectClass& cls) const;

    std::vector<detail::Object> FindAll(const std::string& name) const;

    std::optional<detail::Object> Get(uint32_t id);

  private:
    detail::FNamePool name_pool_;
    detail::TUObjectArray objects_array_;
  };

  class Dumper {
    Dumper(ObjectManager& object_manager);
  };
}
