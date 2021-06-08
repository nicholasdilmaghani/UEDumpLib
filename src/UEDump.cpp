#include "../include/UEDumpLib/callbacks.hpp"
#include "private.hpp"


bool UEDump::detail::read(uintptr_t addr, void* buffer, size_t size) {
  if (callbacks::read) {
    return callbacks::read(addr, buffer, size);
  }
  return false;
}
