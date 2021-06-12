#include "../include/UEDumpLib/UEDump.hpp"
#include "private.hpp"

namespace UEDump {
  PropertyManager::PropertyManager(const ObjectManager& object_manager): object_manager_(object_manager) {
    GeneratePropertyMap();
  }

  void PropertyManager::GeneratePropertyMap() {
    const auto objects = object_manager_.GetAll();

    for (const auto& object : objects) {
      const auto props = object.Properties(object_manager_.GetNamePool());
      classes_[object.Name()] = props;
    }
  }

}