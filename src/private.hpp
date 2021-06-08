#pragma once

namespace UEDump {
  namespace detail {

    bool read(uintptr_t addr, void* buffer, size_t size);

    template<typename T>
    T read(uintptr_t address) {
      T buffer{};
      read(address, &buffer, sizeof(T));
      return buffer;
    }

  }
}
