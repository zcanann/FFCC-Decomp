// Function: TRKCloseFile
// Entry: 801ad6c0
// Size: 8 bytes

void TRKCloseFile(void)

{
  undefined4 in_r0;
  
  trapWord(0x1f,in_r0,0);
  return;
}

