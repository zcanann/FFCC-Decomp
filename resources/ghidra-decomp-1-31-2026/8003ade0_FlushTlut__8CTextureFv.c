// Function: FlushTlut__8CTextureFv
// Entry: 8003ade0
// Size: 80 bytes

void FlushTlut__8CTextureFv(CTexture *texture)

{
  int iVar1;
  
  if (texture->field93_0x60 == 9) {
    iVar1 = 0x100;
  }
  else if (texture->field93_0x60 == 8) {
    iVar1 = 0x10;
  }
  else {
    iVar1 = 0;
  }
  DCFlushRange(*(undefined4 *)&texture->field_0x7c,iVar1 << 2);
  return;
}

