#pragma once

#include "detail.hpp"

#ifdef _LIB
#define CALLBACK extern
#else
#define CALLBACK
#endif

namespace UEDump {
  namespace callbacks {
    CALLBACK detail::read_t read;
    CALLBACK detail::name_decrypt_t decrypt;
  }
}