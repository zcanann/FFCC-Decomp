// Function: GetSoundMode__10CRedDriverFv
// Entry: 801bec90
// Size: 72 bytes

undefined4 GetSoundMode__10CRedDriverFv(void)

{
  int iVar1;
  
  iVar1 = __OSReadROM();
  if (iVar1 == 0) {
    DAT_8032f400 = 1;
  }
  else {
    DAT_8032f400 = DAT_8032f3c8;
  }
  return DAT_8032f400;
}

