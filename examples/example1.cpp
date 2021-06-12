#include "../include/UEDump/UEDump.hpp"

int main() {
  const int process_id = 0;
  const auto process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);

  if (!process_handle) {
    return 1;
  }

  UEDump::callbacks::read = [](uintptr_t addr, void* buff, size_t size) -> bool {
    return ReadProcessMemory(process_handle, (void*)addr, buff, size);
  };

  const auto object_manager = UEDump::ObjectManager{ obj_objs, process::BaseAddress() + offs->namepool };

  // The first NamePool entry is always "None", so assuming we know the cipher (xor) and the key length (4)
  // finding the key is trivial.
  auto first_entry = object_manager.GetPoolEntry(0);
  uint8_t name_key[4] = { 'N', 'o', 'n', 'e' };

  for (auto i = 0; i < first_entry.size(); i++) {
    name_key[i] ^= first_entry[i] ^ first_entry.size();
  }

  UEDump::callbacks::decrypt = [&](char* data, size_t size) {
    for (int i = 0; i < size; i++) {
      data[i] ^= size ^ name_key[i & 3];
    }
  };

  const auto objects = object_manager.GetAll();

  for (const auto& object : objects) {
    std::cout << object.Name() << " : " << object.Address() << std::endl;
  }

  return 0;
}
