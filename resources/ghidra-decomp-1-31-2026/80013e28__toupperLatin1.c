// Function: ?toupperLatin1
// Entry: 80013e28
// Size: 72 bytes

byte _toupperLatin1(byte character)

{
  if ((((0x60 < character) && (character < 0x7b)) || ((0xdf < character && (character < 0xf7)))) ||
     ((0xf7 < character && (character < 0xfd)))) {
    character = character - 0x20;
  }
  return character;
}

