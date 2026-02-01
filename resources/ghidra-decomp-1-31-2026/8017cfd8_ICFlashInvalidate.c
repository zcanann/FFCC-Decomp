// Function: ICFlashInvalidate
// Entry: 8017cfd8
// Size: 16 bytes

uint ICFlashInvalidate(void)

{
  uint in_HID0;
  
  return in_HID0 | 0x800;
}

