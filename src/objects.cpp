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

    std::string Object::FullName() const {
      std::string full_name;

      for(Object outer = Outer(); outer.object_; outer = outer.Outer()) {
        full_name = outer.Name() + "." + full_name;
      }

      full_name = Class().Name() + " " + full_name + Name();

      return full_name;
    }

    Object Object::Class() const {
      const auto cls = read<uint64_t>(object_ + MemoryLayout::UObject::Class);
      return { cls, pool_ };
    }

    Object Object::Outer() const {
      const auto outer = read<uint64_t>(object_ + MemoryLayout::UObject::Outer);
      return { outer, pool_ };
    }

    std::unordered_map<std::string, unsigned> Object::Properties(const FNamePool& pool) const {
      std::unordered_map<std::string, unsigned> properties;

      auto prop = read<uint64_t>(object_ + MemoryLayout::UStruct::ChildProperties);

      while (prop) {
        const auto fname = FName{ prop + MemoryLayout::FField::Name };
        const auto name = std::string(fname.entry(pool));
        const auto offset = read<uint32_t>(prop + MemoryLayout::FProperty::Offset);

        properties[name] = offset;

        prop = read<uint64_t>(prop + MemoryLayout::FField::Next);
      }

      /*
      auto child = read<uint64_t>(object_ + MemoryLayout::UStruct::Children);

      while (child) {
        const auto fname = FName{ prop + MemoryLayout::FField::Name };
        const auto name = std::string(fname.entry(pool));
        const auto offset = read<uint32_t>(prop + MemoryLayout::FProperty::Offset);

        properties[name] = offset;
        child = read<uint64_t>(prop + MemoryLayout::UField::Next);
      }
      */

      return properties;
    }
  }
}
