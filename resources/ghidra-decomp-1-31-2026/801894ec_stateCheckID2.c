// Function: stateCheckID2
// Entry: 801894ec
// Size: 56 bytes

void stateCheckID2(void)

{
  DVDLowRead(&DAT_8030ca20,0x20,0x420,cbForStateCheckID2);
  return;
}

