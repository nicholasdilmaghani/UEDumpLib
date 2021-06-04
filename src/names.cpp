#include "../include/UEDumpLib/UEDump.hpp"
#include "structures.hpp"

namespace UEDump {
  std::pair<bool, uint16_t> detail::FNameEntry::Info() const {
    const auto info = read<uint16_t>(object_ + MemoryLayout::FNameEntry::Info);
    const auto length = info >> MemoryLayout::FNameEntry::LenBit;
    const bool is_wide = (info >> MemoryLayout::FNameEntry::WideBit) & 1;
    return { is_wide, length };
  }

  detail::FNameEntry::operator std::string() const {
    const auto [is_wide, length] = Info();

    if (is_wide) [[unlikely]] {
      // TODO: Add unicode support.
      throw std::exception("Unicode strings unimplemented");
    }

    std::string buffer{ "", length };
    read(object_ + MemoryLayout::FNameEntry::HeaderSize, buffer.data(), length);

    if (fn_decrypt) {
      fn_decrypt(buffer.data(), length);
    }

    return buffer;
  }

  detail::FNameEntry detail::FName::entry(const FNamePool& pool) const {
    const auto display_index = read<uint32_t>(object_);
    return pool.GetEntry(display_index);
  }

}
