#pragma once

#include <functional>
#include <memory>

namespace UEDump {
  class ObjectManager;

  namespace detail {
    typedef std::function<bool(uintptr_t, void*, size_t)> read_t;
    typedef std::function<void(char*, unsigned int)> name_decrypt_t;

    
  }
}
