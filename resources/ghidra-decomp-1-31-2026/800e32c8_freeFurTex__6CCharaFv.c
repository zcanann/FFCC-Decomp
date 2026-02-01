// Function: freeFurTex__6CCharaFv
// Entry: 800e32c8
// Size: 60 bytes

void freeFurTex__6CCharaFv(void)

{
  if (DAT_8032edf0 != 0) {
    Free__7CMemoryFPv(&Memory);
    DAT_8032edf0 = 0;
  }
  return;
}

