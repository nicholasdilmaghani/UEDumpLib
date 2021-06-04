#include <optional>

#include "../include/UEDumpLib/UEDump.hpp"
#include "structures.hpp"

namespace UEDump {
  namespace detail {
    std::optional<Object> TUObjectArray::GetObject(uint32_t id) const {
      const uint32_t chunk_index = id / 0x10000;
      const uint32_t index = id % 0x10000;

      if (id >= num_elements) return {};
      if (chunk_index >= num_chunks) return {};

      const auto chunk = read<uintptr_t>(objects + chunk_index);

      if (!chunk) return {};

      const auto obj = read<uintptr_t>(chunk + index * MemoryLayout::FUObjectItem::Size);

      if (!obj) return {};

      return Object{ obj };
    }

    std::string Object::Name(const FNamePool& pool) const {
      const auto name = FName{ object_ + MemoryLayout::UObject::Name };
      return std::string(name.entry(pool));
    }

    // TODO: Implement.
    Object Object::Class() const {
      return { 0 };
    }

    // TODO: Implement.
    Object Object::Outer() const {
      return { 0 };
    }

  }
}
