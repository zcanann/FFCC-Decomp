// Function: TRKOpenFile
// Entry: 801ad6b8
// Size: 8 bytes

void TRKOpenFile(void)

{
  undefined4 in_r0;
  
  trapWord(0x1f,in_r0,0);
  return;
}

