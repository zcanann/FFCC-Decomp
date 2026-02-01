// Function: stateReadingFST
// Entry: 80188b40
// Size: 148 bytes

void stateReadingFST(void)

{
  DAT_8032f0c4 = stateReadingFST;
  if (*(uint *)(DAT_8032f088 + 0x3c) < DAT_8030ca28) {
    OSPanic(&DAT_8032eaec,0x287,s_DVDChangeDisk____FST_in_the_new_d_802175fc);
  }
  DVDLowRead(*(undefined4 *)(DAT_8032f088 + 0x38),DAT_8030ca28 + 0x1f & 0xffffffe0,DAT_8030ca24,
             cbForStateReadingFST);
  return;
}

