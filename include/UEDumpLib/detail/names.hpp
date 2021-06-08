#pragma once

#include <string>

#include "../detail.hpp"
#include "../UEDump.hpp"

namespace UEDump {
  namespace detail {
    class FName;
    class FNameEntry;
    class FNamePool;

    struct FNameEntryHandle {
      FNameEntryHandle(uint32_t id) : block(id >> 16), offset(id & 0xFFFF) {}

      uint32_t block = 0;
      uint32_t offset = 0;
    };

    class FNameEntry {
    public:
      explicit FNameEntry(uintptr_t object) : object_(object) {}
      FNameEntry() : FNameEntry(0) {}
      operator bool() const { return object_; }
      explicit operator std::string() const;

    private:
      [[nodiscard]] std::pair<bool, uint16_t> Info() const;
      uintptr_t object_;
    };


    class FName {
    public:
      FName(uintptr_t object) : object_(object) {}
      FNameEntry entry(const FNamePool& pool) const;

    private:
      uintptr_t object_;
    };
    class FNamePool {
    public:
      FNamePool() : lock{ 0 }, current_block{ 0 }, current_byte_cursor{ 0 } {}
      [[nodiscard]] FNameEntry GetEntry(FNameEntryHandle handle) const;

      friend ObjectManager;
      friend FNameEntry;
      friend FName;

    private:
      uint8_t lock[8];
      uint32_t current_block;
      uint32_t current_byte_cursor;
      std::unique_ptr<uintptr_t[]> blocks;
    };
  }


}
