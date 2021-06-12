#pragma once

#include "names.hpp"

#include <string>
#include <map>

namespace UEDump {
  namespace detail {
    class Object;
    class TUObjectArray;

    class Object {
    public:
      Object(uintptr_t object, const FNamePool& pool) : object_(object), pool_(pool) {}

      Object(const Object& old) : object_(old.object_), pool_(old.pool_) {}
      Object& operator=(const Object& old) { object_ = old.object_; return *this; }

      operator bool() const { return object_; }
      uintptr_t Address() const { return object_; }
      std::string Name() const;
      std::string FullName() const;
      std::string CppName() const;
      Object Class() const;
      Object Outer() const;
      bool IsDerivedFrom(Object obj);
      std::unordered_map<std::string, unsigned> Properties(const FNamePool& pool) const;

    private:
      uintptr_t object_;
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
