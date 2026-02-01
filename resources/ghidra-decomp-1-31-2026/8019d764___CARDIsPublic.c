// Function: __CARDIsPublic
// Entry: 8019d764
// Size: 48 bytes

undefined4 __CARDIsPublic(CARDDir *cardDir)

{
  if (cardDir->gameName[0] == 0xff) {
    return 0xfffffffc;
  }
  if ((cardDir->permission & 4) != 0) {
    return 0;
  }
  return 0xfffffff6;
}

