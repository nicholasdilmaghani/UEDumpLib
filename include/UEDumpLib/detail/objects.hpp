#pragma once

#include "names.hpp"

namespace UEDump {
  namespace detail {
    class Object;
    class ObjectClass; // TODO: Implement.
    class TUObjectArray;

    class Object {
    public:
      Object(uintptr_t object, const FNamePool& pool) : object_(object), pool_(pool) {}
      operator bool() const { return object_; }
      uintptr_t Address() const { return object_; }
      std::string Name() const;
      Object Class() const;
      Object Outer() const;

    private:
      const uintptr_t object_;
      const FNamePool& pool_;
    };

    struct TUObjectArray {
      [[nodiscard]] std::optional<Object> GetObject(uint32_t id, const FNamePool& pool) const;

      uintptr_t objects;
      uintptr_t preallocated_objects;
      uint32_t max_elements;
      uint32_t num_elements;
      uint32_t max_chunks;
      uint32_t num_chunks;
    };
  }


}
