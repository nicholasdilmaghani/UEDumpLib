#include <optional>

#include "../include/UEDumpLib/UEDump.hpp"
#include "structures.hpp"
#include "private.hpp"

namespace UEDump {
  namespace detail {
    std::optional<Object> TUObjectArray::GetObject(uint32_t id, const FNamePool& pool) const {
      const uint32_t chunk_index = id / 0x10000;
      const uint32_t index = id % 0x10000;

      if (id >= num_elements) return {};
      if (chunk_index >= num_chunks) return {};

      const auto chunk = read<uintptr_t>(objects + chunk_index * sizeof(void*));

      if (!chunk) return {};

      const auto obj = read<uintptr_t>(chunk + index * MemoryLayout::FUObjectItem::Size);

      if (!obj) return {};

      return Object{ obj, pool };
    }

    std::string Object::Name() const {
      const auto name = FName{ object_ + MemoryLayout::UObject::Name };
      return std::string(name.entry(pool_));
    }

    // TODO: Implement.
    Object Object::Class() const {
      const auto cls = read<uint64_t>(object_ + MemoryLayout::UObject::Class);
      return { cls, pool_ };
    }

    // TODO: Implement.
    Object Object::Outer() const {
      const auto outer = read<uint64_t>(object_ + MemoryLayout::UObject::Outer);
      return { outer, pool_ };
    }
  }
}
