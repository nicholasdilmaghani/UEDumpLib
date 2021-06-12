#pragma once
/**
 * UEStructures.hpp
 *
 * This is where you set the details of the target's UE structures.
 */

namespace MemoryLayout {
  // alignof(FNameEntry)
  constexpr uint16_t Stride = 4;

  namespace FUObjectItem {
    // sizeof(FUObjectItem)
    constexpr uint16_t Size = 0x14;
  };

  namespace FName {
    // Offset to Number member of FName
    constexpr uint16_t Number = 8;
  };

  namespace FNameEntry {
    // Offset to Memory filled with info about type and size of string
    constexpr uint16_t Info = 4;
    // Offset to bit which shows if string uses wide characters
    constexpr uint16_t WideBit = 0;
    // Offset to bit which has lenght of string
    constexpr uint16_t LenBit = 1;
    // Size of FNameEntry header (offset where a string begins)
    constexpr uint16_t HeaderSize = 6;
  };
  
  namespace UObject {
    // Offset to index of this object in all objects array
    constexpr uint16_t Index = 0xC;
    // Offset to UClass pointer (UClass* ClassPrivate)
    constexpr uint16_t Class = 0x10;
    // Offset to FName structure
    constexpr uint16_t Name = 0x18;
    // (UObject* OuterPrivate)
    constexpr uint16_t Outer = 0x28;
  };

  namespace UField {
    constexpr uint16_t Next = 0x30;
  };

  namespace UStruct {
    // Offset to parent structure
    constexpr uint16_t Supernamespace = 0x48;
    // Offset to children array
    constexpr uint16_t Children = 0x50;
    constexpr uint16_t ChildProperties = 0x58;
    constexpr uint16_t PropertiesSize = 0x60;
  };

  namespace UEnum {
    constexpr uint16_t Names = 0x48;
  };

  namespace UFunction {
    constexpr uint16_t FunctionFlags = 0xB8;
    // Always +0x28 from flags location
    constexpr uint16_t Func = 0xB8 + 0x38;
  };

  namespace FField {
    constexpr uint16_t Class = 8;
    constexpr uint16_t Next = 0x20;
    constexpr uint16_t Name = 0x28;
  };

  namespace FProperty {
    constexpr uint16_t ArrayDim = 0x38;
    constexpr uint16_t ElementSize = 0x3C;
    constexpr uint16_t PropertyFlags = 0x40;
    constexpr uint16_t Offset = 0x4C;
    // sizeof(FProperty)
    constexpr uint16_t Size = 0x80;
  };

  namespace UProperty {
    constexpr uint16_t ArrayDim = 0x38;
    // Offset to property size
    constexpr uint16_t ElementSize = 0x3C;
    // Offset to flags
    constexpr uint16_t PropertyFlags = 0x40;
    // Offset to property offset
    constexpr uint16_t Offset = 0x4C;
    // sizeof(UProperty)
    constexpr uint16_t Size = 0x80;
  };
};
